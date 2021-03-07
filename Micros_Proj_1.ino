const int red = 31;
const int green = 33;
const int yellow = 35;
const int buzz = 37;
const int button = 39;
void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

while( digitalRead(button) == 0)
{
  digitalWrite(red, HIGH);
  delay(500);
  digitalWrite(red, LOW);
  delay(500);
}

while(true){
  digitalWrite(red, HIGH);
  delay(12000);
  for(int i=0; i < 3; i++){
    digitalWrite(buzz, HIGH);
    delay(500);
    digitalWrite(buzz, LOW);
    delay(500);
  }

  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  delay(12000);
  for(int i=0; i < 3; i++){
    digitalWrite(buzz, HIGH);
    delay(500);
    digitalWrite(buzz, LOW);
    delay(500);
  }

  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  for(int i=0; i < 3; i++){
    digitalWrite(buzz, HIGH);
    delay(500);
    digitalWrite(buzz, LOW);
    delay(500);
  }
  digitalWrite(yellow, LOW);
}
}
