#include <SoftwareSerial.h>

#define axisX_TX 3
#define axisX_RX 2

#define axisY_TX 6
#define axisY_RX 7
#define openButton 5
#define closeButton 4

SoftwareSerial axisX(axisX_RX,axisX_TX);
SoftwareSerial axisY(axisY_RX,axisY_TX);
void setup() {
  pinMode(openButton,INPUT_PULLUP);
  pinMode(closeButton,INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Hi");
  axisX.begin(115200);
  axisY.begin(115200);
  
}

char state= ' ';
int var = 0;

void loop() {
  int openSys = digitalRead(openButton);
  int closeSys = digitalRead(closeButton);

  if(openSys == LOW && closeSys == HIGH && state == ' '){
    axisY.write('2');
    Serial.println("sysY open");
    state = '2';
  }else if(closeSys == LOW && openSys == HIGH && state == ' '){
    axisX.write('1');
    Serial.println("sysX close");
    state = '1';
  }

  if(axisY.read() == '1' && state == '1'){
    Serial.println("end of closing process");
    state = ' ';
  }
  else if(axisX.read() == '1' && state == '1'){
    axisY.write('1');
    Serial.println("sysX closed");
  }
  
  if(axisY.read() == '2' && state == '2'){
    axisX.write('2');
    Serial.println("sysY opened");
  }
  else if(axisX.read() == '2' && state == '2'){
    Serial.println("end of opening process");
    state = ' ';
  }
}
