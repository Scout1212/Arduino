//The 3 pins that control the Shift Register
#include <LiquidCrystal.h>

int latchPin;
int clockPin;
int dataPin;

int p1Front = A1;
//int p1Back = 13;
//int p2Front = 3;
int p2Back = 9;

int buttonUp1 = A5;
int buttonDown1 = A4;
int buttonUp2 = A3;
int buttonDown2 = A2;
int poten = A0;
int buzz = 9;

//0 serving, 1 first after serve, 2 is in game, 3 is game over
int gameState = 0;



//temp 

int p2Button = 13;
int p1Button = 3;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

LiquidCrystal lcd(2, 5, 10, 7, 6, 4);

int direction = 1;
bool success = false;

//A binary number that keeps track of the current STATE of the LEDs.
byte currentState;

long timesLastCall[] = {-1, -1, -1};

void setup(){
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

  pinMode(p1Front, INPUT);
  //pinMode(p1Back, INPUT);
  //pinMode(p2Front, INPUT);
  //temp
  pinMode(p1Button, INPUT);
  pinMode(p2Button, INPUT);

  pinMode(p2Back, INPUT);
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
  //p2 == 0B10000000;
  //p1 == 0B00000001;
  //direction = 1 -> p2

  //Serial.println(gameState);

  if(gameState == 0){
    currentState = 0B00000001;
    updateShiftRegister();
    if(digitalRead(p1Button) && timeFromHit(false, 2) >= 500){
      //Serial.println("Hello1");
      gameState = 1;
      direction = 1;
      timeFromHit(true, 0);
    }
  }
  else if(gameState == 1 || gameState == 2){
    p1PowerSet();
    p2PowerSet();
    oscilate();

  }

  //Serial.println(digitalRead(p1Button));

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

int p1Power = 8;
bool pressed1 = false;
void p1PowerSet() {
  //Serial.println(p1Power);
  digitalRead(buttonUp1);
  if(digitalRead(buttonUp1) && p1Power < 9 && !pressed1) {
    p1Power++;
    pressed1 = true;
  } else if (digitalRead(buttonDown1) && p1Power > 2 && !pressed1) {
    p1Power--;
    pressed1 = true;
  }
  else if(!digitalRead(buttonUp1) && !digitalRead(buttonDown1)){
    pressed1 = false;
  }
}

int p2Power = 8;
bool pressed2 = false;
void p2PowerSet() {
  if (digitalRead(buttonUp2) && p2Power < 9 && !pressed2) {
    p2Power++;
    pressed2 = true;
  } else if (digitalRead(buttonDown2) && p2Power > 2 && !pressed2) {
    p2Power--;
    pressed2 = true;

  }
  else if(!digitalRead(buttonUp2) && !digitalRead(buttonDown2)){
    pressed2 = false;
  }
  Serial.println(p2Power);
}

int rate = 1000;
bool changed = false;

void oscilate() {
  double b = (2 * PI) / (rate);
  int shiftBy = (direction * -3.5 * cos(b * timeFromHit(false, 0)) + 3.5) + .5;

  currentState = 0B00000001 << shiftBy;
  if(gameState == 2){
    if(currentState == 0B00000001 && !changed) {
      changed = true;
      //tone(buzz, 400);
      rate = 1000 * p1Power;
      direction  = 1;
      timeFromHit(true, 0);
      checkSide(true);
      Serial.println("hello2");
    } 
    else if (currentState == 0B10000000 && !changed){
      //start
      changed = true;
      //tone(buzz, 400);
      rate = 1000 * p2Power;
      direction = -1;
      timeFromHit(true, 0);
      checkSide(true);
    } 
    else if (currentState != 0B00000001 && currentState != 0B10000000){
      changed = false;
      checkSide(false);
    }
    else {
      noTone(buzz);
    }
  }
  else if(currentState != 0B00000001 && currentState != 0B10000000 && gameState == 1){
    gameState = 2;
  }

  updateShiftRegister();
}

void updateShiftRegister(){
  digitalWrite(latchPin, LOW);                          //allows us to edit       //MSBFIRST MOST Sig Bit first,  left to right
  shiftOut(dataPin, clockPin, MSBFIRST, currentState);  //LSBFIRST Least Sig Bit first,  RIGHT to left
  digitalWrite(latchPin, HIGH);                         //stop editing
}


//pass true to define a new time;
//this is so each side, the sin graph starts at 0
//called in oscillate
long timeFromHit(bool newTime, int index) {
  long time = millis();
  if (newTime || timesLastCall[index] == -1)
    timesLastCall[index] = time;

  return millis() - timesLastCall[index];
}
long futureCooldown;
long futureWindow;
bool heldBack;


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

void reset(int index){
  timesLastCall[index] = -1;
}

//todo --> make an input start ball movement and suspend loss.

//true is player1
bool player1PlaceHolder;
bool started = false;
int window = 2000;
void checkSide(bool lastLed){
  //Serial.println(success == 1? "success": "");
  if(success)
    return;
  if(!lastLed)
    success = false;
  
  if(direction == -1 && digitalRead(p1Button) && !lastLed){
    timeFromHit(true, 2);
    gameState = 0;
  }
  else if(direction == 1 && digitalRead(p2Button) && !lastLed){
    timeFromHit(true, 2);
    gameState = 0;
  }

  int button = direction == -1? p1Button : p2Button;
  //something with time probably
  if(lastLed){
    if(!started){
      timeFromHit(true, 1);
      started = true;
      return;
    }
  }
  else{
    //Todo maybe scale scale off of speed
      if(timeFromHit(false, 1) <= 3000){
        if(digitalRead(button)){
          started = false;
          success = true;
          return;
        }
      }
      else{
        //Serial.println("hello");
        reset(1);
        started = false;
        gameState = 0;
      }
    }
  }

