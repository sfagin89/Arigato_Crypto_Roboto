import time
import sys
import board
from adafruit_motorkit import MotorKit

def motor(runTime):
    
    kit = MotorKit(i2c=board.I2C())

    kit.motor1.throttle = .5
    kit.motor2.throttle = -.5
    time.sleep(runTime)
    kit.motor1.throttle = 0
    kit.motor2.throttle = 0

    
    