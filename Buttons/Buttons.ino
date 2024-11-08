// C++ code
//
int button1 = 12;
int button2 = 11;
int led1 = 3;
int led2 = 2;
int led3 = 4;
long futureLED;

void setup()
{
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  futureLED = 0;
}

void loop()
{
  //state(1);
  //checkButton();

  //toggleBlink2Buttons(led1, millis());

  //controlBrightness();
  //toggleLED1Button();

  //cycle(millis());
  //stopCyclingLED(millis());

  //manuallyCycle();

  blinkOnOff();
}

void turnOnWhenHeld(){
  digitalWrite(led1, digitalRead(button1));
  digitalWrite(led2, digitalRead(button2));  
}


/*
void toggleLED2Buttons(){
  if(digitalRead(button1))
    stat = 1;
  else if(digitalRead(button2))
    stat = 0;
  digitalWrite(led1, stat);
}
*/

void blink(int led, long millis){
  int seconds = millis/1000;
  digitalWrite(led, seconds%2 == 0? 0:1);
}


int stat = 0;
void toggleBlink2Buttons(int led, long millis){

  if(digitalRead(button1))
    stat = 1;
  else if(digitalRead(button2))
    stat = 0;

  if(stat){
    blink(led1, millis);
  }
  else{
    digitalWrite(led, 0);
  }
}

void state(int a){
  digitalWrite(led1, a);
  digitalWrite(led2, a);
  digitalWrite(led3, a);
}

int checkButton(){
  int b1State = digitalRead(button1);
  int b2State = digitalRead(button2);
  Serial.print("b1State = ");
  Serial.print(b1State);
  Serial.print(" b2State = ");
  Serial.println(b2State);
}

int brightness = 0;
bool pressed = false;

void controlBrightness(){
  int b1State = digitalRead(button1);
  int b2State = digitalRead(button2);

  if(b1State && brightness < 255 && !pressed){
    brightness += 5;
    pressed = true;
  }
  else if(b2State && brightness > 0 && !pressed){
    brightness -= 5;
    pressed = true;
  }
  else if(!b2State && !b1State)
    pressed = false;
  Serial.println(brightness);

  analogWrite(led1, brightness);

}


bool stats = false;
bool prossed = false;

void toggleLED1Button(){
  int b1State = digitalRead(button1);  

  if(b1State && !prossed){
    stats = !stats;
    prossed = true;
  }
  else if(!b1State)
    prossed = false;
  digitalWrite(led1, stats);
}

int stap = 0;
bool prissed = false;

void cycle(long millis){
  int b1State = digitalRead(button1); 


  if(b1State && !prissed){
    prissed = true;
    if(stap < 2){
      stap++;
    }
    else
      stap = 0;
  }
  else if(!b1State)
    prissed = false;

  if(stap == 0){
    digitalWrite(led1, 0);
  }
  else if(stap == 1){
    digitalWrite(led1, 1);
  }
  else if(stap == 2){
    blink(led1, millis);
  }
}


bool playing = true;
bool prushed = false;

double savedStat = 0;

void stopCyclingLED(long millis){
  int b2State = digitalRead(button2); 

  /*
    if(b1State)
      isCycling = true;
    else if(b2State)
      isCycling = false;
    

    if(isCycling)
  */

  if(b2State && !prushed){
    playing = !playing;

    if(playing)
      futureLED = millis;
    prushed = true;
  }
  else if(!b2State)
    prushed = false;

  if(playing){
    if(millis >= futureLED + 1000)
    {
      futureLED = millis;
      //update the LED
      savedStat++;
    }

    int pattern = (int)savedStat % 3;

    Serial.println(savedStat);
    int led1b = pattern == 0? 1:0;
    int led2b = pattern == 1? 1:0;
    int led3b = pattern == 2? 1:0;

    digitalWrite(led1, led1b);
    digitalWrite(led2, led2b);
    digitalWrite(led3, led3b);
  }
}

int num = 0;
bool prosshed = false;

void manuallyCycle(){
  int pattern;
  int b2State = digitalRead(button2); 


  if(b2State && !prosshed){
    num++;
    Serial.println("prssed");
    prosshed = true;
  }
  else if(!b2State)
    prosshed = false;

  pattern = num % 3;

  Serial.println(num);

  int led1b = pattern == 0? 1:0;
  int led2b = pattern == 1? 1:0;
  int led3b = pattern == 2? 1:0;

  digitalWrite(led1, led1b);
  digitalWrite(led2, led2b);
  digitalWrite(led3, led3b);
}


bool pressed1 = false;
bool pressed2 = false;

bool standby = false;
bool blinking = false;

void blinkOnOff(){
	//first button = standby
	//second button = activate
  int b1State = digitalRead(button1);
  int b2State = digitalRead(button2);

  if(b1State && !pressed1){
    standby = !standby;
    pressed1 = true;
  }
  else if(!b1State)
    pressed1 = false;

 

  if(standby && b2State && !pressed2){
    pressed2 = true;
    blinking = !blinking;
  }
  else if(!b2State){
    pressed2 = false;
  }
  
  if(!standby)
    blinking = false;
  
  if(blinking){
    blink(led1, millis());
  }
  else if(standby){
    digitalWrite(led1, 1);
  }
  else
    digitalWrite(led1, 0);

  Serial.println(blinking);
}

