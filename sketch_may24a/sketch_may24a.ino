#include <Servo.h> 

 Servo myservo;

 int pos = 0;    // variable to store the servo position

 void setup() {
  // put your setup code here, to run once:

myservo.attach(11);
}

void loop() {
   for (pos = 110; pos <= 120; pos += 2) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(4);                       // waits 15ms for the servo to reach the position
  }
  delay(60);
  for (pos = 120; pos >= 110; pos -= 2) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(4);                       // waits 15ms for the servo to reach the position
}
delay(60);
}
