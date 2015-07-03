# put this file with ports.h
# TODO: define EN_OBSTACLE and OBSTACLE in ports.h and ports.cpp

#include "obstacle.h"
#include "ports.h"
#include <arduino.h>

using namespace Ports;

int Obstacle::hasObstacle()
{
  int val;//定义数字变量val
  digitalWrite(EN_OBSTACLE,HIGH);
  delay(1000);
  val=digitalRead(OBSTACLE);
  return val;
}
