from sys import argv
from helper import *
from pixy import *
import pixy 
from ctypes import *



class Blocks (Structure):
  _fields_ = [ ("m_signature", c_uint),
    ("m_x", c_uint),
    ("m_y", c_uint),
    ("m_width", c_uint),
    ("m_height", c_uint),
    ("m_angle", c_uint),
    ("m_index", c_uint),
    ("m_age", c_uint) ]

if __name__ == "__main__":
    command = argv[1]
    if len(argv) > 2:
        time = float(argv[2])

    if command == "right":
        right(None, time)
    elif command == "left":
        left(None, time)
    elif command == "up":
        up(time)
    elif command == "down":
        down(time)
    elif command == "launch":
        launch()
    elif command == "resetl":
        reset_left()
    elif command == "resetr":
        reset_right()
    elif command == "time":
        print(time.time())
        time.sleep(3)
        print(time.time())
    elif command == "sweep":
        right(None, 6)
        while True:
            left(None, 6)
            right(None, 6)
    elif command == "size":
        # initiate pixy
        pixy.init()
        pixy.change_prog("color_connected_components")
        pixy.set_lamp(0, 0)
        blocks = BlockArray(100)
        height = 0
        width = 0
        for i in range(0, 100):
            count = pixy.ccc_get_blocks (100, blocks)
            if count > 0:
                height += blocks[0].m_height
                width += blocks[0].m_width

        print("area: " + str((width/100 ) * (height/100)))
        print(str(width/100))
        print(str(height/100))

    else:
        print("invalid usage")