int G4 = 392 - 100;
int E4b = 311 - 100;
int B4b = 466 - 100;

int buzz = 11;

int led1 = 5;
int led2 = 3;
int led3 = 9;
int led4 = 10;



void setup() {
  // put your setup code here, to run once:
  pinMode(buzz, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  playMarch();

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
        if(tones[musicI] == G4){
          digitalWrite(led1, 1);
          digitalWrite(led2, 0);
          digitalWrite(led3, 0);
        }
        else if(tones[musicI] == E4b){
          digitalWrite(led1, 0);
          digitalWrite(led2, 1);
          digitalWrite(led3, 0);

        }
        else if(tones[musicI] == B4b){
          digitalWrite(led1, 0);
          digitalWrite(led2, 0);
          digitalWrite(led3, 1);
        }
      }
      else
      {
        noTone(buzz);
        digitalWrite(led1, 0);
        digitalWrite(led2, 0);
        digitalWrite(led3, 0);
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

void playMarch(){
  int hello[] = {G4,   0, G4,   0,   G4, E4b, B4b ,G4,   E4b, B4b, G4, 0};
  int durations[] = {950, 50, 950,50, 1000, 750, 250, 1000, 750, 250, 1000,1000};
  
  playTones(buzz, hello, durations, 12);

}

void song(){
  
}

