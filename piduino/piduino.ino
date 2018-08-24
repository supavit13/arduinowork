#include <Wire.h>
#include <DS1307.h>

DS1307 clock;
RTCDateTime dt;

int motorPin1 = 4;// Blue   - 28BYJ48 pin 1

int motorPin2 = 5;// Pink   - 28BYJ48 pin 2

int motorPin3 = 6;// Yellow - 28BYJ48 pin 3

int motorPin4 = 7;// Orange - 28BYJ48 pin 4

int motorPin5 = 10;// Blue   - 28BYJ48 pin 1

int motorPin6 = 11;// Pink   - 28BYJ48 pin 2

int motorPin7 = 12;// Yellow - 28BYJ48 pin 3

int motorPin8 = 13;// Orange - 28BYJ48 pin 4

int motorSpeed = 100;     //variable to set stepper speed

char statemachine = '0';

char axis = 'x';
char val = '0';
int timedelay = 0;
long prev_time = 0;
void setup() {

  
  pinMode(motorPin1, OUTPUT);

  pinMode(motorPin2, OUTPUT);

  pinMode(motorPin3, OUTPUT);

  pinMode(motorPin4, OUTPUT);

  pinMode(motorPin5, OUTPUT);

  pinMode(motorPin6, OUTPUT);

  pinMode(motorPin7, OUTPUT);

  pinMode(motorPin8, OUTPUT);

  pinMode(3, INPUT);
  pinMode(2, INPUT);
  
  clock.begin();
  if (!clock.isReady())
  {
    clock.setDateTime(__DATE__, __TIME__);
  }
  Serial.begin(9600);
  Serial.println("Start");
  


}

void loop(){
  int limitSW1 = digitalRead(3);
  int limitSW2 = digitalRead(2);
  dt = clock.getDateTime();
  
  String temptime = clock.dateFormat("U", dt);
  long timer = temptime.toInt();
 if(val == 's' && statemachine == '0' && limitSW1 == 1){
    val = '1';
  }
   Serial.print(val);
   Serial.println(statemachine);
 if (Serial.available())

  {

    val = Serial.read();

    Serial.println(val);

  }

  if (val == '1'){

      
      clockwise('0');     

  }

    if (val == '2'){

      counterclockwise('0');    

  }             

    if (val == '0'){

  digitalWrite(motorPin1, LOW);

  digitalWrite(motorPin2, LOW);

  digitalWrite(motorPin3, LOW);

  digitalWrite(motorPin4, LOW);

  }      

}

void counterclockwise (char mode){

  // 1

  digitalWrite(motorPin1, HIGH);

  digitalWrite(motorPin2, LOW);

  digitalWrite(motorPin3, LOW);

  digitalWrite(motorPin4, HIGH);

  delay(motorSpeed);

  // 2

  digitalWrite(motorPin1, HIGH);

  digitalWrite(motorPin2, HIGH);

  digitalWrite(motorPin3, LOW);

  digitalWrite(motorPin4, LOW);

  delay (motorSpeed);

  // 3

  digitalWrite(motorPin1, LOW);

  digitalWrite(motorPin2, HIGH);

  digitalWrite(motorPin3, HIGH);

  digitalWrite(motorPin4, LOW);

  delay(motorSpeed);

  // 4

  digitalWrite(motorPin1, LOW);

  digitalWrite(motorPin2, LOW);

  digitalWrite(motorPin3, HIGH);

  digitalWrite(motorPin4, HIGH);

  delay(motorSpeed);

}

void clockwise(char mode){

 // 1

  digitalWrite(motorPin1, LOW);

  digitalWrite(motorPin2, LOW);

  digitalWrite(motorPin3, HIGH);

  digitalWrite(motorPin4, HIGH);

  delay(motorSpeed);

  // 2

  digitalWrite(motorPin1, LOW);

  digitalWrite(motorPin2, HIGH);

  digitalWrite(motorPin3, HIGH);

  digitalWrite(motorPin4, LOW);

  delay (motorSpeed);

  // 3

  digitalWrite(motorPin1, HIGH);

  digitalWrite(motorPin2, HIGH);

  digitalWrite(motorPin3, LOW);

  digitalWrite(motorPin4, LOW);

  delay(motorSpeed);

  // 4

  digitalWrite(motorPin1, HIGH);

  digitalWrite(motorPin2, LOW);

  digitalWrite(motorPin3, LOW);

  digitalWrite(motorPin4, HIGH);

  delay(motorSpeed);

}
