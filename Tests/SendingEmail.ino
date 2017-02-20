#include <UIPEthernet.h> // Used for Ethernet with ENC28J60

// **** ETHERNET SETTING ****
// Arduino Uno pins: 10 = CS, 11 = MOSI, 12 = MISO, 13 = SCK
// Ethernet MAC address - must be unique on your network - MAC Reads T4A001 in hex (unique in your network)
byte mac[] = { 0x54, 0x34, 0x41, 0x30, 0x30, 0x31 };                                       
// For the rest we use DHCP (IP address and such)

EthernetClient client;
char server[] = "www.wiplink.com.br"; // IP Adres (or name) of server to dump data to
int  interval = 10000; // Wait time between emails 
int i = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("Program: Send Email");

  Ethernet.begin(mac);
  delay(1000);
  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Default Gateway IP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server IP: ");
  Serial.println(Ethernet.dnsServerIP());
}

void loop() {
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("-> Connected");
    i++;
    // Make a HTTP request:
    client.print("GET /wimax/ardemail.php?");
    client.print("FromName=arduino&");
    client.print("Assunto=Loop");
    client.print(i);
    client.print("&");
    client.print("MailMsg=ola");
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(server);
    client.println( "Connection: close" );
    client.println();
    client.stop();
  }
  else {
    // you didn't get a connection to the server:
    Serial.println("--> connection failed/n");
  }

  delay(interval);
}
