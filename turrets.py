import usb.core
import time

# open connection to turret
DEV = usb.core.find(idVendor=0x0A81, idProduct=0x0701)
if DEV is None:
    raise ValueError('Launcher not found.')
if DEV.is_kernel_driver_active(0) is True:
    DEV.detach_kernel_driver(0)
# DEV.set_configuration()

if DEV.is_kernel_driver_active(0):
    DEV.detach_kernel_driver(0)
try:
    DEV.set_configuration()
    DEV.reset()
except usb.core.USBError as e:
    sys.exit("Could not set configuration: %s" % str(e))

endpoint = DEV[0][(0,0)][0]
print(endpoint)

def turret_up():
    DEV.ctrl_transfer(0x21,0x09,0x0200,0,[0x02])

def turret_down():
    DEV.ctrl_transfer(0x21,0x09,0x0200,0,[0x01])

def turret_left():
    DEV.ctrl_transfer(0x21,0x09,0x0200,0,[0x04])

def turret_right():
    DEV.ctrl_transfer(0x21,0x09,0x0200,0,[0x08])

def turret_stop():
    DEV.ctrl_transfer(0x21,0x09,0x0200,0,[0x20])

def turret_fire():
    DEV.ctrl_transfer(0x21,0x09,0x0200,0,[0x10])
    time.sleep(5.5)
    DEV.ctrl_transfer(0x21,0x09,0x0200,0,[0x08])
    DEV.ctrl_transfer(0x21,0x09,0x0200,0,[0x20])
    
if __name__ == "__main__":
    turret_right()
    time.sleep(1)
    turret_stop()