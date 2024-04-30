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

void steer(int t, int d) {
  while (turn != t) {
    turn += turn < t ? 1 : -1;

    turnPin.write(turnCenter + turn);

    delay(20);
  }

  delay(d);
}

void drive(int v, int d) {
  while (vel != v) {
    vel += vel < v ? 1 : -1;

    drivePin.write(driveCenter + vel);

    delay(20);
  }

  delay(d);
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

  center();
  halt();
  delay(500);

  // Box Maneuver

  steerDrive(  0,  20, 1000); // drive out of box
  steerDrive( 20,  15, 5000); // steer right out o
  steerDrive(  0,  15,  500); // ease forward
  steerDrive(  0,   0, 2000); // pause
  steerDrive(  0, -20, 2000); // back-up
  steerDrive(  0,   0, 2000); // pause
  steerDrive( 20,  15, 5000); // steer right into boxmk,jih
  steerDrive(  0,  15,  500);
  steerDrive(  0,  0,   500);

  center();
  halt();


//  turn.write(94); // 94 CENTER!!
//  delay(3000);
//  turn.write(74); // 94 - 20 = 144 LEFT!!
//  delay(3000);
//  turn.write(94); // 94 CENTER!!
//  delay(3000);
//  turn.write(114); // 94 + 20 = 144 RIGHT!!

//  drive.write(110)// ; Forward -- "That's a good speed" - Mr. Dickie
//  drive.write(80); // Backward -- "Hehehe...there you go" - Mr. Dickie
}

void loop() {

}
