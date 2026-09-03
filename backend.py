import paho.mqtt.client as mqtt
import json
from dotenv import load_dotenv
import os
from useKi import predict_data

load_dotenv()

ip = os.getenv("IPADDRESS")
sendTopic = "led/control"


def on_connect(client, userdata, flags, rc):
    print("Connected with code ", rc)
    client.subscribe("plant/sensors")


def on_message(client, userdata, msg):
    print(f"data: {msg.topic}, {msg.payload.decode()}")
    data = json.loads(msg.payload.decode())
    predictedValue = predict_data(data)
    print(predictedValue)
    if(predictedValue < 40):
        print("Message send led on ")
        client.publish(sendTopic,json.dumps({"LED":"ON"}))
    else:
        print("Message send led off ")
        client.publish(sendTopic,json.dumps({"LED":"OFF"}))



client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(ip, 1883, 60)

client.loop_forever()


