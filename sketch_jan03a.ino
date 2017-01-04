//uno


#include <Stepper.h>
#include <Wire.h>

#include <Servo.h>

#define STEPS_PER_MOTOR_REVOLUTION 32   
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64
#define MOTOR 3
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 8, 10, 9, 11);
int  Steps2Take;
Servo myservo;

int r = 0;
int motorstatus=1;




void setup() {

  Wire.begin(8);                // join i2c bus with address #8

  Wire.onReceive(receiveEvent); // register event

  myservo.attach(7); 
 Stepper stepper(STEPS_PER_MOTOR_REVOLUTION, 8, 10, 9, 11);

 

  Serial.begin(115200);           // start serial for output

}



void loop() {

  delay(50);

   if(motorstatus==1){
 Steps2Take  = - STEPS_PER_OUTPUT_REVOLUTION ;  // Rotate CW 1 turn
  small_stepper.setSpeed(1000);   
  small_stepper.step(Steps2Take);
   }
   else if(motorstatus==0){
    Steps2Take  = - STEPS_PER_OUTPUT_REVOLUTION ;  // Rotate CW 1 turn
  small_stepper.setSpeed(0);   
  small_stepper.step(Steps2Take);
   }
}



// function that executes whenever data is received from master

// this function is registered as an event, see setup()

void receiveEvent(int howMany) {

   r = Wire.read(); // receive byte as a character

   Serial.print(r);         // print the character

   myservo.write(r); 
int x = Wire.read();    // receive byte as an integer
  if(x == 1){
    motorstatus=1;

  }
  else if(x == 0){
    motorstatus=0;

   delay(100);

}
}

