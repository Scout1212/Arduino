int redLed;
int yellowLed;
int greenLed;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  redLed = 13;

  greenLed = 2;

  yellowLed = 8;



  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sec = millis()/1000;
  greenLedPattern(sec);
  redLedPattern(sec);
  yellowLedPattern(sec);
}

void greenLedPattern(int sec){
  int pattern = sec%6;

  if(pattern < 5)
    digitalWrite(greenLed, LOW);
  else
    digitalWrite(greenLed, HIGH);
}

void yellowLedPattern(int sec){
  int pattern = sec % 6;

  if(pattern > 3)
    digitalWrite(yellowLed, LOW);
  else if(pattern == 3)
    digitalWrite(yellowLed, HIGH);
  else if(pattern == 4)
    digitalWrite(yellowLed, LOW);
  else if(pattern == 5)
    digitalWrite(yellowLed, HIGH);
}

void redLedPattern(int sec){
  int pattern =  sec % 2;
  if(pattern == 0)
    digitalWrite(redLed, LOW);
  else
    digitalWrite(redLed,HIGH);

}