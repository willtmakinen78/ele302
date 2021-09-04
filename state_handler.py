from wrappers import *
import time

# Object used for handling of orientation variables
class Orientation:
    l_shift = False
    x_locked = False
    y_locked = False
    curr_pos = 0

    def __init__(self, curr_pos):
        self.curr_pos = curr_pos

    def oReset():
        self.l_shift = False
        self.x_locked = False
        self.y_locked = False

# Object used for handling of lostObject variables
class lostObject:
    lost = False
    tim = 0
    timElapse = 0

    def lReset():
        self.lost = False
        self.tim = 0
        self.timeElapse = 0

def falsify(num):
    return num*[False]

# Handle the case where the turret loses sight of the object while slowing down to target
def handle_lost(lostObj):
    lost = lostObj.lost
    tim = lostObj.tim
    print("Target lost")

    # If we hadn't already lost it, start a time
    if (not lost):
        lostObj.tim = time.time()
        lostObj.lost = True
        lostObj.timElapse = 0
    
    else:
        # How much time has elapsed? 
        prevTim = lostObj.tim
        lostObj.tim = time.time()
        lostObj.timElapse += lostObj.tim - prevTim            



# Calculate the direction of turret move necessary to minimize offset
def handle_offset(offset, mov, x=True):

    # Target the x until offset is less than 10
    if math.fabs(offset) > 10:
        if offset > 0:
            # Object to the left
            if x:
                mov.curr_pos = left(mov.curr_pos, 0.01)
                l_shift = True
            # Object is up
            else:
                up(0.01)
        
        #Object to the right If so, move right
        else:
            if x:
                #Object to the right 
                mov.curr_pos = right(mov.curr_pos, 0.01)
            else:
                down(0.01)

    # Perform one final corretion to prevent overshot
    else:

        # If we are manipulating x, handle overcorrection
        if x:
            # Don't mess with x direction anymore
            mov.x_locked = True

            # Did we correct left? Go right to prevent overcorrection.
            if mov.l_shift:
                mov.curr_pos = right(mov.curr_pos, 0.04)
        
            # Did we correct right? Go left to prevent overcorrection.
            else:
                mov.curr_pos = left(mov.curr_pos, 0.04)

        else:
            mov.y_locked = True

    return mov

# Launch the turret 
def handle_launch():
    inc = 0
    accept = raw_input("Launch?")

    # Should we launch?
    if (str(accept) == "y"):
        #launch()
        inc = 1
        time.sleep(1)
        down(0.4)
        print("Launched!")

    # No launch 
    else:
        print("No launch")

    return inc

def main():
    x, y, z = handle_launch()
    print(type(x))
    print(y)
    print(z)

if __name__ == "__main__":
    main()