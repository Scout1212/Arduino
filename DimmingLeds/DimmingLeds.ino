int led1;
int led2;
int led3;

void setup() {
  // put your setup code here, to run once:
  led1 = 11;
  led2 = 9;
  led3 = 3;

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  // int mili = millis();

  // int timeUnit = mili/2;

  // int pattern =  timeUnit % 255;

  // analogWrite(led1, pattern);
  // analogWrite(led2, pattern + 255 * (1/3));
  // analogWrite(led3, pattern + 255 * (2/3));

  // delay(1);

  int mili = millis();

  //brightToDim(led1, mili);
  curvedDim(led2);
  curvedDim(led1);
  curvedDim(led3);


  
}

void brightToDim(int led, int millis){
  int lastMilli = 0;
  bool inc = true;
  int brightness = lastMilli == 0? 0: brightness;
  if(millis - lastMilli == 200){
    if(inc){
      brightness++;
      inc = brightness == 255? false: true;
    }
    else{
      brightness--;
      inc = brightness == 0;
    }

    lastMilli = millis;
  }
  
  analogWrite(led, brightness);
}

void curvedDim(int led){
  int brightness = 127.5*sin((PI/1500)*millis())+127.5;

  analogWrite(led, brightness);
}
