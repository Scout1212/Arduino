int redLed;
int blueLed;
int greenLed;

void setup() {
  Serial.begin(9600);
  redLed = 13;

  greenLed = 2;

  blueLed = 8;



  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  
  digitalWrite(redLed, 1);
  digitalWrite(blueLed, HIGH);
  digitalWrite(greenLed, HIGH);
  
  delay(500);
    
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, LOW);
  digitalWrite(greenLed, LOW);

}

void loop() {
  offOn(redLed);
  offOn(blueLed);
  offOn(greenLed);

}

void offOn(int port){
  	digitalWrite(port, HIGH);
  	delay(1000);
  	digitalWrite(port, LOW);
  	delay(1000);
  }
