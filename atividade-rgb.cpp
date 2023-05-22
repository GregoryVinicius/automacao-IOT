void setup()
{
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

}

void loop()
{
  int step = 10;
  for(int azul = 0; azul <= 255; azul+= step){
    for(int vermelho = 0; vermelho <=255; vermelho+= step){
      for(int verde = 1; verde <= 255; verde+= step){
        analogWrite(5, azul);
        analogWrite(3, verde);
        analogWrite(6, vermelho);
        delay(100);
      }
    }
  }
}
