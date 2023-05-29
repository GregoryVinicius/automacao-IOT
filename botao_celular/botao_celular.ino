int leitura = 0;

int ReadUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delay(2);
  digitalWrite(triggerPin, HIGH);
  delay(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  int cm = (int)(0.01723 * (double)pulseIn(echoPin, HIGH));
}

void setup()
{
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  leitura = ReadUltrasonicDistance(4, 2);
  Serial.println(leitura);
  
  if(leitura > 34){
    //apaga os LEDs se necessário
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    digitalWrite(14, LOW);
  }
  
  if(leitura > 25 & leitura < 35){
    //apaga os LEDs se necessário
    digitalWrite(14, LOW);
    digitalWrite(13, LOW);
    
    digitalWrite(12, HIGH);
    tone(13, 495, 100);
  }
  
  if(leitura > 15 & leitura < 26){
    //apaga os LEDs se necessário
    digitalWrite(14, LOW);
    
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    tone(13, 396, 100);
  }
  
  if(leitura < 16){

    digitalWrite(14, HIGH);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    tone(13, 330, 100);
  }
  
  delay(100);
}