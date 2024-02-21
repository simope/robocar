#include "robocar.h"
#include <DabbleESP32.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <ESP32Servo.h> 
#include <LCD_I2C.h>

LCD_I2C lcd(0x3F, 16, 2);
Servo myservo;  // create servo object to control a servo
int servoPin = 5;  // GPIO pin used to connect the servo control (digital out)
int position = 0;
int honk = 4;

// Initialize Car with its pins
Car myCar(0, 2, 15, 14, 13);

void setup(){
  pinMode(honk, OUTPUT);
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
  lcd.backlight();
  Serial.begin(115200);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("ESP32_Car");       //set bluetooth name of your device
  myCar.stop();
  	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(servoPin, 500, 2400);   // attaches the servo on pin 18 to the servo object
                                         // using SG90 servo min/max of 500us and 2400us
                                         // for MG995 large servo, use 1000us and 2000us,
                                         // which are the defaults, so this line could be
                                         // "myservo.attach(servoPin);"
  lcd.print("    ROBO-BEE");
}

void loop(){

  noTone(honk);
  Dabble.processInput();
  if (position>180){position=180;}
  if (position<0){position=0;}

  if (GamePad.isStartPressed())
  {
    tone(honk, 440);
  }

  if (GamePad.isUpPressed())
  {
    Serial.println("FORWARD!");
    myCar.moveFW();
  }

  if (GamePad.isDownPressed())
  {
    Serial.println("RETREAT!");
    myCar.moveBW();
  }

  if (GamePad.isLeftPressed())
  {
    Serial.println("To the left!");
    myCar.moveL();
  }

  if (GamePad.isRightPressed())
  {
    Serial.println("To the right!");
    myCar.moveR();
  }

  if (GamePad.isCrossPressed())
  {
    Serial.println("GAASS!");
    myCar.accelerate();
    Serial.println(myCar.getSpeed());
  }

  if (GamePad.isCirclePressed())
  {
    Serial.println("SLOW DOWN!");
    myCar.decelerate();
    Serial.println(myCar.getSpeed());

  }
  
  if (GamePad.isTrianglePressed())
  {
    Serial.println("UP THE VIEW!");
    position += 15;
    myservo.write(position);
    Serial.println(myCar.getSpeed());

  }
  
    if (GamePad.isSquarePressed())
  {
    Serial.println("DOWN THE VIEW!");
    position -= 15;
    myservo.write(position);
    Serial.println(myCar.getSpeed());

  }
	delay(100);	

  myCar.stop();
}
