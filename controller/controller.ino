#include <SoftwareSerial.h>

#define axisX_TX 3
#define axisX_RX 2

SoftwareSerial axisX(axisX_RX,axisX_TX);
void setup() {

  Serial.begin(9600);
  Serial.println("Hi");
  axisX.begin(115200);
  axisX.println("Hi");
}
char state= ' ';
int var = 0;
void loop() {
  
  if(Serial.available()){
    var = Serial.read();
    if(var == '+'){
      state = var;
    }
  }
  if(axisX.read() == 2 && state == '+'){
    Serial.println("limite switch middle is active");
    state = ' ';
  }
  Serial.println(var);
  axisX.write(var);
  var = 0;
  delay(1000);

}
