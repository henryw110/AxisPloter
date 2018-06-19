


// the maximume in the steper motor is (90degree)
// The maximum in the x direction is (6500)
//The  maximum in the y direction is (7000)





//define each words

#include <Servo.h>
#include <Stepper.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial =  SoftwareSerial(13, 12);
uint8_t buf[9];
#define DRAW 0
#define INITIALISE 1
#define LEFT LOW
#define RIGHT HIGH
#define SPEED 65
//#define Xmax 6500
//#define Ymax 7000
#define POS HIGH
#define NEG LOW
Servo myservo;

// defines pins numbers
const int Xlimit_swich = 5;
const int Ylimit_swich = 6;
const int XstepPin = 2; // define pin 7
const int XdirPin = 3; // define pine 9
const int YstepPin = 8; // define pin 8
const int YdirPin = 9; // define pine 10
const int Zservpin = 11; // define pine 11
int pos = 0; 
 void penUp() 
  {
for (pos = 100; pos <= 110; pos += 2) {
    myservo.write(pos);            
    delay(4);                      
  }
  delay(100);
  }
 void penDown()
 {
 for (pos = 110; pos >= 100; pos -= 2) { 
    myservo.write(pos);              
    delay(4);                       
}
delay(100);
 }
// initialize each swich

int state = INITIALISE;



void set_x() {
  digitalWrite(XdirPin, LEFT);
  while (digitalRead(Xlimit_swich) == LOW) {
    digitalWrite(XstepPin, HIGH);
    delayMicroseconds(SPEED);
    digitalWrite(XstepPin, LOW);
    delayMicroseconds(SPEED);
  }
}
void set_y() {
  digitalWrite(YdirPin, RIGHT);
  while (digitalRead(Ylimit_swich) == LOW) {
    digitalWrite(YstepPin, HIGH);
    delayMicroseconds(SPEED);
    digitalWrite(YstepPin, LOW);
    delayMicroseconds(SPEED);
  }
}


void motor_x(int steps,int dir) {
  digitalWrite(XdirPin, dir);
  for (int x = 0; x < steps; x++) {
    digitalWrite(XstepPin, HIGH);
    delayMicroseconds(SPEED);
    digitalWrite(XstepPin, LOW);
    delayMicroseconds(SPEED);
  }
}
void motor_y(int steps, int dir) {

  digitalWrite(YdirPin, dir);
  for (int x = 0; x < steps; x++) {
    digitalWrite(YstepPin, HIGH);
    delayMicroseconds(SPEED);
    digitalWrite(YstepPin, LOW);
    delayMicroseconds(SPEED);
  }
}



/*void step(boolean dir,int steps){
  digitalWrite(YstepPin, dir);
  digitalWrite(YstepPin, dir);
  delayMicroseconds(SPEED);
  for(int i=0;i<steps;i++){
  digitalWrite(XstepPin, HIGH);
  digitalWrite(YstepPin, HIGH);
  delayMicroseconds(SPEED);
  digitalWrite(XstepPin, LOW);
  digitalWrite(YstepPin, LOW);
  delayMicroseconds(SPEED);
  }

  }*/
 

 

static int x3=0,y3=0;
void alg(int x0, int y0, int x1, int y1) {
 
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 //penUp();
  for(;;){
//    setPixel(x0,y0);
  //  Serial.print(y0);
   // Serial.print(",");
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx;
      if(sx>0){motor_x(1,HIGH);}
      else motor_x(1,LOW); }    
    if (e2 < dy) { err += dx; y0 += sy;
      if(sy>0){motor_y(1,LOW);}
      else motor_y(1,HIGH); }
  }
  //penDown();
 // Serial.write("a");
}

void setup()
{
 // pinMode(11,OUTPUT);
  myservo.attach(11); 
  Serial.setTimeout(1000);
  Serial.begin(115200);
  mySerial.begin(57600);
  mySerial.println("live");
  pinMode(XstepPin, OUTPUT);
  pinMode(XdirPin, OUTPUT);
  pinMode(YstepPin, OUTPUT);
  pinMode(YdirPin, OUTPUT);
  penDown();
  delay(150);
  set_x(); // anitilise it to zero
  set_y(); // anitilise it to zero
  //Serial.println("live");
  //penDown();
  //delay(190);
 // penUp();
  //delay(190);
  alg(0,0,1000,1000);
  mySerial.println("live");
  Serial.write("a");
}

int pos1_x=0;
int pos1_y=0;
int pos2_x=0;
int pos2_y=0;
void loop()
{
   Serial.println("live");
  if (Serial.available() > 0 )
  {

    //mySerial.println("live");
    Serial.readBytes( buf, 4);
    if ((256*buf[1]+buf[0]!=0) || (256*buf[3]+buf[2]!=0)){
    //mySerial.println(256*buf[1]+buf[0]);   
    //mySerial.println(256*buf[3]+buf[2]);
    }
    
    pos2_x = (256*buf[1]+buf[0])*6;
    pos2_y = (256*buf[3]+buf[2])*6; 
    if( (pos2_x !=pos1_x) || (pos2_y !=pos1_y ) ) {
      alg(pos1_x,pos1_y,pos2_x,pos2_y);
      
    }
    pos1_x = pos2_x;
    pos1_y = pos2_y;
   
    
    //mySerial.print(pos2_x);
    //mySerial.print(",");
    //mySerial.println(pos2_y);
    Serial.write("a");
    //mySerial.write("a"); 
    //penUp();
    //delay(20);
    penUp();
    //delay(160);
    penDown();
   // delay(160);
  }
 
  //else Serial.write("a");

 
  
}
/*int xval[]={0,10,0,-10,5,0};
int yval[]={0,6,0,-7,8,0};
void loop()
{
  for(int x=1;x<6;x++)
  {
    alg(xval[x-1],yval[x-1],xval[x],yval[x]);
  }
//alg(xval[0],yval[0],xval[1],yval[1]);  
 while(1);
  
}*/
