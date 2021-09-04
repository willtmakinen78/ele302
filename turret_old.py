from __future__ import print_function
import pixy 
from ctypes import *
from pixy import *

import os
import sys
import time
import RPi.GPIO as GPIO

FIRE_TIME = 3.5
state = "SEARCHING"

# ensure sudo priveledges
if not os.geteuid() == 0:
    sys.exit("Script must be run as root.")

# setup GPIO pins
GPIO.setmode(GPIO.BCM)

psoc_output = 20
psoc_input = 16

# initiate GPIO
GPIO.setup(psoc_output, GPIO.OUT)
GPIO.setup(psoc_input, GPIO.IN)
GPIO.output(psoc_output, 0)



# initiate pixy
pixy.init()
pixy.change_prog ("color_connected_components");

class Blocks (Structure):
  _fields_ = [ ("m_signature", c_uint),
    ("m_x", c_uint),
    ("m_y", c_uint),
    ("m_width", c_uint),
    ("m_height", c_uint),
    ("m_angle", c_uint),
    ("m_index", c_uint),
    ("m_age", c_uint) ]

blocks = BlockArray(100)
frame = 0


   
if __name__ == '__main__':
    try:
        while True:   
            drive_state = GPIO.input(psoc_input)
            if (drive_state == 1):
                if (state == "SEARCHING"):
                    # pivot turret back and forth or something
                    print(state)
                    turret_left()
                    GPIO.output(psoc_output, 0)
                    
                    # see if any objects have been detected
                    count = pixy.ccc_get_blocks (100, blocks)
                    if (count > 0):
                        # tell psoc that object has been found
                        GPIO(psoc_output, 1)
                        print("found object, delaying 2 secs and transitioning to SHOOTING state")
                        time.sleep(2)
                        state = "SHOOTING"
                        
                elif (state == "SHOOTING"):
                    # point turret towards target, shoot, confirm hit
                    println(state)
                    # keep input to psoc updated
                    GPIO(psoc_output, 1)
                    print("delaying 5 secs to emulate shooting then going back to SEARCHING state")
                    turret_fire()
                    time.sleep(5)
                    
            else:
                state = "SEARCHING"
                print("STOPPED")
            
                
    finally:
        # reset GPIO ports
        GPIO.cleanup()                    
