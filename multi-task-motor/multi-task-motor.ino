#include <Thread.h>
#include <ThreadController.h>
Thread worker1 = Thread();
Thread worker2 = Thread();

#define CLK_A 13
#define CW_A 12
#define EN_A 11
#define LIMIT_L_A 9
#define LIMIT_R_A 10
#define CLK_B 6
#define CW_B 7
#define EN_B 8
#define LIMIT_L_B 5
#define LIMIT_R_B 4

int rotationA = 0;
int rotationB = 0;
char command = '0';
void motorStepA( int MAX){

   for(int x = 0; x < MAX; x++) {
        digitalWrite(CLK_A,HIGH);
        delayMicroseconds(100);
        digitalWrite(CLK_A,LOW);
        delayMicroseconds(100);
      }
}
void motorStepB( int MAX){

   for(int x = 0; x < MAX; x++) {
        digitalWrite(CLK_B,HIGH);
        delayMicroseconds(100);
        digitalWrite(CLK_B,LOW);
        delayMicroseconds(100);
      }
}

void task1(){
  int limit_l = digitalRead(LIMIT_L_A);
  int limit_r = digitalRead(LIMIT_R_A);
  if(limit_l == LOW && command == '1'){
    digitalWrite(CW_A, LOW);
    motorStepA(4000);
    command = '0';
    rotationA = 1;   
  }else if(limit_r == LOW && command == '2'){
    digitalWrite(CW_A , HIGH); //ccw     
    motorStepA(4000);  
    command = 0;
    rotationA = 1;
  }else if(limit_l == LOW){
    motorStepA(0); 
    rotationA = 0;
  }else if(limit_r == LOW){
    motorStepA(0); 
    rotationA = 0;
  }
  else if(rotationA == 1 ) motorStepA(1);
  
  
}
void task2(){
  int limit_l = digitalRead(LIMIT_L_B);
  int limit_r = digitalRead(LIMIT_L_B);
  if(limit_l == LOW && command == '1'){
    digitalWrite(CW_A, HIGH);
    motorStepB(4000);
    command = '0';
    rotationB = 1;   
  }else if(limit_r == LOW && command == '2'){
    digitalWrite(CW_B , LOW); //ccw     
    motorStepB(4000);  
    command = 0;
    rotationB = 1;
  }else if(limit_l == LOW){
    motorStepB(0); 
    rotationB = 0;
  }else if(limit_r == LOW){
    motorStepB(0); 
    rotationB = 0;
  }
  else if(rotationA == 1 ) motorStepB(1);
}

ThreadController controller = ThreadController();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  worker1.onRun(task1); worker1.setInterval(0);
  worker2.onRun(task2); worker2.setInterval(0);
  controller.add(&worker1);
  controller.add(&worker2);

  pinMode(CLK_A,OUTPUT);
  pinMode(CW_A,OUTPUT);
  pinMode(LIMIT_L_A, INPUT_PULLUP);
  pinMode(LIMIT_R_A, INPUT_PULLUP);

  pinMode(EN_A,OUTPUT);
  digitalWrite(EN_A,LOW);
  digitalWrite(CW_A,LOW);

  pinMode(CLK_B,OUTPUT);
  pinMode(CW_B,OUTPUT);
  pinMode(LIMIT_L_B, INPUT_PULLUP);
  pinMode(LIMIT_R_B, INPUT_PULLUP);

  pinMode(EN_B,OUTPUT);
  digitalWrite(EN_B,LOW);
  digitalWrite(CW_B,HIGH);
}

void loop() {
  
  if(Serial.available()){
    command = Serial.read();  
  }
  controller.run();
  command = '0';
}
