int buzzer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  buzzer = 11;
  pinMode(OUTPUT, 11);


}

void loop() {
  // put your main code here, to run repeatedly:

  buzzerRange(millis());

  //buzzerTesting(millis());

  //londonBridge(millis());

}

void buzzerRange(int millis){
  long changer = 300*sin(millis*(PI/1000)) + 600;
  long freq = 166*sin(millis*(PI/100)) + 377 + changer;
  tone(buzzer, freq);
}

void buzzerTesting(long milli){
  int second = milli/1000;
	int pattern = second%4;
	

	if(pattern == 0)
		tone(buzzer, 261.63);
	else if(pattern < 3)
		tone(buzzer, 293.66);
	else
		noTone(buzzer);
}

void londonBridge(long millis){
  int halfSecond = millis/500;
  int pattern = halfSecond % 8;

  if(pattern == 0 || pattern == 2 || pattern == 6)
    tone(buzzer, 392.00);
  else if(pattern == 1)
    tone(buzzer, 440.00);
  else if(pattern == 3 || pattern == 5)
    tone(buzzer, 349.23);
  else if(pattern == 4)
    tone(buzzer, 329.63);
  else
    noTone(buzzer);

}


