
//http://autocorerobotica.blog.br/aprenda-utilizar-o-sensor-de-tensao-com-arduino/

int leitura;  //Variável para leitura da porta analógica

float volts; //Armazenar o cálculo
float somatorio = 0; //somatorio para fazer a media
float media; //Armazenar o cálculo media
int i=1; //variavel i;

void setup(){
  Serial.begin(9600);
}

void loop(){
  delay(2000);  
  while(i<3){
    volts = ((analogRead(A3)*0.0489)*5);
    Serial.println("Sua tensao eh de : ");  
    Serial.println(volts);
    Serial.println();
    somatorio = somatorio + volts;
    i++;
  } 
  delay(1000);
  
  media = somatorio/i;
  Serial.println();
  Serial.println("Media de tensao eh de: ");
  Serial.println(media);
  Serial.println();
  i = 0;  //zerando o i
  media = 0; //zerando a media
  somatorio=0;  //zerando o somatorio
}
