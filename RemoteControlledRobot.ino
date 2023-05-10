/**
	
**/


#include <IRremote.h>


const int PWM_M1 = 5;
const int IN1_M1 = 2;
const int IN2_M1 = 3;

const int PWM_M2 = 6;
const int IN1_M2 = 8;
const int IN2_M2 = 9;

const int IR_RECEIVE_PIN = 11;
const int IR_FEEDBACK_LED_PIN = 12;

int speed = 150;

int trigger_pin = 7;
int echo_pin = 10;
int buzzer_pin = 12; 
int time;
int distance; 

void setup(){
  Serial.begin(9600);
  Serial.println("Start");

  
  pinMode(PWM_M1,OUTPUT);
  pinMode(PWM_M2,OUTPUT);
  
  Serial.begin (9600); 
        pinMode (trigger_pin, OUTPUT); 
        pinMode (echo_pin, INPUT);
        pinMode (buzzer_pin, OUTPUT);
  
  pinMode(IN1_M1,OUTPUT);
  pinMode(IN2_M1,OUTPUT);
  
  pinMode(IN1_M2,OUTPUT);
  pinMode(IN2_M2,OUTPUT);
  pinMode(12,OUTPUT);
  IrReceiver.begin(IR_RECEIVE_PIN, true);
}

void loop(){
  if (IrReceiver.decode()) {

    switch(IrReceiver.decodedIRData.command){

      case 1://vol+
      forward();
      break;
      case 4://|<<
      turnRight();
      break;
      case 5://>||
      stop();
      break ;  
      case 6://>>|
      turnLeft();
      break ;               
      case 8://down arrow
      speedDown();
      break ;  
      case 9://vol-
      backward();
      break ;  
      case 10://up arrow
      speedUp();
      break ;  


    }
    IrReceiver.resume(); 
  }
  digitalWrite (trigger_pin, HIGH);
    delayMicroseconds (10);
    digitalWrite (trigger_pin, LOW);
    time = pulseIn (echo_pin, HIGH);
    distance = (time * 0.034) / 2;

  if (distance <= 10) 
        {
        Serial.println ("  Open ");
        Serial.print (" Distance= ");              
        Serial.println (distance);        
        digitalWrite (buzzer_pin, HIGH);
        delay (500);
        }
  else {
        Serial.println ("closed ");
        Serial.print (" Distance= ");              
        Serial.println (distance);        
        digitalWrite (buzzer_pin, LOW);
        delay (500);        
       } 
}



void forward(){
  Serial.println("forward");
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
  
  digitalWrite(IN1_M1, HIGH);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, HIGH);
  digitalWrite(IN2_M2, LOW);
}

void backward(){
  Serial.println("backward");
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
  
  digitalWrite(IN1_M1, LOW);
  digitalWrite(IN2_M1, HIGH);
  
  digitalWrite(IN1_M2, LOW);
  digitalWrite(IN2_M2, HIGH);
}

void turnLeft(){
  Serial.println("turnLeft");
  analogWrite(PWM_M1, 0);
  analogWrite(PWM_M2, speed);
  
  digitalWrite(IN1_M1, HIGH);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, HIGH);
  digitalWrite(IN2_M2, LOW);
}

void turnRight(){
  Serial.println("turnRight");
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, 0);
  
  digitalWrite(IN1_M1, HIGH);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, HIGH);
  digitalWrite(IN2_M2, LOW);
}

void stop(){
  Serial.println("stop");
  digitalWrite(IN1_M1, LOW);
  digitalWrite(IN2_M1, LOW);
  
  digitalWrite(IN1_M2, LOW);
  digitalWrite(IN2_M2, LOW);
}

void speedUp(){
  Serial.println("speedUp");
  speed+=10;
  if(speed>255) speed =255;
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
}

void speedDown(){
  Serial.println("speedDown");
  speed-=10;
  if(speed<0) speed =0;
  analogWrite(PWM_M1, speed);
  analogWrite(PWM_M2, speed);
}
