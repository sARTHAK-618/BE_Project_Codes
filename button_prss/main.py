import machine
import time

LED = machine.Pin(2, machine.Pin.OUT)
BUT = machine.Pin(0, machine.Pin.IN)

while True:
    but_state = BUT.value()
    if (but_state == False):
        LED.value(1)
    else:
        LED.value(0)