#include <Wire.h>


// ================================================================
// ===                         DEFINES                          ===
// ================================================================
#define MOTOR_R_P 3
#define MOTOR_R_A 4
#define MOTOR_R_B 5

#define MOTOR_L_P 9
#define MOTOR_L_A 7
#define MOTOR_L_B 8

#define SONIC_L_T 10
#define SONIC_L_E 11
#define SONIC_R_T 12
#define SONIC_R_E 13



#define SPEED 185
#define DANGER_DISTANCE 30

#define DEBUG 1

// ================================================================
// ===                       FUNCTIONS                          ===
// ================================================================


//****************Motors****************
void motor_right(char dir,int power){
  if(dir=='f'){
    digitalWrite(MOTOR_R_A,HIGH);
    digitalWrite(MOTOR_R_B,LOW);
  }else{
    digitalWrite(MOTOR_R_A,LOW);
    digitalWrite(MOTOR_R_B,HIGH);
  }
  analogWrite(MOTOR_R_P,power);
}

void motor_left(char dir,int power){
  if(dir=='f'){
    digitalWrite(MOTOR_L_A,HIGH);
    digitalWrite(MOTOR_L_B,LOW);
  }else{
    digitalWrite(MOTOR_L_A,LOW);
    digitalWrite(MOTOR_L_B,HIGH);
  }
  analogWrite(MOTOR_L_P,power);;
}

void forward(int power){
  motor_right('f',power);
  motor_left('f',power);
}

void backward(int power){
  motor_right('b',power);
  motor_left('b',power);
}


int get_r_distance(){
  digitalWrite(SONIC_R_T, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONIC_R_T, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(SONIC_R_E, HIGH);
  // Calculating the distance
  int distance = duration*0.034/2;
  return distance;
}

int get_l_distance(){
  digitalWrite(SONIC_L_T, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONIC_L_T, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(SONIC_L_E, HIGH);
  // Calculating the distance
  int distance = duration*0.034/2;
  return distance;
}


void clear(){
  digitalWrite(SONIC_R_T, LOW);
  digitalWrite(SONIC_L_T, LOW);
  delayMicroseconds(2);
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //set serial monitor baud rate to match

  pinMode(SONIC_L_T, OUTPUT);
  pinMode(SONIC_L_E, INPUT);

  pinMode(SONIC_R_T, OUTPUT);
  pinMode(SONIC_R_E, INPUT);
  
  Serial.println("Reading...");
   
}

void loop() {
  // put your main code here, to run repeatedly:
  clear();


  
  int left_distance = get_l_distance();
  int right_distance = get_r_distance();

  
  if(DEBUG){
      Serial.print("\r\nLeft: ");
      Serial.print(left_distance);
      Serial.print("\t\tRight: ");
      Serial.print(right_distance);
  }

  
  if(left_distance < DANGER_DISTANCE && right_distance < DANGER_DISTANCE){
    backward(SPEED);
    delay(500);
    motor_right('f',SPEED);
    motor_left('b',SPEED);
    delay(250);
  }else if(left_distance < DANGER_DISTANCE ){
    motor_right('f',SPEED);
    motor_left('b',SPEED);
    delay(250);
  }else if(right_distance < DANGER_DISTANCE ){
    motor_right('b',SPEED);
    motor_left('f',SPEED);
    delay(250);
  }
  motor_right('f',SPEED);
  motor_left('f',SPEED);
  
}







