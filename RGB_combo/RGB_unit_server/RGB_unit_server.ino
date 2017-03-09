//NOTE: This program needs to be installed on the esp which works in conjunction with
//the atmega to control the RGB leds

#include <ESP8266WiFi.h>

String request = "";

int i=0; //this is the iterator used to parse inputString

const char* ssid = "The K3 Home";
const char* password = "antisocialmachine";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);
}

void loop() {
  // Connect to WiFi network
  if (WiFi.status() != WL_CONNECTED){
    //Serial.println();
    //Serial.println();
    //Serial.print("Connecting to ");
    //Serial.println(ssid);
    WiFi.begin(ssid, password);

    long checker = millis()+10000;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      //Serial.print(".");
      if(checker<millis()){
          return;
      }
    }
    //Serial.println("");
    //Serial.println("WiFi connected");
  
    // Start the server
    server.begin();
    //Serial.println("Server started");

    // Print the IP address
    //Serial.println(WiFi.localIP());
    //Serial.println(WiFi.macAddress());
  }

  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  //Serial.println("new client");
  long checker = millis()+3000;
  while(!client.available()){
    delay(1);
    if(checker<millis()){
      return;
    }
  }
  i=0;
  
  // Read the first line of the request
  request = client.readStringUntil('\r');
  //Serial.println(request);
  client.flush();
  client.write("<!DOCTYPE HTML><html><body><h1>Main Door</h1><a href=\"/unlock\"><h3>Unlock</h3></a></body></html>");
  //client.write("");
  // Match the request

//    String page = "<!DOCTYPE HTML><html><body><h1>Main Door</h1><a href=\"/unlock\"><h3>Unlock</h3></a></body></html>";

  sendRGB();
}

void sendRGB(){
  String r;
  String g;
  String b;
  while(request.charAt(i)!='('){
    i++;  
  }
  i++;
  r = getValue(',');
  i++;
  g = getValue(',');
  i++;
  b = getValue(')');
  Serial.print(r + "," + g + "," + b + ","+"\n");
  
}

String getValue(char check){
  String integer="";
  while(request.charAt(i)!=check){
    integer+= request.charAt(i);   
    i++;
    }
    return integer;
  }
