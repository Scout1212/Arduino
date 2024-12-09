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

LiquidCrystal lcd(2, 5, 10, 7, 6, 4);


//A binary number that keeps track of the current STATE of the LEDs.
byte currentState;

void setup() {
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
void loop() {
  //currentState = 0B10000000;
  //The left bit is the LCD side
  //the right bit is the button side 

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
void initialStateOfSR() {
  //allows us to edit
  digitalWrite(latchPin, LOW);

  //edits the shift register.
  //MSBFIRST Most Significant Bit first,  left to right
  //LSBFIRST Least Significant Bit first,  right to left
  shiftOut(dataPin, clockPin, MSBFIRST, currentState);

  //stops the editing.
  digitalWrite(latchPin, HIGH);
}

void checkComponents() {
  Serial.print(" p1 Up: ");
  Serial.print(digitalRead(buttonUp1));
  Serial.print(" p2 Up: ");
  Serial.print(digitalRead(buttonUp2));
  Serial.print(" p1 Down: ");
  Serial.print(digitalRead(buttonDown1));
  Serial.print(" p2 Down: ");
  Serial.println(digitalRead(buttonDown2));
  Serial.println(analogRead(poten));
  lcd.setCursor(0, 0);
  lcd.print("hello, world!");
}


int p1Power = 1;
bool pressed1 = false;
void p1PowerSet() {
  //Serial.println(p1Power);
  digitalRead(buttonUp1);
  if(digitalRead(buttonUp1) && p1Power < 9 && !pressed1) {
    p1Power++;
    pressed1 = true;
  } else if (digitalRead(buttonDown1) && p1Power > 1 && !pressed1) {
    p1Power--;
    pressed1 = true;
  }
  else if(!digitalRead(buttonUp1) && !digitalRead(buttonDown1)){
    pressed1 = false;
  }
}

int p2Power = 1;
bool pressed2 = false;
void p2PowerSet() {
  if (digitalRead(buttonUp2) && p2Power < 9 && !pressed2) {
    p2Power++;
    pressed2 = true;
  } else if (digitalRead(buttonDown2) && p2Power > 1 && !pressed2) {
    p2Power--;
    pressed2 = true;

  }
  else if(!digitalRead(buttonUp2) && !digitalRead(buttonDown2)){
    pressed2 = false;
  }
  Serial.println(p1Power);
}

int rate = 1000;
int direction = 1;
bool changed = false;

void oscilate() {
  double b = (2 * PI) / (rate);
  int shiftBy = (direction * -3.5 * cos(b * timeFromHit(false, 0)) + 3.5) + .5;


  currentState = 0B00000001 << shiftBy;

  if(currentState == 0B00000001 && !changed) {
    changed = true;
    //tone(buzz, 400);
    rate = 1000 * p1Power;
    direction  = 1;
    timeFromHit(true, 0);
  } else if (currentState == 0B10000000 && !changed) {
    changed = true;
    //tone(buzz, 400);
    rate = 1000 * p2Power;
    direction = -1;
    timeFromHit(true, 0);
  } else if (currentState != 0B00000001 && currentState != 0B10000000)
    changed = false;
  else {

    noTone(buzz);
  }

  digitalWrite(latchPin, LOW);                          //allows us to edit       //MSBFIRST MOST Sig Bit first,  left to right
  shiftOut(dataPin, clockPin, MSBFIRST, currentState);  //LSBFIRST Least Sig Bit first,  RIGHT to left
  digitalWrite(latchPin, HIGH);                         //stop editing
}

int timesLastCall[] = {-1, -1};
//pass true to define a new time;
//this is so each side, the sin graph starts at 0
//called in oscillate
long timeFromHit(bool newTime, int index) {
  long time = millis();
  if (newTime || timeLastCall[timesLastCall] == -1)
    timesLastCall[index] = time;

  return millis() - timesLastCall[timesLastCall];
}

long futureCooldown;
long futureWindow;
boolean heldBack;


/*
 * swingSensor: Checks if the tilt sensor was swung.
 * Parameters --> tiltSensor, window (in milliseconds)
 * Returns --> int that indicates that sensor was swung
 *             0 = Rest    1 = Held Back    2 = Swung
 *
 */
static int swingSensor(int tiltSensorFront, int tiltSensorBack, int window)
{
  //Declaring output
  int output;

  //Time setup
  long now = millis();

  //State of sensors
  int tiltStateFront = digitalRead(tiltSensorFront);
  int tiltStateBack = digitalRead(tiltSensorBack);

  //detecting position of the paddle
  if((tiltStateFront && tiltStateBack))
  {
      output = 0;
      //Serial.println("At rest");
  }
  else if(!tiltStateFront && tiltStateBack)
  {
    output = 1;
    heldBack = true;
    //Serial.println("Held back");
  }
  else if(tiltStateFront && !tiltStateBack && heldBack)
  {
    output = 2;
    futureCooldown = now + window;
    heldBack = false;
    //Serial.println("Swung");
  }
  else if(tiltStateFront && !tiltStateBack && !heldBack)
  {
    //Making the paddle automatically revert to "at rest"
    //after window amount of time has passed
    if(now >= futureCooldown)
    {
      output = 0;
    }
    else
    {
      output = 2;
    }
  }
  //Returning output
  return output;
}


//conceptually this is bad --> i need to check for early swings
//im gonna need a boolean to check which side its on to start registering what side its on
//im gonna need to call checkSide outside of the binary checks 


//true is player1
bool player1PlaceHolder;
bool started = false;
int window = 1000;
void checkSide(bool side){
  int front;
  int back;
  int swing = 
  if(Side){
    front = p1Front;
    back = p1Back;
  }
  else{
    front = p2Front;
    back = p2Back;
  }

  if(!started)
    timelastCall(true, 1);

  if(timeFromStart >= 100){
    if(swingSensor(front, back, window) ==  2){
      return true;
      started = false;
    }
  }
  else
    started = false;

  return false;
}
