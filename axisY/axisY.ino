#include <SoftwareSerial.h>

#define TX 3
#define RX 2
#define LED 13
#define SW_S 5
#define SW_M 6

SoftwareSerial controller(RX,TX);
void setup() {

  Serial.begin(9600);
  Serial.println("hiY");
  controller.begin(115200);
  pinMode(LED,OUTPUT);
  pinMode(SW_S,INPUT_PULLUP);
  pinMode(SW_M,INPUT_PULLUP);

}
char var = ' ';
char state = ' ';
void loop() {
  
  if(controller.available()){
    var = controller.read(); 
  }
  if(var == '2' && state == ' '){
    Serial.println("opening system start..");
    state = '2';
  }
  else if(var == '1' && state == ' '){
    Serial.println("closing system start..");
    state = '1';
  }
  else if(digitalRead(SW_S) == LOW && state == '2'){
    Serial.println("limit switch side is active"); 
    state = ' ';
    controller.write('2');
  }
  else if(digitalRead(SW_M) == LOW && state == '1'){
    Serial.println("limit switch middle is active"); 
    state = ' ';
    controller.write('1');
  }
  
  digitalWrite(LED,HIGH);
  delay(100);
  digitalWrite(LED,LOW);
  delay(100);
  var = ' ';
}
