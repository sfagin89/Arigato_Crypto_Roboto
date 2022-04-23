from coinbase.wallet.client import Client
from resources.keys import coinbase_api_key as api_key, coinbase_api_secret as secret, doge_wallet


# checking Coinbase balance tutorial:
# https://medium.com/@samhagin/check-your-balance-on-coinbase-using-python-5641ff769f91

client = Client(api_key, secret)
doge_account = client.get_account(doge_wallet)
balance = doge_account["balance"]["amount"]
balance_round = round(float(balance), 2)
print(f"Doge Coin Balance: {balance_round}")

