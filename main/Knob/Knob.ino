/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo drive;  // create servo object to control a servo
Servo turn;

int potpin = A0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  drive.attach(10);  // attaches the servo on pin 9 to the servo object
// drive.write(140);
// delay(2000);
// drive.write(90);

  turn.attach(12);
  turn.write(45);
  delay(2000);
  turn.write(90);

  //seting up the pins for the front distance sensors
  const int frontTrigPin = 2;
  const int frontEchoPin = 3;

  //seting up the pins for the left distance sensors
  const int leftTrigPin = 4;
  const int leftEchoPin = 5;

  //seting up the pins for the right distance sensors
  const int rightTrigPin = 6;
  const int rightEchoPin = 7;

  //seting up the pins for the front distance sensors
  const int backTrigPin = 8;
  const int backEchoPin = 9;

  // Front Distant Sensors
  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);

  // Left Distance Sensors
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);

  // Right Distance Sensors
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);

  // Back Distance Sensors
  pinMode(backTrigPin, OUTPUT);
  pinMode(backEchoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  // val = map(val, 0, 1023, 0, 180);     // scale it for use with the servo (value between 0 and 180)
  // drive.write(val);                  // sets the servo position according to the scaled value
  // delay(15);                           // waits for the servo to get there
}

float getDistanceFront() {
  digitalWrite(frontTrigPin, LOW);
  
  delayMicroseconds(2);

  digitalWrite(frontTrigPin, HIGH); 

	delayMicroseconds(10);  
	
  digitalWrite(frontTrigPin, LOW);  

  return pulseIn(frontEchoPin, HIGH);
}

float getDistanceLeft() {
  digitalWrite(leftTrigPin, LOW);
  
  delayMicroseconds(2);

  digitalWrite(leftTrigPin, HIGH); 

	delayMicroseconds(10);  
	
  digitalWrite(leftTrigPin, LOW);  

  return pulseIn(leftEchoPin, HIGH);
}

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