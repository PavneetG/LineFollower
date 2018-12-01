/*
Name: Pavneet Gill and Jonathan Sukhu 
 Date: 2017-06-02
 Description: This progams uses input from proximity sensors inorder to make the robot go forward on a track 
 */

//Initiating pins and Declaring variables for sensors
const int rightSensor =1; 
const int leftSensor = 2; 
const int middleSensor =3;

//declaring variable to calculate pid 
float Kp=0, Ki=0, Kd=0; 
float error=0, P=0, I=0, D=0, PIDValue=0; 
float previousError = 0, previous_I=0; 
int initialMotorSpeed=100; 

//declaring variable for mode
int mode; 
int counter =0;

//declaring array to store sensor value 
int sensorValue [3]; 

//Declaring pins for driving 
//const int SwitchPin = 3; //switch pin to reverse direction 
const int Motor1APin = 13; // 7 //backward motor pin 
const int Motor2APin = 12; // 6 //forward drive pin
const int Motor3APin = 7; // backward drive pin 
const int Motor4APin = 6; // forward drive pin
const int Enable12EPin = 9;//enable pin to allow the left motor to drive 
const int Enable34EPin = 10; // enable pin to allow the right motor to drive

void setup(){
  //pinMode(SwitchPin,INPUT);
  
  //iniaiting sensor pins as input 
  pinMode(rightSensor,INPUT);
  pinMode(leftSensor,INPUT); 
  pinMode(middleSensor,INPUT); 
  
  //intiating motor pins as output 
  pinMode(Motor1APin,OUTPUT);
  pinMode(Motor2APin,OUTPUT);
  pinMode(Motor3APin,OUTPUT);
  pinMode(Motor4APin,OUTPUT);
  pinMode(Enable12EPin,OUTPUT);
}

void loop (){
  readSensors (); 
  switch (mode) {
  case 0:
     if (counter == 0)
     {
     rotate (); 
     counter ++; 
     }
     else
     {
       rotate (); 
     }
     break;
  default: 
     calculatePID (); 
     motor_control (); 
  break;
  }
}
  
void readSensors ()
{
  //reading value of sensor and storing in an array 
  sensorValue [0] = digitalRead(leftSensor);
  sensorValue[1] = digitalRead(rightSensor); 
  sensorValue [2] = digitalRead (middleSensor);
  
  //checks all possiblities of sensor value 
   if((sensorValue[0] == 0) && (sensorValue [1] == 0) && (sensorValue [2] == 1))//if right and left sensor detect nothing
   {
     error = 0; 
   }
   else if((sensorValue[0] == 0) && (sensorValue [1] == 1) && (sensorValue [2] == 1)) //if right sensor detects black line
   {
     error = 1; 
   }
   else if((sensorValue[0] == 1) && (sensorValue [1] == 0) && (sensorValue [2] == 1)) //if left sensor detects black line
   {
     error = -1; 
   }
   else if((sensorValue[0] == 1) && (sensorValue [1] == 1) && (sensorValue [2] == 1)) // if all three sensors detect black line
   {
     mode = 0;  
   }
}

void calculatePID()
{
  P = error;
  I = I + error;
  D = error-previousError;
  PIDValue = (Kp*P) + (Ki*I) + (Kd*D);
  previousError = error;
}

void motor_control()
{
    // Calculating motor speed
    int leftMotorSpeed = initialMotorSpeed - PIDValue;
    int rightMotorSpeed = initialMotorSpeed + PIDValue;
    
    // constrain motor speed to not exceed PWM value
    constrain(leftMotorSpeed,0,255);
    constrain(rightMotorSpeed,0,255);
    
    //changing value of speed based on error
    analogWrite(Enable12EPin,initialMotorSpeed-PIDValue);   //Left Motor Speed
    analogWrite(Enable34EPin,initialMotorSpeed+PIDValue);  //Right Motor Speed
    
    //driving forward
    digitalWrite(Motor2APin,HIGH);
    digitalWrite(Motor1APin,LOW);
    digitalWrite(Motor3APin,LOW);
    digitalWrite(Motor4APin,HIGH);
}

void rotate()
{
  
}


