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

const float speedOfSound = 343.0;

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

float frontDistanceArray[] = {0,0,0};
float rightDistanceArray[] = {0,0,0};
float backDistanceArray[] = {0,0,0};

const int lightPin = 9;

void steer(int t, int d) {
  while (turn != t) {
    turn += turn < t ? 1 : -1;

    turnPin.write(turnCenter + turn);

    delay(30);
  }

  delay(d);
}
float filter(float a, float b, float c) {
  if(a < b) {
    if (b < c) {
      return b;
    } else if (a < c) {
      return c;
    } else {
      return a;
    }
  } else if (a < c) {
    return a;
  } else if (b < c) {
    return c;
  } else {
    return b;
  }
}

void drive(int v) {
  while (vel != v) {
    vel += vel < v ? 1 : -1;

    drivePin.write(driveCenter + vel);

    delay(30);
  }
}

void center() {
  turnPin.write(turnCenter);
}

void halt() {
  drivePin.write(driveCenter);
}

void steerDrive(int t, int v, int d) {
  while (turn != t || vel != v) {
    turn += turn < t ? 1 : -1;
    vel += vel < v ? 1 : -1;

    turnPin.write(turnCenter + turn);
    drivePin.write(driveCenter + vel);

    delay(30);
  }

  delay(d);
}

void alphaTest() {
  // turnPin.write(94); // 94 CENTER!!
  // delay(3000);
  // turnPin.write(74); // 94 - 20 = 144 LEFT!!
  // delay(3000);
  // turnPin.write(94); // 94 CENTER!!
  // delay(3000);
  // turnPin.write(20); // 94 + 20 = 144 RIGHT!!

  // drivePin.write(110); // Forward -- "That's a good speed" - Mr. Dickie
  // drivePin.write(80); // Backward -- "Hehehe...there you go" - Mr. Dickie

  steerDrive(  0,  20, 2000);
  // steerDrive( 20,  15, 3000);
  steer(20, 2000);
  steerDrive(  0,  20, 2000);
  steer(-20, 2000);
  steerDrive(  0,   0, 3000);

  steerDrive(  0, -20, 2000);
  steer(20, 2000);
  steerDrive(  0, -20, 2000);
  steer(-20, 2000);
  steerDrive(  0, -20, 3000);
  steerDrive(  0,   0, 3000);

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

  // alphaTest();
  // bravoTest();
  // charlieTest();
  // deltaTask();
  foxTrotTask();

  //delay(1000);
  halt();
  center();
  blinkLight(10);
}

void loop() {
  Serial.println("Distance: " + String(getDistanceFront()));
}

float getDistanceFront() {

  frontDistanceArray[0] = frontDistanceArray[1];
  frontDistanceArray[1] = frontDistanceArray[2];

  digitalWrite(frontTrigPin, LOW);
    
  delayMicroseconds(2);

  digitalWrite(frontTrigPin, HIGH); 

  delayMicroseconds(10);  
    
  digitalWrite(frontTrigPin, LOW);  

  frontDistanceArray[2] = pulseIn(frontEchoPin, HIGH);

  return filter(frontDistanceArray[0], frontDistanceArray[1], frontDistanceArray[2]);
}

float getDistanceRight() {

  rightDistanceArray[0] = rightDistanceArray[1];
  rightDistanceArray[1] = rightDistanceArray[2];

  digitalWrite(rightTrigPin, LOW);
    
  delayMicroseconds(2);

  digitalWrite(rightTrigPin, HIGH); 

  delayMicroseconds(10);  
    
  digitalWrite(rightTrigPin, LOW);  

  rightDistanceArray[2] = pulseIn(rightEchoPin, HIGH);

  return filter(rightDistanceArray[0], rightDistanceArray[1], rightDistanceArray[2]);
}


float getDistanceBack() {

  backDistanceArray[0] = backDistanceArray[1];
  backDistanceArray[1] = backDistanceArray[2];

  digitalWrite(backTrigPin, LOW);
    
  delayMicroseconds(2);

  digitalWrite(backTrigPin, HIGH); 

  delayMicroseconds(10);  
    
  digitalWrite(backTrigPin, LOW);  

  backDistanceArray[2] = pulseIn(backEchoPin, HIGH);

  return filter(backDistanceArray[0], backDistanceArray[1], backDistanceArray[2]);
}

void driveToDistance(float distance) {
  
  while (getDistanceFront() <= distance) {
    drive(40);
  }

}

void blinkLight(int time) {
  for (int i = 0; i < time; i++) {
    digitalWrite(lightPin, HIGH);
    delay(500);
    digitalWrite(lightPin, LOW);
    delay(500);
  }
}


void bravoTest() {
  // steerDrive(  0,  20, 3000); // drive out of box
  // steerDrive( 20,  15, 5000); // steer right out
  // steerDrive(  0,  15,  500); // ease forward
  // steerDrive(  0,   0, 2000); // pause
  // steerDrive(  0, -20, 4000); // back-up
  // steerDrive(  0,   0, 2000); // pause
  // steerDrive( 20,  15, 5000); // steer right into box
  // steerDrive(  0,  15,  500); // ease forward
  // steerDrive(  0,  0,   500); // stop

  drive(20);
  delay(2000);
  steer(20,0);
  delay(6000);
  steer(0,0);
  delay(500);
  drive(0);
  delay(2000);
  drive(-15);
  delay(8000);
  drive(0);
  delay(500);
  steer(20,0);
  drive(20);
  delay(5000);
  steer(0,0);
  delay(2000);
  drive(0);
}

void charlieTest() {

  int i = 300;

  while (i > 0) {
    if (getDistanceFront() > 2000000*1.5 / speedOfSound) {
      drive(25);

      i--;
    } else if (getDistanceFront() <= 2000000*1.5 / speedOfSound) {
      drive(0);
    }
  }

}

void deltaTask() {

  while (true) {

    float distance = getDistanceFront();

    if(distance < 30 && distance > 20) {
      drive(20);
    } else if (distance <= 20) {
      drive (10);
    } else if (distance > 30) {
      drive(30);
    }
  }

}

void foxTrotTask() {
// float prevDistance;
// while (true) {
//   prevDistance = distance();
//   distance = getDistanceRight
//   drive(20);
//   delay(6000);
// }

drive(-20);
delay(2000);
drive(0);
delay(1000);
steer(20, 0);
drive(-20);
delay(3000);
steer(-20, 0);
delay(3000);
drive(0);
delay(500);
drive(15);
delay(500);
halt();






// float rightDistance = 0;

// while(rightDistance == 0) {

//  if (getDistanceRight() > 200)  {
//   float rightDistance = getDistanceRight();
//  }
  
  // while (getDistanceRight()+100 < rightDistance) {
  //   int time = millis();

  //   if (millis() - time > 1000) {

  //   }

  //   time = millis() - time;
  // }
}

