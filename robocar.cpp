// robocar.cpp

#include "robocar.h"
#include "Arduino.h"

Car::Car(int ENp, int FW1p, int BW1p, int FW2p, int BW2p) {
  EN = ENp;
  FW1 = FW1p;
  FW2 = FW2p;
  BW1 = BW1p;
  BW2 = BW2p;
  pinMode(EN, OUTPUT);
  pinMode(FW1, OUTPUT);
  pinMode(FW2, OUTPUT);
  pinMode(BW1, OUTPUT);
  pinMode(BW2, OUTPUT);
  speed = 50;
}

int Car::getSpeed() {
  return speed;
}

void Car::accelerate(){
  speed += 2;
  if (speed > 100){
    speed = 100;
  }
}

void Car::decelerate(){
  speed -= 2;
  if (speed < 50){
    speed = 50;
  }
}

void Car::stop() {
  digitalWrite(EN, LOW);
  digitalWrite(FW1, LOW);
  digitalWrite(FW2, LOW);
  digitalWrite(BW1, LOW);
  digitalWrite(BW2, LOW);
}

void Car::moveFW() {
  int duty = (int)(speed/100.0 * 255);
  analogWrite(EN, duty);
  digitalWrite(FW1, HIGH);
  digitalWrite(FW2, HIGH);
  digitalWrite(BW1, LOW);
  digitalWrite(BW2, LOW);
}

void Car::moveBW() {
  int duty = (int)(speed/100.0 * 255);
  analogWrite(EN, duty);
  digitalWrite(FW1, LOW);
  digitalWrite(FW2, LOW);
  digitalWrite(BW1, HIGH);
  digitalWrite(BW2, HIGH);
}

void Car::moveL() {
  int duty = (int)(speed/100.0 * 255);
  analogWrite(EN, duty);
  digitalWrite(FW1, LOW);
  digitalWrite(FW2, HIGH);
  digitalWrite(BW1, HIGH);
  digitalWrite(BW2, LOW);
}

void Car::moveR() {
  int duty = (int)(speed/100.0 * 255);
  analogWrite(EN, duty);
  digitalWrite(FW1, HIGH);
  digitalWrite(FW2, LOW);
  digitalWrite(BW1, LOW);
  digitalWrite(BW2, HIGH);
}