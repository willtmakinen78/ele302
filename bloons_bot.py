from __future__ import print_function
import pixy 
from ctypes import *
from pixy import *
from turrets import *
import math
import os
import sys
import time
import RPi.GPIO as GPIO
from control import Blocks

# Imports from our files
from wrappers import *

# Set up state variables objects
state = "SEARCHING"

# Set up global variables
SETUP_TIME = 6
LEFT_MOST = 0
RIGHT_MOST = 5.5
X_MID_POINT = 160
Y_TARGET = 210
RELOAD_COUNTER = 0

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
pixy.change_prog("color_connected_components")
pixy.set_lamp(0, 0)

# Move turret all the way to the left
sweep_right()
down(0.5)
print("Let's go!")
curr_pos = RIGHT_MOST
just_launched = 0
just_launched_time = 0
elapsed_jl = 0 
x_locked = False

blocks = BlockArray(100)
frame = 0
blob = None # Thing we are currently detecting
   
prev_time = time.time()
elapsed = 0
GO_LEFT = 1

if __name__ == '__main__':
    try:
        mov = Orientation(curr_pos)
        lostObj = lostObject()

        while True:

            # Waits a second after its launch
            if just_launched:
                temp_time = time.time() 
                elapsed_jl += time.time() - just_launched_time
                just_launched_time = temp_time

                # has it sweeped enough 
                if elapsed_jl > 1:
                    just_launched = 0
                    elapsed_jl = 0
                    just_launched_time = 0

            prev_time = time.time()
            print(state)
            drive_state = GPIO.input(psoc_input)
            drive_state = 1

            if (drive_state == 1):

                # see if any objects have been detected
                count = pixy.ccc_get_blocks (100, blocks)

                if (state == "SEARCHING"):
                    # pivot turret back and forth
                    moving = 0
                    GPIO.output(psoc_output, 0)
                    diff = time.time() - prev_time
                    elapsed += diff
                    print(str(elapsed) + " seconds")

                    if (elapsed > RIGHT_MOST):
                        elapsed = 0
                        prev_time = time.time()
                        GO_LEFT = not GO_LEFT
                        stop()
                    
                    if GO_LEFT and not moving:
                        noStop_left()
                        moving = 1
                    elif not GO_LEFT and not moving:
                        noStop_right()
                        moving = 1

                    prev_time = time.time()
                    curr_time = prev_time
    
                    # Has an object been found?
                    if (count > 0 and not just_launched):
                        print("found object, is it in range?")

                        #Get the average of the blocks
                        blob = avg_blocks(count, blocks)
                        ar = blob.area()
                        print(ar)
                        if (ar >= 600):
                            print("In range")
                            # stop turret tell psoc that object has been found
                            stop()
                            GPIO.output(psoc_output, 1)
                            ending_x = blob.xPos
                            state = "TARGETING"
                        else:
                            print("Out of range.")

                # point turret towards target, LAUNCH, confirm hit
                elif (state == "TARGETING"):
                    # point turret towards target, LAUNCH, confirm hit
                    # keep input to psoc updated
                    GPIO.output(psoc_output, 1)
                    count = pixy.ccc_get_blocks (100, blocks)

                    # Target has been lost
                    if (count == 0):
                        lostObj = handle_lost(lostObj)

                        # If we've spent to long trying to find a lost Object,
                        # just go back to searching and move on
                        if (lostObj.timElapse >= SETUP_TIME):
                            state = "SEARCHING"
                            lostObj.lReset()

                        else:
                            # Look right based on location of last seen
                            if ending_x > X_MID_POINT:
                                mov.curr_pos = right(mov.curr_pos, 0.01)

                            # Look left based on location of last seen
                            else:
                                mov.curr_pos = left(mov.curr_pos, 0.01)
                    
                    # Adjust the turret to align with the target
                    else:
                        blob = avg_blocks(count, blocks)

                        # Correct the x direction
                        if not mov.x_locked:
                            print("adjusting x")
                            offset = X_MID_POINT - blob.xPos
                            mov = handle_offset(offset, mov)

                        # Correct the y direction
                        else:
                            print("adjusting y")
                            offset = Y_TARGET - blob.yPos
                            mov = handle_offset(offset, mov, False)
                            if mov.y_locked:
                                state = "LAUNCHING"

                elif (state == "LAUNCHING"):

                    # Reset the targeting variables, update state, and launch
                    mov.oReset()
                    state = "SEARCHING"
                    just_launched = handle_launch()
                    RELOAD_COUNTER += just_launched
                    if just_launched:
                        just_launched_time = time.time()

                    # Check if we should enter the reload state 
                    if RELOAD_COUNTER >= 3:
                        state = "RELOADING"
                
                elif (state == "RELOADING"):
                    re_load = raw_input("Reload? [y/n]")
                    if str(re_load) == "y":
                        RELOAD_COUNTER = 0
                        print("Nice work")
                        state = "SEARCHING"

                else:
                    state = "SEARCHING"
                    print("STOPPED")    
                
    finally:
        # reset GPIO ports
        GPIO.cleanup()                    