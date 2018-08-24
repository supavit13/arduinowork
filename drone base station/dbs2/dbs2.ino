#include <Wire.h>
#include <DS1307.h>
//define pin for axis X stepper motor
#define EN_X 9
#define CW_X 8
#define CLK_X 10
//define pin for axis Y stepper motor
#define EN_Y 11
#define CW_Y 12
#define CLK_Y 13
//define pin for limit switch axis X
#define SIDE_SW_X 7
#define MID_SW_X 6
//define pin for limit switch axis Y
#define SIDE_SW_Y 5
#define MID_SW_Y 4

#define IN 3
#define OUT 2

#define RS 0


DS1307 clock;
RTCDateTime dt;

char input = '0';
void setup() {
  //setup pin
  pinMode(EN_X,OUTPUT);
  pinMode(CW_X,OUTPUT);
  pinMode(CLK_X,OUTPUT);
  pinMode(EN_Y,OUTPUT);
  pinMode(CW_Y,OUTPUT);
  pinMode(CLK_Y,OUTPUT);
  pinMode(SIDE_SW_X, INPUT);
  pinMode(MID_SW_X, INPUT);
  pinMode(SIDE_SW_Y, INPUT);
  pinMode(MID_SW_Y, INPUT);
  pinMode(IN, INPUT);
  pinMode(OUT, INPUT);

  pinMode(RS,OUTPUT);
  //set LOW 
  digitalWrite(EN_X,LOW);
  digitalWrite(CW_X,LOW);
  digitalWrite(CLK_X,LOW);
  digitalWrite(EN_Y,LOW);
  digitalWrite(CW_Y,LOW);
  digitalWrite(CLK_Y,LOW);

  Serial.begin(9600);
  Serial.println("Ready..");
  clock.begin();
  if (!clock.isReady())
  {
    clock.setDateTime(__DATE__, __TIME__);
  }

  
}

void loop() {
  int in = digitalRead(IN);
  int out = digitalRead(OUT);
  Serial.println(in);
  Serial.println(out);
  if(in == 1){
    in = 0;
    spinMode('1');
    delay(2000);
    spinMode('3');
    digitalWrite(RS,LOW);
  }else if(out == 1){
    out = 0;
    spinMode('4');
    delay(2000);
    spinMode('2');
    digitalWrite(RS,LOW);
  }
  
}
void spinX(){
  digitalWrite(CLK_X,HIGH);
  delayMicroseconds(200);
  digitalWrite(CLK_X,LOW);
  delayMicroseconds(200);
}
void spinY(){
  digitalWrite(CLK_Y,HIGH);
  delayMicroseconds(200);
  digitalWrite(CLK_Y,LOW);
  delayMicroseconds(200);
}
void cw_axis_X(){
  digitalWrite(CW_X,LOW);
  while(1){
    if(digitalRead(MID_SW_X) == HIGH) break;
    spinX();
  }
  Serial.println("Middle limit switch is ACTIVE in X axis");
}
void ccw_axis_X(){
  digitalWrite(CW_X,HIGH);
  while(1){
    if(digitalRead(SIDE_SW_X) == HIGH) break;
    spinX();
  }
  Serial.println("Side limit switch is ACTIVE in X axis");
}
void cw_axis_Y(){
  digitalWrite(CW_Y,LOW);
  while(1){
    if(digitalRead(MID_SW_Y) == HIGH) break;
    spinY();
  }
  Serial.println("Middle limit switch is ACTIVE in Y axis");
}
void ccw_axis_Y(){
  digitalWrite(CW_Y,HIGH);
  while(1){
    if(digitalRead(SIDE_SW_Y) == HIGH) break;
    spinY();
  }
  Serial.println("Side limit switch is ACTIVE in Y axis");
}
void spinMode(char mode){
  switch(mode){
      case '1' : 
        Serial.println("Mode clockwise rotation in X axis");
        cw_axis_X();
        break;
      case '2' :
        Serial.println("Mode counterclockwise rotation in X axis");
        ccw_axis_X();
        break;
      case '3' :
        Serial.println("Mode clockwise rotation in Y axis");
        cw_axis_Y();
        break;
      case '4' :
        Serial.println("Mode counterclockwise rotation in Y axis");
        ccw_axis_Y();
        break;
      case '0' :
        break;
      default :
        Serial.println("Invalid mode");
        input = '0';
        break;
  }
  input = '0';
  digitalWrite(EN_X,LOW);
  digitalWrite(CW_X,LOW);
  digitalWrite(CLK_X,LOW);
  digitalWrite(EN_Y,LOW);
  digitalWrite(CW_Y,LOW);
  digitalWrite(CLK_Y,LOW);
  Serial.flush();
}

