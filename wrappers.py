from turrets import *
import time

#Simplified blob class
class AvgBlob:
    xPos = 0
    yPos = 0
    width = 0
    height = 0

    def __init__(self, x, y, width, height):
        self.xPos = x
        self.yPos = y
        self.width = width
        self.height = height

    def area(self):
        return self.height*self.width


# Determine the average position of multiple blocks
def avg_blocks(count, blocks):
    print("COUNT: " + str(count))
    x = 0
    y = 0
    w = 0
    h = 0
    for i in range(0, count):
        x += blocks[i].m_x
        y += blocks[i].m_y
        w += blocks[i].m_width
        h += blocks[i].m_height
    return AvgBlob(x/count, y/count, w/count, h/count)

# Turret movement wrapper function -- RIGHT
def right(current_pos, secs):
    turret_right()
    time.sleep(secs)
    turret_stop()
    if current_pos is not None:
        return current_pos + secs

# Turret movement wrapper function -- LEFT
def left(current_pos, secs):
    turret_left()
    time.sleep(secs)
    turret_stop()
    if current_pos is not None:
        return current_pos - secs

# Turret movement wrapper function -- UP
def up(secs):
    turret_up()
    time.sleep(secs)
    turret_stop()

# Turret movement wrapper function -- DOWN
def down(secs):
    turret_down()
    time.sleep(secs)
    turret_stop()

# Turret movement wrapper function -- LAUNCH
def launch():
    turret_fire()
    time.sleep(3.5)

# Turret movement wrapper function -- STOP
def stop():
    turret_stop()

# Reset the turret to the left most position
def sweep_left():
    turret_left()
    time.sleep(5.5)
    turret_stop()
    print("Done.")

# Reset the turret to the right most position
def sweep_right():
    turret_right()
    time.sleep(5.5)
    turret_stop()
    print("Done.")

# No stop right
def noStop_right():
    turret_right()

# No stop left
def noStop_left():
    turret_left()




