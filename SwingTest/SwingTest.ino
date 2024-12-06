
int tilt = 13;
int tilt2 = 12;
int led = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(tilt, OUTPUT);
  pinMode(tilt2, pinMode);
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led, swing(millis()));
}

bool primed;
bool success;
int callTime;

bool swing(long milli){
  if(!digitalRead(tilt)){
    primed = true;
  }
  if(primed && digitalRead(tilt2)){
    primed = false;
    success = true;
  }

  if(success){
    callTime = milli;
    if(callTime <= millis + 500){
      return true;
    }
    else
      success = false;
  }
  
  return false;
  //test with light
}