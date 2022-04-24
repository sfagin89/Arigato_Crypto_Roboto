from time import sleep
import threading
import enum
import queue
import json
from coinbase.wallet.client import Client
from resources.keys import coinbase_api_key as api_key, coinbase_api_secret as secret, doge_wallet, AWSIoTCredentials
from awscrt import io, mqtt, auth, http
from awsiot import mqtt_connection_builder


class RobotDistance(enum.Enum):
    """This class enumerated codes to indicate the distance the robot should move."""

    SHORT = 1
    MEDIUM = 3
    LONG = 5

# checking Coinbase balance tutorial:
# https://medium.com/@samhagin/check-your-balance-on-coinbase-using-python-5641ff769f91


# Global queue
doge_update_queue = queue.Queue()  # queue used to communicate between crypto balance checker thread and MQQT thread


def get_DOGE_wallet_id():
    """"This function allows user to identify the IDs for their wallets."""
    client = Client(api_key, secret)
    doge_account = client.get_accounts()
    print(doge_account)


def get_DOGE_balance():
    """This function continuously checks a Coinbase wallet balance."""

    client = Client(api_key, secret)  # establish connection to Coinbase API
    doge_account = client.get_account(doge_wallet)  # get account details for the given wallet

    # thresholds for determining how long to run robot
    delta_short_threshold = 1
    delta_medium_threshold = 2
    delta_long_threshold = 3

    # keep track of previous balance
    previous_balance = round(float(doge_account["balance"]["amount"]), 2)

    # continuously check wallet balance
    while True:
        doge_account = client.get_account(doge_wallet)  # get account details for the given wallet
        current_balance = doge_account["balance"]["amount"]  # extract balance, this returns a string
        balance_round = round(float(current_balance), 2)  # convert string balance to float rounded to 2 decimal places
        delta = abs(balance_round - previous_balance)  # calculate delta

        # only add to queue if delta is equal to or greater than thresholds
        if delta == delta_short_threshold:
            doge_update_queue.put(RobotDistance.SHORT.value)  # add short distance to the queue
        elif delta == delta_medium_threshold:
            doge_update_queue.put(RobotDistance.MEDIUM.value)  # add medium distance to the queue
        elif delta >= delta_long_threshold:
            doge_update_queue.put(RobotDistance.LONG.value)  # add long distance to the queue
        previous_balance = balance_round  # set the new previous balance
        print(f"Doge Coin Balance: {balance_round}")
        sleep(1)  # time delay before next call


def send_MQTT_message_to_robot():
    """This function publishes MQTT message to AWS IoT device when there is update from Coinbase wallet."""

    mqtt_connection = mqtt_connect()   # make MQTT broker connection for AWS IoT device
    mqtt_topic = "robot/move_command"  # topic for publishing

    # continuously check if there are messages in the queue
    while True:
        if not doge_update_queue.empty():  # checking if the queue has any updates
            robot_distance = doge_update_queue.get()  # get the distance from the queue
            print(f"Robot distance received from queue: {robot_distance}")
            mqtt_publish(mqtt_connection, mqtt_topic, robot_distance)  # publish to mqtt
            doge_update_queue.task_done()  # indicate that the work with this distance is done
        sleep(1)


# example of how to publish to AWS IoT via MQTT
# https://aws.amazon.com/premiumsupport/knowledge-center/iot-core-publish-mqtt-messages-python/
def mqtt_connect():
    """This function establishes MQTT connection to AWS IoT. Returns an mqtt connection object."""
    event_loop_group = io.EventLoopGroup(1)
    host_resolver = io.DefaultHostResolver(event_loop_group)
    client_bootstrap = io.ClientBootstrap(event_loop_group, host_resolver)
    mqtt_connection = mqtt_connection_builder.mtls_from_path(
        endpoint=AWSIoTCredentials.ENDPOINT,
        cert_filepath=AWSIoTCredentials.PATH_TO_CERTIFICATE,
        pri_key_filepath=AWSIoTCredentials.PATH_TO_PRIVATE_KEY,
        client_bootstrap=client_bootstrap,
        ca_filepath=AWSIoTCredentials.PATH_TO_AMAZON_ROOT_CA_1,
        client_id=AWSIoTCredentials.CLIENT_ID,
        clean_session=False,
        keep_alive_secs=6
    )
    print("Connecting to {} with client ID '{}'...".format(
        AWSIoTCredentials.ENDPOINT, AWSIoTCredentials.CLIENT_ID))
    # Make the connect() call
    connect_future = mqtt_connection.connect()
    # Future.result() waits until a result is available
    connect_future.result()
    print("Connected!")

    return mqtt_connection


def mqtt_publish(mqtt_connection, topic, data):
    """This function publishes MQTT to AWS IoT."""

    # Publish message to server.
    print('Begin Publish')
    message = data  # {"message": data} can send data as json, choosing to send integer directly

    # publish mqtt message to AWS IoT
    mqtt_connection.publish(topic=topic, payload=json.dumps(message), qos=mqtt.QoS.AT_LEAST_ONCE)
    print("Published: '" + json.dumps(message) + "' to the topic: " + topic)
    print('Publish End')


if __name__ == '__main__':
    print("Hello, this is application checks the balance of a DOGECOIN wallet and send updates via MQQT")

    # uncomment if you want to discover the ID for your wallet
    # get_DOGE_wallet_id()

    doge_wallet_thread  = threading.Thread(target=get_DOGE_balance, daemon=True)
    mqqt_message_thread = threading.Thread(target=send_MQTT_message_to_robot, daemon=True)

    # start the threads
    doge_wallet_thread.start()
    mqqt_message_thread.start()

    # block until threads done
    doge_wallet_thread.join()
    mqqt_message_thread.join()


