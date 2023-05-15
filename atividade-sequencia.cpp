int luz = 12;
void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop()
{
  if(luz >= 11 && luz <= 13)
  {
    delay(100);
    if(!digitalRead(2))
    {
      digitalWrite(luz, LOW);
      if(luz > 11){
      luz--;
	  digitalWrite(luz, HIGH);
      }else if(luz <= 11){
        digitalWrite(luz, HIGH);
      }
    }
    if(!digitalRead(4)){
      delay(100);
      digitalWrite(luz, LOW);
      if(luz <13){
        luz++;
        digitalWrite(luz, HIGH);
      }else if(luz >= 13){
        digitalWrite(luz, HIGH);
      }
    
    }
  }
}
