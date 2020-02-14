// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Author - Chinmay Manchanda 
// Runs the Automated Robot
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Global Variables
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 

                                                              // "AFMotor.h" is a library availaible on arduino website which contains 
#include <AFMotor.h>                                          // some predefined functions to control the DC motors with the L239D 
#include <Servo.h>              // Add library
Servo name_servo;               // Define any servo name


                                                              // Motor Shield.
const int trigPin = A3;
const int echoPin = A4;                                       // Defines pins numbers for the Ultra sonic distance sensor

long duration;                                                // defines variables for the calculation of distance
int distance;

char currentDirection = 's';                                  // Initialize the current direction to 's' which means 'stop'.

AF_DCMotor m1(1);               // Initializing DC motor for the first wheel.
AF_DCMotor m2(2);
AF_DCMotor m3(3);               // Initializing DC motor for the second wheel.
AF_DCMotor m4(4);    
// Initializing DC motor for the rotation of Ultrasonic distance sensor ( UDS ).

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Function: Receive Byte
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
char receiveCommand(){
   
  char command = 0;
  if(Serial.available()>0){                              // This if statement takes in a condition which makes it work 
                                                         // if there's an input from the serial monitor. It takes the input 
    // Read the oldest byte in the serial buffer:        // and returns it as a command for further actions.
    command = Serial.read();
    
  }

  return command;

}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Function: Update Direction
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
char updateDirection(char command){

  char f,b,l,r,s;                        // Initializing a few varialble's which stand as follows. || f = forward || b = backward || l = left || r = right || s = stop ||
                                         // Two functions are called in the following if statements which are included in the "AFMotor.h", namely "m1.run() and m2.run()". These functions set the direction of the DC motor to either forward or backward.
    if (command == 'f') {
      
      m1.run(FORWARD);                   //  This if statement comes into action if the input to the function
      m2.run(FORWARD);  
      m4.run(FORWARD);                   //  is 'f' and this part sets both the wheels in forward direction
      Serial.println("Forwards");        //  which in a way sets the robot's direction to forward direction.
      
    }
    if (command == 'b') {
      
      m1.run(BACKWARD);                  //  This if statement comes into action if the input to the function
      m2.run(BACKWARD);
      m4.run(BACKWARD);                  //  is 'b' and this part sets both the wheels in backward direction 
      Serial.println("Backwards");       //  which in a way sets the robot's direction to backward direction.

    }
    if (command == 'l') {
      
      m1.run(BACKWARD);                  //  This if statement comes into action if the input to the function is 'l'
      m2.run(FORWARD);
      m4.run(FORWARD);                   //  and this part sets the left wheel to backward direction and the right wheel
      Serial.println("Turn Left");       //  to forward direction which makes the robot turn left.
    
    }
    if (command == 'r') {
    
      m1.run(FORWARD);                   //  This if statement comes into action if the input to  the function is 'r'
      m2.run(BACKWARD);
      m4.run(FORWARD);                   //  and this part sets the right wheel to backward direction and the left wheel 
      Serial.println("Turn Right");      //  to forward direction which makes the robot turn right.

    }
    if (command == 's') {
      
      m1.setSpeed(0);                    //  This if statement comes into action if the input to
      m2.setSpeed(0);
      m4.setSpeed(0);                    //  the function is 's' and this part sets the motor speed to
      Serial.println("Stop");            //  '0' which stops the robot from moving.

    }

}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Function: Update Speed
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int updateSpeed(char command){           // This function takes in the command input as numbers starting from '1' uptill '4' and works to set the motor speed.
                                         // Two functions are called in the following if statements which are included in the "AFMotor.h", namely "m1.setSpeed() and m2.setSpeed()". These functions set the speed of the DC motor ranging from 0 to 256.
  if (command == '1') {

    Serial.println("Speed 25%");         
    m1.setSpeed(64);                     // Sets the speed of wheel 1 to 64.
    m2.setSpeed(64);
    m4.setSpeed(64);                     // Sets the speed of wheel 2 to 64.
  
  }
  if (command == '2') {
  
    Serial.println("Speed 50%");
    m1.setSpeed(128);                    // Sets the speed of wheel 1 to 128.
    m2.setSpeed(128);                    // Sets the speed of wheel 2 to 128.
    m4.setSpeed(128);
    
  }
  if (command == '3') {
  
    Serial.println("Speed 75%");         
    m1.setSpeed(192);                    // Sets the speed of wheel 1 to 192.
    m2.setSpeed(192);                    // Sets the speed of wheel 2 to 192.
    m4.setSpeed(192);
  
  }
  if (command == '4') {
  
    Serial.println("Speed 100%");
    m1.setSpeed(255);                    // Sets the speed of wheel 1 to 256.
    m2.setSpeed(255);                    // Sets the speed of wheel 2 to 256.
    m4.setSpeed(255);
  }

}  
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int servoRotate(char dir) {

  int servo_position;                          

   
    if( dir == 'l' ){
    
        for (servo_position = 70; servo_position <=180; servo_position +=1){
    
            name_servo.write(servo_position);
            delay(10);
        }
    }
  if(dir == 's'){
    
    for (servo_position=180; servo_position >= 70; servo_position -=1){
  
        name_servo.write(servo_position);
        delay(10);
    }
  }
}
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// Function: Read Distance with Ultra Sonic Sensor
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int readPing() {                         // This functions reads the ultrasonic sensor distance.
    
  digitalWrite(trigPin, LOW);            // Clears the trigPin
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);           // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);     // Reads the echoPin, returns the sound wave travel time in microseconds
  
  distance= duration*0.034/2;            // Calculating the distance

  return distance;                       

}


// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// The setup() method runs once, when the sketch starts
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void setup(){ 
  
  Serial.begin(9600);                                          // Initialize the serial communications

  Serial.println("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");        // Print the program details
  Serial.println("Program: R2R Test Program"); 
  Serial.println("Initializing ...");
  
 
  Serial.println("Initialization complete");                   // Initialization completed successfully
  Serial.println("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

  pinMode(trigPin, OUTPUT);                                    // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);                                     // Sets the echoPin as an Input

  name_servo.attach (10); 
  servoRotate('s');

  delay(5000);
  updateDirection('f');                                    // update the direction to forward and speed to 3
  updateSpeed('3');                                          // so that the robot moves in forward direction when it starts.


}

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// The loop() method runs over and over again
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void loop(){

  char command = 0;                                 // Initialization of few varialbles which will be used during the void loop().
  int curr_dist = 0;                                // This variable stores the current distance or the distance when the sensor faces front.
  int curr_left_dist = 0;                           // This variable stores the current distance when the sensor faces left.
  int curr_right_dist = 0;                          // This variable stores the current distance when the sensor faces right.
  
  
  curr_dist = readPing();                           // Calling the readPing() function to sense the distance from the obstacle in front.
  Serial.println(curr_dist);

 
  if(curr_dist < 35){                               // This 'if' statement comes into action if the distance between the robot and the obstacle is less than 20 cms.
  
    updateDirection('s');                             // Calling the updateDirection() function to make the robot stop.
    
    servoRotate('l');
   
    curr_left_dist = readPing();                    // Reading and storing the distance between the obstacle and robot and storing it in curr_left_distance while the sensor is facing left.

    servoRotate('s');
    
    if(curr_left_dist > 40){         // This 'if' statement comes into action if the distance between the obstacle and the robot is more on the left side.
    
        updateDirection('l');                         // If the distance on left is more than on right , then it's safe to move in the left direction and here we 
        updateSpeed('3');                             // are updating the speed to '3' and the direction to 'left' which makes the robot turn left.
  
        delay(2000);                                // After a delay of 1 second while turning left
  
        updateDirection('f');                         // We update the direction to 'forward' ('f') and the speed to 3
        updateSpeed('3');                             // so that the robot can now go forward on it's path.
      
      }
      else{
                                                    // If the distance on right is more than on left , then it's safe to move in the right direction and here we
        updateDirection('r');                         // are updating the speed to '3' and the direction to 'right' which makes the robot turn right.
        updateSpeed('3');
           
        delay(2000);                                // After a delay of 1 second while turning right
        
        updateDirection('f');                         // We update the direction to 'forward' ('f') and the speed to 3
        updateSpeed('3');                             // so that the robot can now go forward on it's path.
  
      }

   }

}
  
/*
  delay(3000);
  m1.run(FORWARD);
  m2.run(BACKWARD);
  m4.run(BACKWARD);

  m1.setSpeed(255);
  m2.setSpeed(255);
  m4.setSpeed(255);

  delay (500);
  
  m1.setSpeed(0);
  m2.setSpeed(0);
  m4.setSpeed(0);
*/

/*

  delay(1000);
  m1.run(FORWARD);
  m2.run(FORWARD);
  m3.run(BACKWARD);
  m4.run(BACKWARD);

  
  
  m1.setSpeed(255);
  m2.setSpeed(255);
  m3.setSpeed(255);
  m4.setSpeed(255);

  
  */
  
    
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
