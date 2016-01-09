 #include <Servo.h>
#include <LiquidCrystal.h>

#define brake 0
#define forward 1
#define backward 2
#define frontleft 3
#define frontright 4
#define backleft 5
#define backright 6



 char incomingByte;
int speedvalue=200; //INITIAL SPEED VALUE
int *speedpointer=&speedvalue; // Pointer pointing to speedvalue's address

  //NORMAL I/O Ports
  const int ledPin1 = 22;    //Normal I/O PORT
  const int motor1Pin = 24;    // H-bridge leg 1 (pin 2, 1A)
  const int motor2Pin = 25;    // H-bridge leg 2 (pin 7, 2A)
  const int motor3Pin = 26;    // H-bridge leg 3 (pin 10, 3A)
  const int motor4Pin = 27;    // H-bridge leg 4 (pin 15, 4A)
  //PWM PORTS
  const int enablePin1 = 2;   // H-bridge enable pin2
  const int enablePin2= 3;
  //LCD screen
  const int rw =6;
  const int enable =7;
  const int d4 = 8;
  const int d5 = 9;
  const int d6 = 10;
  const int d7 = 11;
  
  LiquidCrystal lcd(rw,enable,d4,d5,d6,d7);





void setup(){
    // Setting up pins for perpherials
 
    pinMode(ledPin1, OUTPUT); 
   
 
    
    // setting pins for H bridge DC motor Control
    pinMode(motor1Pin, OUTPUT); 
    pinMode(motor2Pin, OUTPUT);  
    pinMode(motor3Pin, OUTPUT); 
    pinMode(motor4Pin, OUTPUT); 
    pinMode(enablePin1, OUTPUT);
   pinMode(enablePin2, OUTPUT);
    // Starting serial communications at the set bit rate
    Serial.begin(9600);
    
 lcd.begin(16, 2);
   //start the H bridge by writing it in high mode.
digitalWrite(enablePin1, HIGH); 
 digitalWrite(enablePin2, HIGH); 

}

void loop(){
  radio_communication();


}


void move(unsigned int direction,int speed){
  
  analogWrite(enablePin1,speed);
  analogWrite(enablePin2,speed);
  switch (direction){
    case frontright:// moves right
   
      
      digitalWrite(motor1Pin, LOW);   
      digitalWrite(motor2Pin, HIGH);
      digitalWrite(motor3Pin, HIGH);   
      digitalWrite(motor4Pin, LOW);    
      break;
  
  
      case frontleft: // moves left
    
    
      digitalWrite(motor1Pin, HIGH);   
      digitalWrite(motor2Pin, LOW);
      digitalWrite(motor3Pin, LOW);   
      digitalWrite(motor4Pin, HIGH);  
    break;
    
 
  
  case forward:// moves straight

 
     digitalWrite(motor1Pin, HIGH);   
      digitalWrite(motor2Pin, LOW);
      digitalWrite(motor3Pin, HIGH);   
      digitalWrite(motor4Pin, LOW);  
      
       break;
    
  
  
  case backward: // moves reverse
  
   
     digitalWrite(motor1Pin, LOW);   
      digitalWrite(motor2Pin, HIGH);
      digitalWrite(motor3Pin, LOW);   
      digitalWrite(motor4Pin, HIGH);  
    break;
 
  
    
  case backright: // goes in reverse right
 
     
      digitalWrite(motor1Pin, HIGH);   
      digitalWrite(motor2Pin, LOW);
      digitalWrite(motor3Pin, LOW);   
      digitalWrite(motor4Pin, HIGH);    
  break;
  
  case backleft:// goes in reverse left

   
      digitalWrite(motor1Pin, LOW);   
      digitalWrite(motor2Pin, HIGH);
      digitalWrite(motor3Pin, HIGH);   
      digitalWrite(motor4Pin, LOW);  
  break;
  
  case brake: // stops the motors
  
    
     digitalWrite(motor1Pin, LOW);   
      digitalWrite(motor2Pin, LOW);
      digitalWrite(motor3Pin, LOW);   
      digitalWrite(motor4Pin, LOW);  
  break;
  
   default:// stops the motors
 
 
     digitalWrite(motor1Pin, LOW);   
      digitalWrite(motor2Pin, LOW);
      digitalWrite(motor3Pin, LOW);   
      digitalWrite(motor4Pin, LOW);  
  break;
  
}
}
void radio_communication(){  // START COMMUNICATIONS
lcd.clear();
lcd.print("Standby Mode");
lcd.setCursor(0,1);
lcd.print("Speed:");
lcd.print(speedvalue*100/255);
lcd.print("%");
//Default: no buttons pressed robot doesn't move
move(brake,0);

if (Serial.available() > 0) {  // If any data is comming in read it.

incomingByte = Serial.read();  //Incomming data is recieved as characters from a keyboard


// w - go forward
if (incomingByte == 'w'){
move(forward,*speedpointer);
LED_Display();
lcd.clear();
lcd.setCursor(0, 0); // top left
lcd.print("Moving Forward");
lcd.setCursor(0,1);
lcd.print("Speed:");
lcd.print(speedvalue*100/255);
lcd.print("%");
delay(2000);
}
// a - go left
else if (incomingByte == 'a'){
move(frontleft,*speedpointer);
LED_Display();
lcd.clear();
lcd.print("Moving left");
lcd.setCursor(0,1);
lcd.print("Speed:");
lcd.print(speedvalue*100/255);
lcd.print("%");
delay(8000);
}
//d - go right
else if (incomingByte == 'd'){
move(frontright,*speedpointer);
LED_Display();
lcd.clear();
lcd.print("Moving Right");
lcd.setCursor(0,1);
lcd.print("Speed:");
lcd.print(speedvalue*100/255);
lcd.print("%");
delay(8000);
}
// go reverse s
else if (incomingByte == 's'){
move(backward,*speedpointer);
LED_Display();
lcd.clear();
lcd.print("Moving Backward");
lcd.setCursor(0,1);
lcd.print("Speed:");
lcd.print(speedvalue*100/255);
lcd.print("%");
delay(2000);
}
else if (incomingByte == 'e')//decrease speed
{
  speedvalue-=25;
  if(*(speedpointer)<0)
  speedvalue=0;
}
else if (incomingByte='r'){//increase speed
  speedvalue+=25;
  if(*(speedpointer)>=250)
  speedvalue=255;
}
}
}

void LED_Display(){
  digitalWrite(ledPin1, HIGH);
  delay(50);
  digitalWrite(ledPin1, LOW);
}

