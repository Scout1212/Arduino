//The 3 pins that control the Shift Register
int latchPin;
int clockPin;
int dataPin;

int g4 = 392;
int a4 = 440;
int f4 = 349;
int e4 = 330;

//A binary number that keeps track of the current STATE of the LEDs.
byte currentState;

void setup() 
{
  Serial.begin(9600);
  latchPin = 8;
  clockPin = 12;
  dataPin = 11;
  
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  //This initializes the LEDs to their starting value, it should be 
  //an 8 bit BINARY number.  Where each bit corresponds to an LED.
  //0 means OFF and 1 means ON.
  currentState = 0B00000000;

  initialStateOfSR();
}
void loop() 
{
  challenge(millis());

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
/*
  turnOnLED():
  Given an ledNum from 0 to 7 turn on a specific LED from the 
  shift register.  Otherwise displays an error message 
 */
void turnOnLED(int ledNum)
{
  //Checking to see if they entered a valid ledNum
  if(ledNum >= 0 && ledNum <= 7)
  {       
    //set a binary number to 00000001

    //byte bin = 0B00000001;
    
    
    //shift it to the correct position

    //bin = bin << ledNum;
    
    
    //change the correct bit in the currentState to on.
    //currentState |= bin;
    

    //Update the currentState
    

    //Turn on the LEDs

    currentState |= 0B00000001 << ledNum;
    digitalWrite(latchPin, LOW);//allows us to edit       //MSBFIRST MOST Sig Bit first,  left to right
    shiftOut(dataPin, clockPin, MSBFIRST, currentState);  //LSBFIRST Least Sig Bit first,  RIGHT to left
    digitalWrite(latchPin, HIGH);//stop editing

  }
  else
  {
    Serial.println("Cant turn on: Invalid LED");
  }
}

/*
 * updateShiftRegister():
 * This method will allow use to turn on or off a specific LED
 * led: is the LED that you are choosing.  Should be an int from 0 to 7.
 * state:  represents what you want to do with LED.  HIGH means ON and LOW means OFF.
 */
void updateShiftRegister(int led, int state)
{
  if(state == HIGH)
    turnOnLED(led);
  else
    turnOffLED(led);
}
/*
  turnOffLED():
  Given an ledNum from 0 to 7, turn OFF a specific LED from the 
  shift register.  Otherwise displays an error message 
 */
void turnOffLED(int ledNum)
{
  if(ledNum >= 0 && ledNum <= 7)
  {  
    //Getting a hold of the bit at ledNum to see if it is even on or not.
    byte copy = currentState;
    byte copyShift = copy >> ledNum;
    byte theBit = copyShift%2;
    
    //printing the Bit for testing
    //Serial.print("theBit = ");
    //Serial.println(theBit);

    //Checking if the bit is on and we need to turn it off
    if(theBit == 1)
    {
      //hold the previous state, for saftey.  Not needed
      byte hold = currentState;
      
      //set a binary number to 00000001
      byte binary = 1;
    
      //shift it to the correct possition
      byte shifted = binary << ledNum;

      //Update the state by using the shifted binary number
      byte updatedState = shifted ^ hold;//XOR,

      //Turn on the LEDs
      currentState = updatedState;
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, currentState);
      digitalWrite(latchPin, HIGH);
    }
    else
    {
      Serial.print("turnOff() LED: ");
      Serial.print(ledNum);
      Serial.println(", is already off");
    }
  }
  else
  {
    Serial.println("Cant turn OFF: Invalid LED");
  }
}

void practice(long mili){
  long halfSec = mili / 500;
  int pattern = halfSec %4;
  if(pattern == 0)
    currentState = 0B11111111;
  else if(pattern == 1)
    currentState = 0B01010101;
  else if(pattern == 2)
    currentState = 0B10101010;
  else
    currentState = 0B00000000;
  updateRegister();
}

void challenge(long milli){
  int newState = 0B00000001;
  int changeBy = abs(7*sin(milli*(PI/8000))) + .5;
  currentState = newState << changeBy;

  updateRegister();
}

void updateRegister(){
  digitalWrite(latchPin, LOW);//allows us to edit       //MSBFIRST MOST Sig Bit first,  left to right
  shiftOut(dataPin, clockPin, MSBFIRST, currentState);  //LSBFIRST Least Sig Bit first,  RIGHT to left
  digitalWrite(latchPin, HIGH);//stop editing
}

