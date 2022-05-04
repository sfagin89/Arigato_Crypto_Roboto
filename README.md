# Arigato the Crypto Roboto

EC544 Networking the Physical World

Spring 2022 Final Project




This project deploys a Raspberry Pi robotic car, whose movements are controlled by payments to a crypto-wallet. The robot is subscribed to a movement command topic on an AWS MQTT server. Messages are published to that topic when the robot’s crypto-wallet receives currency, Dogecoin in this case. A user scans a QR code that appears on an e-ink display sitting on top of the robot. The display is controlled by a FRDM-64F board and it interfaces with the board via a custom PCB.

Our project employs various technologies, including low-level firmware, custom PCB design, IoT communication, APIs, and crypto-currency. Ian Chadwick connected the robot with MQTT, Sara Fagin created the custom PCB for the e-ink display, and Santiago Gomez developed the e-ink firmware for the FRDM-K64F board. He is also responsible for the client application that links the robot’s crypto-wallet with its MQTT Message Broker. This report delves into the implementation of each component. Furthermore, each component discussion provides insight into the development of the respective engineer.

## Hardware
- [NXP FRDM-K64F Development Board](https://www.nxp.com/design/development-boards/freedom-development-boards/mcu-boards/freedom-development-platform-for-kinetis-k64-k63-and-k24-mcus:FRDM-K64F)
- [Waveshare’s 2.9 inch V2 e-ink display](https://www.waveshare.com/wiki/4.2inch_e-Paper_Module)
- [Adafruit Stepper + DC Motor FeatherWing motor control board](https://learn.adafruit.com/adafruit-stepper-dc-motor-featherwing)
- [RaspberryPi 3 B+](https://www.raspberrypi.com/products/raspberry-pi-3-model-b-plus/)
- [JetBot Chassis and motors](https://jetbot.org/master/index.html)
- [Custom PCB for e-Ink](https://github.com/sfagin89/Arigato_Crypto_Roboto/tree/main/PCB_files)
  - [Documentation of Full PCB Assembly](https://github.com/sfagin89/Arigato_Crypto_Roboto/tree/main/PCB_files/PCB%20Assembly)

## Software
- [Custom e-Ink Firmware](https://github.com/sfagin89/Arigato_Crypto_Roboto/tree/main/eink_firmware/development/eink_spi_firmware)
- [Robot Software](https://github.com/sfagin89/Arigato_Crypto_Roboto/tree/main/RPi)
- [Crypto App](https://github.com/sfagin89/Arigato_Crypto_Roboto/tree/main/crypto_app)

## Implementation Video
- [EC544 - Arigato Crypto Roboto](https://www.youtube.com/watch?v=zG-Wq4VXOKg)

## Final Report
- [Final Report](https://github.com/sfagin89/Arigato_Crypto_Roboto/blob/main/Final%20Project%20Report.pdf)

## Custom PCB Schematic and Board Layout

### Final PCB Schematic
![Custom PCB Schematic](https://github.com/sfagin89/Arigato_Crypto_Roboto/blob/e5e9a5214d5f0a81ab09beffe147bd4ab1f389d4/PCB_files/ECE544_v3_schem.png)

### Final PCB Board Layout
![Custom PCB Board Layout](https://github.com/sfagin89/Arigato_Crypto_Roboto/blob/c02a1528563c0215d122c3ca72903ed1fb15780a/PCB_files/ECE544_v3_board.png)

### PCB Board Top Layer
![Custom PCB Board Layout - Top Layer](https://github.com/sfagin89/Arigato_Crypto_Roboto/blob/c02a1528563c0215d122c3ca72903ed1fb15780a/PCB_files/ECE544_v3_board_top.png)

### PCB Board Bottom Layer
![Custom PCB Board Layout - Bottom Layer](https://github.com/sfagin89/Arigato_Crypto_Roboto/blob/c02a1528563c0215d122c3ca72903ed1fb15780a/PCB_files/ECE544_v3_board_btm.png)

## Functional Block Diagrams


![Technology Stack](https://user-images.githubusercontent.com/30096097/166684281-6e805d7c-9191-4b2c-8d69-3d8db56d2791.jpeg)



![Firmware Architecture - E-INK Firmware](https://user-images.githubusercontent.com/30096097/166616635-c3e24d55-607d-4b58-ab62-506a47517805.png)


![Firmware Architecture - Development Pipe](https://user-images.githubusercontent.com/30096097/166616664-18d5f208-ab0f-4a01-9c0d-cda46340b7ad.png)


![Robot Car Architecture](https://user-images.githubusercontent.com/13345034/166616968-b8a1f653-6c51-4e58-a324-c958855ef366.jpeg)


![Motor Control Software Architecture](https://user-images.githubusercontent.com/13345034/166617033-9c3753e3-a4ba-4514-a2e5-f6785130dc26.jpeg)


![Motor Control Software Development Pipeline](https://user-images.githubusercontent.com/13345034/166617059-116e8ba1-6c50-40f9-857f-ce57c63b9f24.jpeg)


![Firmware Architecture - Crypto App](https://user-images.githubusercontent.com/30096097/166616678-9f83f57f-a751-4170-b36c-24d4db70fd81.png)
