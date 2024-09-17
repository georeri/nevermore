#include "Servo.h"
#include "ServoInput.h"

#define led1Pin 10
#define led2Pin 11
#define numPositions 9
ServoInputPin<2> ch(1000, 2000);
ServoInputPin<3> eyes(1000, 2000);
int curPos = 2;
bool leftLast = false;
bool rightLast = false;
int eyesNow = 0;
Servo myservo;
#define servoPin 9
#define left 150
#define right 30
#define front 90
int moveAmount = 1;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  myservo.attach(servoPin);
  myservo.write(front);
  Serial.begin(115200);
  ch.attach();
  eyes.attach();

}

void eyesOn() {
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, HIGH);
}

void eyesOff() {
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
}

void turnToRight() {
  int angle = myservo.read(); 
  if (angle > right) {
    Serial.print("RIGHT ANGLE: ");
    Serial.println(angle);
    myservo.write(angle - moveAmount);
    delay(15);
  }
}

void turnToLeft() {
  int angle = myservo.read(); 
  if (angle < left) {
    Serial.print("LEFT ANGLE: ");
    Serial.println(angle);
    myservo.write(angle + moveAmount);
    delay(15);
  }
}


void loop() {

  eyesNow = eyes.map(1, 3);
  if ( eyesNow == 2 ){
    eyesOn();
  }
  else {
    eyesOff();
  }
  
  curPos = ch.map(1, numPositions);
  if (curPos <3 || curPos>7) {
    Serial.print("CURRENTPOS: ");
    Serial.println(curPos);
    myservo.attach(servoPin);
    if (curPos < 3){
      leftLast = false;
      rightLast = true;
      turnToRight();
    }
    else if (curPos > 7) {
      leftLast = true;
      rightLast = false;
      turnToLeft();
    }
    else {}
  }
  else {
    if (rightLast || leftLast ){
      myservo.detach();
    }
  }
}
