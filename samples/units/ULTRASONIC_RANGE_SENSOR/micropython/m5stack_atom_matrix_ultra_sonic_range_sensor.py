from m5stack import *
from m5ui import *
from uiflow import *
import unit
import math

Ultrasonic_1 = unit.get(unit.ULTRASONIC, unit.PORTA)

dist = None

while True:
  dist = Ultrasonic_1.distance
  print("Distance:", dist)
  wait_ms(25)
