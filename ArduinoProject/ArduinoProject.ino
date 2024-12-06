//The 3 pins that control the Shift Register
#include <LiquidCrystal.h>

int latchPin;
int clockPin;
int dataPin;

int tilt1 = A1;
int tilt2 = 13;
int tilt3 = 3;
int tilt4 = 9;

int buttonUp1 = A5;
int buttonDown1 = A4;
int buttonUp2 = A3;
int buttonDown2 = A2;
int poten = A0;
int buzz = 9;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

LiquidCrystal lcd(   2,  5,10, 7, 6, 4);


//A binary number that keeps track of the current STATE of the LEDs.
byte currentState;

void setup() 
{
  Serial.begin(9600);
  latchPin = 8;
  clockPin = 12;
  dataPin = 11;

  pinMode(buttonUp1, INPUT);
  pinMode(buttonUp2, INPUT);
  pinMode(buttonDown2, INPUT);
  pinMode(buttonDown1, INPUT);
  pinMode(poten, INPUT);
  pinMode(buzz, OUTPUT);
  
  pinMode(tilt1, INPUT);
  pinMode(tilt2, INPUT);
  pinMode(tilt3, INPUT);
  pinMode(tilt4, INPUT);
  pinMode(poten, INPUT);
  
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  currentState = 0B00000000;

  initialStateOfSR();
  
  lcd.begin(16, 2);
  
}
void loop() 
{
  p1PowerSet();
  p2PowerSet();
  
  oscilate();
  //checkComponents();
}
/*
 * initialStateOfSR():  
 * This method turns on or off the LEDs connected to the shift register
 * based off of the byte currentState.
 */
void initialStateOfSR()
{
  //allows us to edit 
  digitalWrite(latchPin, LOW);      

  //edits the shift register.
  //MSBFIRST Most Significant Bit first,  left to right
  //LSBFIRST Least Significant Bit first,  right to left
  shiftOut(dataPin, clockPin, MSBFIRST, currentState);  

  //stops the editing.
  digitalWrite(latchPin, HIGH);
}

void checkComponents(){
  Serial.print(" p1 Up: ");
  Serial.print(digitalRead(buttonUp1));
  Serial.print(" p2 Up: ");
  Serial.print(digitalRead(buttonUp2));
  Serial.print(" p1 Down: ");
  Serial.print(digitalRead(buttonDown1));
  Serial.print(" p2 Down: ");
  Serial.println(digitalRead(buttonDown2));
  Serial.println(analogRead(poten));
  lcd.setCursor(0,0);
  lcd.print("hello, world!");
}


int p1Power = 1;

void p1PowerSet(){
  if(buttonUp1 && p1Power < 9){
    p1Power++;
  }
  else if(buttonDown1 && p1Power > 1){
    p1Power--;
  }
}

int p2Power = 1;

void p2PowerSet(){
  if(buttonUp2 && p2Power < 9){
    p2Power++;
  }
  else if(buttonDown2 && p2Power > 1){
    p2Power--;
  }
}

int rate = 1;
int direction = 1;

void oscilate(){
  //Serial.println(timeFromHit(false));
  double b = (2*PI)/(rate);
  //why is it .00
  //Serial.println(b);

  //multiply the graph by a negative to change the side started on
  //trace shiftBy;
  int shiftBy = (direction*-3.5*cos(b*timeFromHit(false)+3.5)) + .5;

  
  currentState = 0B00000001 << shiftBy;
  //Serial.println(currentState);
  Serial.println(shiftBy);
  if(currentState == 0B00000001)
    {
      //tone(buzz, 400);
      rate = 1000*p1Power;
      direction *= -1;
      timeFromHit(true);
    }
  else if (currentState == 0B10000000){
    //tone(buzz, 400);
    rate = 1000*p2Power;
    direction *= -1;
    timeFromHit(true);
  }
  else{
    noTone(buzz);
  }

  digitalWrite(latchPin, LOW);//allows us to edit       //MSBFIRST MOST Sig Bit first,  left to right
  shiftOut(dataPin, clockPin, MSBFIRST, currentState);  //LSBFIRST Least Sig Bit first,  RIGHT to left
  digitalWrite(latchPin, HIGH);//stop editing
}

int timeLastCall = -1;
//pass true to define a new time;
//this is so each side, the sin graph starts at 0
//called in oscillate
long timeFromHit(bool newTime){
  long time = millis();
  if(newTime || timeLastCall == -1)
    timeLastCall = time;
  
  return millis() - timeLastCall;
}
