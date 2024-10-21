void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println("Hello World");
  Serial.print("The ");
  Serial.print("month ");
  Serial.println("is ");
  Serial.println("September.");

  //Declaring and assigning an int to represent the current year.

  int year = 2024;
  //displaying the year with an appropriate label.      

  Serial.println(year);
  //Declare an int to represent your age

  int age;
  //assigning the int with your age.
  
  age = 16;
  //Displaying your age in a full sentence.
  Serial.print("I am ");
  Serial.println(age);
  //declare and assign a boolean stating if it is raining today.

  bool rain = false;
  //Displaying if it is raining or not

  Serial.println(rain);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Eastchester");
  //Serial.println("High School");
  //Serial.print("Ar");
  //Serial.println("duino");
  //Serial.println("Super");
  //Serial.println("Hero");
  //Serial.println("Evil");
  //Serial.print("Villian");
}
