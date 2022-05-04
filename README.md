# Arigato the Crypto Roboto
This project deploys a Raspberry Pi robotic car, whose movements are controlled by payments to a crypto-wallet. The robot is subscribed to a movement command topic on an AWS MQTT server. Messages are published to that topic when the robot’s crypto-wallet receives currency, Dogecoin in this case. A user scans a QR code that appears on an e-ink display sitting on top of the robot. The display is controlled by a FRDM-64F board and it interfaces with the board via a custom PCB. 

Our project employs various technologies, including low-level firmware, custom PCB design, IoT communication, APIs, and crypto-currency. Ian Chadwick connected the robot with MQTT, Sara Fagin created the custom PCB for the e-ink display, and Santiago Gomez developed the e-ink firmware for the FRDM-K64F board. He is also responsible for the client application that links the robot’s crypto-wallet with its MQTT Message Broker. This report delves into the implementation of each component. Furthermore, each component discussion provides insight into the development of the respective engineer.




![Firmware Architecture - E-INK Firmware](https://user-images.githubusercontent.com/30096097/166616635-c3e24d55-607d-4b58-ab62-506a47517805.png)


![Firmware Architecture - Development Pipe](https://user-images.githubusercontent.com/30096097/166616664-18d5f208-ab0f-4a01-9c0d-cda46340b7ad.png)


![Firmware Architecture - Crypto App](https://user-images.githubusercontent.com/30096097/166616678-9f83f57f-a751-4170-b36c-24d4db70fd81.png)
