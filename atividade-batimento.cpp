int batimentos = 0;

void setup() {

  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  batimentos = analogRead(A0);
  Serial.println(batimentos);
  
  digitalWrite(13, HIGH);
  delay(batimentos);
  digitalWrite(13, LOW);
  delay(batimentos);
  
  if(batimentos < 341) {
    digitalWrite(7,HIGH);
  } else {
      digitalWrite(7,LOW);
  }
}

