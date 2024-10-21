int green;
int blue;
int red;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  red = 3;
  blue = 11;
  green = 9;

  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);

  analogWrite(green, 100);

}

void loop() {
  // put your main code here, to run repeatedly:
  long mili = millis();
  //rgbTest(mili);

  //analogWrite(red, 255);
  //analogWrite(green, 255);
  //analogWrite(blue, 255);

  //rainbow(mili);

  colorCycle();

}

void rgbTest(int milis){
  int sec = milis/1000;
  int pattern = sec%4;
  int redB = pattern == 0? 255: 0;
  int greenB = pattern == 1? 255: 0;
  int blueB = pattern == 2? 255: 0;

  analogWrite(red, redB);
  analogWrite(green, greenB);
  analogWrite(blue, blueB);

}

void rainbow(int milli){
  int sec = milli/1000;
  int pattern = sec%7;

  int redb;
  int blueb;
  int greenb;

  if(pattern == 0){
    redb = 255;
    greenb = 0;
    blueb = 0;
  }
  else if(pattern == 1){
    redb = 255;
    greenb = 165;
    blueb = 0;
  }
  else if(pattern == 2){
    redb = 255;
    greenb = 255;
    blueb = 0;
  }
  else if(pattern == 3){
    redb = 0;
    greenb = 255;
    blueb = 0;
  }
  else if(pattern == 4){
    redb = 0;
    greenb = 255;
    blueb = 165;
  }
  else if(pattern == 5){
    redb = 0;
    greenb = 0;
    blueb = 255;
  }
  else if(pattern == 6){
    redb = 128;
    greenb = 0;
    blueb = 128;
  }

  analogWrite(red, redb);
  analogWrite(blue, blueb);
  analogWrite(green, greenb);


}

void colorCycle(){
  long redB = 127.5*sin((PI/1500)*millis()) + 127.5;
  analogWrite(red, redB);
}
