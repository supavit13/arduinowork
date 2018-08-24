#include <SoftwareSerial.h>
//define pin for axis X1 stepper motor
#define EN_X1 11
#define CW_X1 12
#define CLK_X1 13
//define pin for axis X2 stepper motor
#define EN_X2 4
#define CW_X2 5
#define CLK_X2 6
//define pin for limit switch axis X2
#define SIDE_LSW_X2 7
#define MID_LSW_X2 8
//define pin for limit switch axis X1
#define SIDE_LSW_X1 10
#define MID_LSW_X1 9
//define pin for input command
#define TX 3
#define RX 2

SoftwareSerial mySerial(RX,TX);
void setup() {

  Serial.begin(9600);
  Serial.println("hiX");
  mySerial.begin(115200);

  pinMode(SIDE_LSW_X1, INPUT);
}
char state = ' ';
int var = 0;
void loop() {
  
  if(mySerial.available()){
    var = mySerial.read();
//    Serial.println(var);  
  }
  if(var == '+'){
    Serial.println("System start..");
    state = '+';
  }
  if(digitalRead(SIDE_LSW_X1)==HIGH && state == '+'){
    Serial.println("limit switch middle is active"); 
    mySerial.write(2);
    state=' ';
    digitalWrite(SIDE_LSW_X1,LOW);
  }
  if(state != ' ') Serial.println(state);
  var = 0;
  delay(1000);

}
