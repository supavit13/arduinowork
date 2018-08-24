#define CLK 13
#define CW 12
#define EN 11
#define LIMIT_L 9
#define LIMIT_R 10
int rotation = 0;
void setup() {

  Serial.begin(9600);
  pinMode(CLK,OUTPUT);
  pinMode(CW,OUTPUT);
  pinMode(LIMIT_L, INPUT_PULLUP);
  pinMode(LIMIT_R, INPUT_PULLUP);

  pinMode(EN,OUTPUT);
  digitalWrite(EN,LOW);
  digitalWrite(CW,LOW);

}

void loop() {
    char command = '0';
    if(Serial.available()){
      command = Serial.read();
//      Serial.println(command);
    }
    
    int limit_l = digitalRead( LIMIT_L);
    int limit_r = digitalRead( LIMIT_R);
    
    if( limit_l == LOW && command == '1'){
        digitalWrite(CW,LOW); //cw;
        motorStep(4000);
        command = 0;
        rotation = 1;
    }else if(limit_r == LOW && command == '2'){
        digitalWrite(CW , HIGH); //ccw     
        motorStep(4000);  
        command = 0;
        rotation = 1;
    }else if(limit_l == LOW){
        motorStep(0); 
        rotation = 0;
    }else if(limit_r == LOW){
        motorStep(0); 
        rotation = 0;
    }
    else if(rotation == 1 ) motorStep(1);

}
void motorStep( int MAX){

   for(int x = 0; x < MAX; x++) {
        digitalWrite(CLK,HIGH);
        delayMicroseconds(100);
        digitalWrite(CLK,LOW);
        delayMicroseconds(100);
      }
}
