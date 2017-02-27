#include <UIPEthernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;     
EthernetServer server(80);  
String readString;
char site[] = "www.yoursite.com";
uint8_t i = 1;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Program: Send Email"));
  Ethernet.begin(mac);
  server.begin();
  Serial.print(F("IP Address: "));
  Serial.println(Ethernet.localIP());
}

void loop() {
  client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
  
        if (readString.length() < 100) {
          readString += c;             
        }
 
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML>");
          client.println("<BODY>");
          client.println("<H1>Arduino Email</H1>");
          client.println("<hr />");
          client.println("<br />");
          client.println("<a href=\"/?emailsend\">Enviar Email</a><br />"); 
          client.println("</BODY>");
          client.println("</HTML>");
          delay(1);
          client.stop();
           
          if(readString.indexOf("?emailsend") > 0) {
            //digitalWrite(Pin, HIGH);
            Serial.println(F("Sending"));
            SendEmail();
          }
          readString="";    
        }
      }
    }
  }
}

bool SendEmail(){
 if (client.connect(server, 80)){
    Serial.print(F("-> Connected "));
    Serial.println(i);
    // Make a HTTP request:
    client.print("GET /SendEmail.php?");
    client.print("Recipient=");
    client.print("your.email@gmail.com");   //email to send to 
    client.print("&");
    client.print("Subject=");
    client.print("YourSubject");                 //subject of email
    client.print("&");
    client.print("Message=");
    client.print("YourMessageArduino");         //message of email
    client.print(i);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
    if(Sent()){
      Serial.println(F("Email send with sucess"));
      return true;
    } else {
      Serial.println(F("Erro re-sending"));
      SendEmail();
    }
  } else {
    // you didn't get a connection to the server:
    Serial.println(F("--> connection failed/n"));
    return false;
  }
}

bool Sent(){
  while (true) {
      if (client.available()) {
        char c = client.read();
        client.stop();
        i++;
        return true;
      }
      // if the server's disconnected, stop the client:
      if (!client.connected()) {
        Serial.println();
        Serial.println("disconnecting.");
        client.stop();
        return false;
      }
   }
}
