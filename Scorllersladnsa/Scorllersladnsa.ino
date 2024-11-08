// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int button1 = 8;
int button2 = 9;

void setup() {
  // set up the LCD's number of columns and rows:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(2,1);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
}

void loop() {
  // Print a message to the LCD.
  //lcd.setCursor(0,0);
  //lcd.print("hello, world!");

  //print(millis());
  scrollELeft(millis());
  moveUbutton();
  
}

int collU =7;
bool pressed = false;

void moveUbutton(){
  int b1State = digitalRead(button1);
  int b2State = digitalRead(button2);

  if(!b1State && !pressed){
    collU++;
    pressed = true;
    lcd.clear();
  }
  else if(!b2State && !pressed){
    collU--;
    pressed = true;
    lcd.clear();
  }
  else if(!b1State && !b2State)
    pressed = false;

  if(collU <= -1)
    collU = 15;
  else if(collU >= 16)
    collU = 0;

  lcd.setCursor(collU,1);
  lcd.print("e");
}

int position = 0;
boolean printed = false;
void scrollingMsg(int secsFor, String message, long millis){
  int secs = millis/1000;

  if(secs % secsFor == 0){
    if(position < message.length() && !printed){
      lcd.print(message.charAt(position));
      position++;
      printed = true;
    }
    else if(position >= message.length()){
      position = 0;
      //change
      lcd.clear();
    }
  }
  else
    printed = false;

  Serial.println(position);
  
}

void printPractice()
{
	lcd.setCursor(2,1);
	lcd.print("Robert");
	lcd.setCursor(1,0);
	lcd.print("Time: " + millis()/1000);
}

int collumn = 6;
long callTime;
void scrollELeft(long millis){
  //asign this at first call
  callTime = callTime == NULL? millis : callTime;

  if(millis >= callTime + 500){
    lcd.clear();
    collumn--;
    if(collumn == -1)
      collumn = 6;
    
    callTime = millis;
  }

  lcd.setCursor(collumn, 0);
  lcd.print("e");
}



