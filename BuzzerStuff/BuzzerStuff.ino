int buzzer;
int a4 = 440;
int f4 = 349;
int e4 = 329;
int G4 = 392;

int led1 = 5;
int led2 = 3;
int led3 = 9;
int led4 = 10;


G4, 0, G4, 0, G4, E4b, B4b , G4, E4b, B4b, G4, 0

void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  buzzer = 11;
  pinMode(11, OUTPUT);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //buzzerRange(millis());

  playLondonBridge2();

  state(1);

  

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


/**
 * playTones:  Plays an array of tones.  
 * Each for a specified duration.
 * The Arduino can do something else while calling this method.
 * 
 * Precondtions:  1)  tones and durations have the same number of elements
 *                2)  elements of durations are in milliseconds
 *                3)  length is the length of tones and durations
 */
void playTones(int buzz, int tones[], int durations[], int length){
  if(sizeof(tones)/sizeof(int) == sizeof(durations)/sizeof(int))
  {
    long sum = 0;
    for(int i = 0; i<length;i++)
    {
      sum += durations[i];
    }
    //calculate which index we should be working with
    int musicI = 0;
    for(musicI = 0; millis()%sum>=sumUntil(durations,musicI,length);musicI++)//super bananas
    {    }
    if(millis()%sum<sumUntil(durations,musicI,length))    //bananas
    {
      if(tones[musicI]!= 0)
      {
        tone(buzz, tones[musicI]);
        if(tones[musicI] == g4){
          digitalWrite(led1, HIGH);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
        }
        else if(tones[musicI] == f4){
          digitalWrite(led1, LOW);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
        }
        else if(tones[musicI] == e4){
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, LOW);
        }
        else if(tones[musicI] == a4){
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, HIGH);
        }
      }
      else
      {
        noTone(buzz);
      }
    }
  }
}
/**
 * sumUntil:  returns the sum of all the values from 0 to index 
 * inside of arr
 * This is a helper method for playTones
 * 
 * Precondtions:  1)  0<=index<=length-1
 *                2)  length is the length of arr
 */
long sumUntil(int arr[], int index,int length)
{
  long sum = 0;
  for(int i = 0;i<=index;i++)
  {
    sum+=arr[i];
  }
  return sum;
}

void playImperialDeathMarch(){
  
  int list[] = {G4, 0, G4, 0, G4, E4b, B4b , G4, E4b, B4b, G4, 0};

  int durs[] = {500, 500, 500, 500, 500, 500, 500,500};

  playTones(buzzer, list, durs, 8);
}

void state(int a){
  digitalWrite(led1, a);
  digitalWrite(led2, a);
  digitalWrite(led3, a);
  digitalWrite(led4, a);

}

