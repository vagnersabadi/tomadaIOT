

void calc() {

  float valor    = 0;
  int i = 0;
  float media = 0;
  float tensao = 0;

  while (i < 100) {// le X valores para calcular uma media
    valor = (5.0 * analogRead(A0)) / 1023;// regra de 3 5V —– 1023 X —– Valor Obtido
    media += valor;//armazena media
    i++;//incremento while
  }
  media /= 100;//faz a media 

  tensao = (245 * media) / 5;//calcula tensao maxima(V) * media leitura sensor / 5V

  if (tensao < 90)//se indentificar tensao abaixo de 90v entende-se por desligada
  {
    tensao = 0;
  }
  Serial.print("Tensao: ");
  Serial.println (tensao);

  delay(2000);
}
void setup() {
  pinMode(0, INPUT);
  Serial.begin(9600);
}

void loop() {
  calc();
}
