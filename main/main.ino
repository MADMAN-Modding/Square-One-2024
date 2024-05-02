/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo turnPin;
Servo drivePin;

const int turnCenter = 94;
const int driveCenter = 90;
int turn = 0; // -20...20
int vel = 0;  // -25...25

//setting up the pins for the front distance sensors
const int frontTrigPin = 2;
const int frontEchoPin = 3;

//setting up the pins for the back distance sensors
const int backTrigPin = 4;
const int backEchoPin = 5;

//setting up the pins for the right distance sensors
const int rightTrigPin = 6;
const int rightEchoPin = 7;

//setting up the pins for the front distance sensors
// const int backTrigPin = 8;
// const int backEchoPin = 9;

const int lightPin = 9;

void steer(int t, int d) {
  while (turn != t) {
    turn += turn < t ? 1 : -1;

    turnPin.write(turnCenter + turn);

    delay(20);
  }

  delay(d);
}

void drive(int v) {
  while (vel != v) {
    vel += vel < v ? 1 : -1;

    drivePin.write(driveCenter + vel);

    delay(20);
  }
}

void center() {
  turnPin.write(turnCenter);
}

void halt() {
  drivePin.write(driveCenter);
}

void steerDrive(int t, int v, int d) {
  while (turn != t && vel != v) {
    turn += turn < t ? 1 : -1;
    vel += vel < v ? 1 : -1;

    turnPin.write(turnCenter + turn);
    drivePin.write(driveCenter + vel);

    delay(20);
  }

  delay(d);
}

void setup() {
  turnPin.attach(12);
  drivePin.attach(10);

  // Front Distant Sensors
  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);

  // // Left Distance Sensors
  // pinMode(leftTrigPin, OUTPUT);
  // pinMode(leftEchoPin, INPUT);

  // Right Distance Sensors
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);

  // Back Distance Sensors
  pinMode(backTrigPin, OUTPUT);
  pinMode(backEchoPin, INPUT);
  Serial.begin(9600);

  pinMode(lightPin, OUTPUT);

  center();
  halt();

  delay(500);

  // alphaTask();
  // bravoTest();
  // charlieTest();
  // deltaTask();
}

void loop() {
  Serial.println("Distance: " + String(getDistanceFront()));
}

float getDistanceFront() {
  digitalWrite(frontTrigPin, LOW);
  
  delayMicroseconds(2);

  digitalWrite(frontTrigPin, HIGH); 

	delayMicroseconds(10);  
	
  digitalWrite(frontTrigPin, LOW);  

  return pulseIn(frontEchoPin, HIGH);
}

// float getDistanceLeft() {
//   digitalWrite(leftTrigPin, LOW);
//  
//   delayMicroseconds(2);
//
//   digitalWrite(leftTrigPin, HIGH); 
//
// 	delayMicroseconds(10);  
// 
//   digitalWrite(leftTrigPin, LOW);  
//
//   return pulseIn(leftEchoPin, HIGH);
// }

float getDistanceRight() {
  digitalWrite(rightTrigPin, LOW);
  
  delayMicroseconds(2);

  digitalWrite(rightTrigPin, HIGH); 

	delayMicroseconds(10);  
	
  digitalWrite(rightTrigPin, LOW);  

  return pulseIn(rightEchoPin, HIGH);
}

float getDistanceBack() {
  digitalWrite(backTrigPin, LOW);
  
  delayMicroseconds(2);

  digitalWrite(backTrigPin, HIGH); 

	delayMicroseconds(10);  
	
  digitalWrite(backTrigPin, LOW);  

  return pulseIn(backEchoPin, HIGH);
}

void driveToDistance(float distance) {
  
  while(getDistanceFront() <= distance) {
    drive(40);
  }

}

void blinkLight(int time) {
  for (int i = 0; i < time; i++) {
    digitalWrite(lightPin, HIGH);
    delay(1000);
    digitalWrite(lightPin, LOW);
    delay(1000);
  }
}

void alphaTest() {
  turnPin.write(94); // 94 CENTER!!
  delay(3000);
  turnPin.write(74); // 94 - 20 = 144 LEFT!!
  delay(3000);
  turnPin.write(94); // 94 CENTER!!
  delay(3000);
  turnPin.write(114); // 94 + 20 = 144 RIGHT!!

  drivePin.write(110); // Forward -- "That's a good speed" - Mr. Dickie
  drivePin.write(80); // Backward -- "Hehehe...there you go" - Mr. Dickie

  blinkLight(10);
}

void bravoTest() {
  steerDrive(  0,  20, 1000); // drive out of box
  steerDrive( 20,  15, 5000); // steer right out o
  steerDrive(  0,  15,  500); // ease forward
  steerDrive(  0,   0, 2000); // pause
  steerDrive(  0, -20, 2000); // back-up
  steerDrive(  0,   0, 2000); // pause
  steerDrive( 20,  15, 5000); // steer right into boxmk,jih
  steerDrive(  0,  15,  500);
  steerDrive(  0,  0,   500);

  center():
  halt();

  blinkLight(10);
}

void charlieTest() {

  int i = 10000;

  while (i > 0) {
    if(getDistanceFront() > 10) {
      drive(40);
      i++
    } else if (getDistanceFront() =< 10) {
      drive(0);
    }
  }
}

void deltaTask() {
  while(true) {

    float distance = getDistanceFront();

    if(distance < 30 && distance > 20) {
      drive(20);
    } else if (distance =< 20) {
      drive (10)
    } else if (distance > 30) {
      drive(30);
    }
  }
}