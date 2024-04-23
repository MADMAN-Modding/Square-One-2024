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
  turn.attach(12);
  turn.write(94); // 94 CENTER!!
  delay(3000);
  turn.write(74); // 94 - 20 = 144 LEFT!!
  delay(3000);
  turn.write(94); // 94 CENTER!!
  delay(3000);
  turn.write(114); // 94 + 20 = 144 RIGHT!!
//  delay(3000);
//  turn.write(82);
//  delay(3000);
//  turn.write(80);
//  delay(3000);
//  turn.write(78);
//  delay(3000);
//  turn.write(76);

  
// drive.write(140);
// delay(2000);
// drive.write(90);

//  turn.attach(10);
//  turn.write(45);
//  delay(2000);
//  turn.write(90);

}

void loop() {
  // val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  // val = map(val, 0, 1023, 0, 180);     // scale it for use with the servo (value between 0 and 180)
  // drive.write(val);                  // sets the servo position according to the scaled value
  // delay(15);                           // waits for the servo to get there
}
