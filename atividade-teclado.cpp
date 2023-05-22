void setup()
{
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(4, OUTPUT);
}

void loop()
{
  if (!digitalRead(7)) {
    tone(4 , 264, 100);
  }
  if (!digitalRead(6)) {
    tone(4 , 297, 100);
  }
  if (!digitalRead(5)) {
    tone(4 , 330, 100);
  }
}
