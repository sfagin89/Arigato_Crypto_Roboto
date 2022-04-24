from time import sleep
import threading
import enum
import queue
import json
from coinbase.wallet.client import Client
from resources.keys import coinbase_api_key as api_key, coinbase_api_secret as secret, doge_wallet
from awscrt import mqtt
from awsiot import mqtt_connection_builder


class RobotDistance(enum.Enum):
    """This class enumerated codes to indicate the distance the robot should move."""

    SHORT = 0
    MEDIUM = 1
    LONG = 2

# checking Coinbase balance tutorial:
# https://medium.com/@samhagin/check-your-balance-on-coinbase-using-python-5641ff769f91


# Global queue
doge_update_queue = queue.Queue()  # queue used to communicate between crypto balance checker thread and MQQT thread


def get_DOGE_balance():
    client = Client(api_key, secret)
    doge_account = client.get_account(doge_wallet)
    delta_threshold = .25
    previous_balance = round(float(doge_account["balance"]["amount"]), 2)
    while True:
        doge_account = client.get_account(doge_wallet)
        current_balance = doge_account["balance"]["amount"]  # this returns a string
        balance_round = round(float(current_balance), 2)  # convert string balance to float rounded to 2 decimal places
        delta = abs(balance_round - previous_balance)
        if delta >= delta_threshold:  # only add to queue if delta is equal to or greater than threshold
            doge_update_queue.put(RobotDistance.SHORT)  # add distance to the queue
        previous_balance = balance_round  # set the new previous balance
        print(f"Doge Coin Balance: {balance_round}")
        sleep(3)


def send_MQTT_message_to_robot():
    mqtt_connection = mqtt_connect()
    while True:
        if not doge_update_queue.empty():  # checking if the queue has any updates
            robot_distance = doge_update_queue.get()  # get the distance from the queue
            print(f"Robot distance received from queue: {robot_distance}")  # do some work with the distance
            mqtt_publish(mqtt_connection, robot_distance)
            doge_update_queue.task_done()  # indicate that the work with this distance is done

        sleep(1)


# example of how to publish MQTT
def mqtt_connect():
    connection = mqtt_connection_builder.mtls_from_path(
        endpoint=ENDPOINT,
        cert_filepath=PATH_TO_CERTIFICATE,
        pri_key_filepath=PATH_TO_PRIVATE_KEY,
        ca_filepath=PATH_TO_AMAZON_ROOT_CA_1,
        client_id=CLIENT_ID,
        clean_session=False,
        keep_alive_secs=6
    )
    print("Connecting to {} with client ID '{}'...".format(
        ENDPOINT, CLIENT_ID))
    # Make the connect() call
    connect_future = mqtt_connection.connect()
    # Future.result() waits until a result is available
    connect_future.result()
    print("Connected!")

    return connection


def mqtt_publish(mqtt_connection, data):
    # Publish message to server.
    print('Begin Publish')
    message = {"message": data}
    mqtt_connection.publish(topic=TOPIC, payload=json.dumps(message), qos=mqtt.QoS.AT_LEAST_ONCE)
    print("Published: '" + json.dumps(message) + "' to the topic: " + "'test/testing'")
    sleep(0.1)
    print('Publish End')


if __name__ == '__main__':
    print("Hello, this is application checks the balance of a DOGECOIN wallet and send updates via MQQT")

    doge_wallet_thread  = threading.Thread(target=get_DOGE_balance, daemon=True)
    mqqt_message_thread = threading.Thread(target=send_MQTT_message_to_robot, daemon=True)

    # start the threads
    doge_wallet_thread.start()
    mqqt_message_thread.start()

    # block until threads done
    doge_wallet_thread.join()
    mqqt_message_thread.join()
