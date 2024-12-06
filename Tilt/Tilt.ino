int button = 2;
int tilt = 7;
int led = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(button, INPUT);
  pinMode(tilt, INPUT);
  pinMode(led, OUTPUT);

}


void loop() {
  // put your main code here, to run repeatedly:  
  buttonThenTilt(millis());
  

}

bool state = false;
long timeCall = -1;
void buttonThenTilt(long milli){
  //capacitor 
  if(digitalRead(button) && !digitalRead(tilt)){
    state = true;
    timeCall = milli;
  }
  else if(state && !digitalRead(tilt) && timeCall + 1000 < milli)
    state = false;

  digitalWrite(led, state);
}
