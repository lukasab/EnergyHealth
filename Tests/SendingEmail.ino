#include <UIPEthernet.h> // Used for Ethernet with ENC28J60

// **** ETHERNET SETTING ****
// Arduino Uno pins: 10 = CS, 11 = MOSI, 12 = MISO, 13 = SCK
// Ethernet MAC address - must be unique on your network - MAC Reads T4A001 in hex (unique in your network)
byte mac[] = { 0x54, 0x34, 0x41, 0x30, 0x30, 0x31 };                                       
// For the rest we use DHCP (IP address and such)

EthernetClient client;
char server[] = "www.yoursite.com"; // IP Adres (or name) of server to dump data to
int  interval = 10000; // Wait time between emails 

void setup() {

  Serial.begin(9600);
  Serial.println(F("Program: Send Email"));

  Ethernet.begin(mac);
  delay(1000);
  Serial.print(F("IP Address: "));
  Serial.println(Ethernet.localIP());
  Serial.print(F("Subnet Mask: "));
  Serial.println(Ethernet.subnetMask());
  Serial.print(F("Default Gateway IP: "));
  Serial.println(Ethernet.gatewayIP());
  Serial.print(F("DNS Server IP: "));
  Serial.println(Ethernet.dnsServerIP());
}

void loop() {
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println(F("-> Connected"));
    // Make a HTTP request:
    client.print("GET /SendEmail.php?");     //where your php file is (www.yoursite.com/SendEmail.php?)
    client.print("Recipient=");
    client.print("your.email@gmail.com");    //email to send to 
    client.print("&");
    client.print("Subject=");
    client.print("Arduino");                 //subject of email
    client.print("&");
    client.print("Message=");
    client.print("MessageofArduino");         //message of email
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(server);
    client.println( "Connection: close" );
    client.println();
    client.stop();    
  }
  else {
    // you didn't get a connection to the server:
    Serial.println(F("--> connection failed/n"));
  }

  delay(interval);
}
