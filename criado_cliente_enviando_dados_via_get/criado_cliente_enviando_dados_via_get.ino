#include <SPI.h>
#include <UIPEthernet.h>

byte mac[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };//endereço mac

IPAddress ip(192, 168, 0, 101); //seta o ip fixo

EthernetServer server(1000); //porta do servidor, pois ele vai ser o server
EthernetClient cliente;

byte servidor[] = { 192 , 168 , 0 , 166 };            //Servidor JAVA

int val;

void setup()
{
  //iniciar o servidor, passa o mac e o ip fixo, da pra passar só mac, que ai vai te dar um ip por DHCP
  // deve seguir a sequencia Ethernet.begin(mac, ip, dns, gateway, subnet);
  Ethernet.begin(mac, ip);
  server.begin();

  //visualizar info da placa
  Serial.begin(9600);
  Serial.print("IP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("Mascara : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS-ServerIP: ");
  Serial.println(Ethernet.dnsServerIP());
  pinMode(7, OUTPUT);
}

void loop()
{
 digitalWrite(7, HIGH);


  /***converte os valores em string e os concatena no metodo GET para envialos ao servidor***/

  String ENVIA = "GET /?ID=1";
  //ENVIA.concat(id);
  ENVIA.concat("&VOLTS=");
  ENVIA.concat(random(300));
  ENVIA.concat("&CORRENTE=");
  ENVIA.concat(( 5.0 * analogRead(A5) * 100.0) / 1024.0);
  //ENVIA.concat("&TEMPERATURA");
  //ENVIA.concat(( 5.0 * analogRead(A5) * 100.0) / 1024.0);
  
  //ENVIA = "GET /?ID=1@1&VOLTS=219&CORRENTE=0,1123&TEMPERATURA=20";

  if (cliente.connect(servidor, 8080)) {
    Serial.println("CONECTADO...");

    cliente.print(ENVIA);
    cliente.println(" HTTP/1.1");

    cliente.println("Host: www.google.com");
    cliente.println("Connection: close");
    cliente.println();
  } else {
    Serial.println("ERRO NA CONEXAO...");
    digitalWrite(7, LOW);
    delay(1000);
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
    delay(1000);
    digitalWrite(7, HIGH);
  }

  delay(1000);
  cliente.stop();

  /***Verifica se existe robo conectado e sua acao***/

  // verifica as conexões recebidas
  EthernetClient client = server.available();
  long time = millis();

  if (client) // se tiver cliente conectado
  {
    boolean currentLineIsBlank = true;
    String linha;

    while (client.connected()) // em quanto o cliente estiver conectado
    {
      if (client.available())
      {
        char c = client.read(); //Variável para armazenar os caracteres que forem recebidos
        linha.concat(c); // Pega os valor após o IP do navegador ex: 192.168.1.2/0001

        // Recebeu dois caracteres de fim de linha (\ n). O cliente terminou
        // envio do pedido.
        if (c == '\n' && currentLineIsBlank)
        {
          // Enviar um cabeçalho de resposta HTTP padrão
          // IMPORTANTE, ISSO FAZ O ARDUINO RECEBER REQUISIÇÃO AJAX DE OUTRO SERVIDOR E NÃO APENAS LOCAL.
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/javascript");
          client.println("Access-Control-Allow-Origin: *");
          client.println();

          int iniciofrente = linha.indexOf("?");

          if (iniciofrente > -1) { //verifica se existe comando

            iniciofrente  = iniciofrente + 6; // pega o caracter seguinte
            int fimfrente = iniciofrente + 3; //espera 3 caracteres

            String acao   = linha.substring(iniciofrente, fimfrente); //pega o valor do comando

            if (acao == "001") {
              digitalWrite(7, HIGH);
              val = 1;
            }
            else if (acao == "002") {
              digitalWrite(7, LOW);
              val = 0;
            }
            else {}

            client.print("dados({ rele : ");
            client.print(val);
            client.print(" })");
            client.print("Temperatura");
            client.println(( 5.0 * analogRead(A5) * 100.0) / 1024.0);
          }
          break;

          break; // fim da transmissão
        }

        // Se o cliente enviou um caractere de fim de linha (\ n),
        // eleve a bandeira e veja se o próximo caractere é outro
        // caractere de fim de linha
        if (c == '\n')
        {
          currentLineIsBlank = true;
        } else if (c != '\r')
        {
          currentLineIsBlank = false;
        }


        // Se o cliente envia um caractere que não é um caractere de fim de linha,
        // redefinir o sinalizador e aguarde o caractere de fim de linha.
        else if (c != '\r')
        {
          currentLineIsBlank = false;
        }----
      }
    }

  }
  // tempo pro navegador receber os dados
  delay(1);

  // fexa conexão
  client.stop();
  digitalWrite(7, LOW);
  delay(5000);

}

