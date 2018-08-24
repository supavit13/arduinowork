#include <Wire.h>
#include <DS1307.h>
#define SW_A 6
#define EN_A 7
#define CW_A 8
#define CLK_A 9

#define SW_B 10
#define EN_B 11
#define CW_B 12
#define CLK_B 13

#define IN 4
#define OUT 5

#define RS 2


DS1307 clock;
RTCDateTime dt;
void setup() {

  pinMode(IN,INPUT);
  pinMode(OUT,INPUT);
  pinMode(RS,INPUT);

  pinMode(SW_A , INPUT);
  pinMode(EN_A , OUTPUT);
  pinMode(CW_A , OUTPUT);
  pinMode(CLK_A , OUTPUT);
  
  pinMode(SW_B , INPUT);
  pinMode(EN_B , OUTPUT);
  pinMode(CW_B , OUTPUT);
  pinMode(CLK_B , OUTPUT);

  Serial.begin(9600);
  Serial.println("Ready..");
  clock.begin();
  if (!clock.isReady())
  {
    clock.setDateTime(__DATE__, __TIME__);
  }


}

void loop() {
  if(digitalRead(IN)){
    spinMode('I');
    digitalWrite(RS,HIGH);
  }else if(digitalRead(OUT)){
    spinMode('O'); 
    digitalWrite(RS,HIGH); 
  }

}
void spinMode(char mode){
  switch(mode){
    case 'I':
      Serial.println("Mode I working..");
      break;  
    case 'O':
      Serial.println("Mode O working..");
      break; 
  }
}
