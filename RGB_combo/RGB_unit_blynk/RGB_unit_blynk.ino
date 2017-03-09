//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
SimpleTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "5da551f798184a6b8ec12d6b6787f796";

// Your WiFi credentials.
// Set password to "" for open networks.
bool Connected2Blynk = false;
char ssid[] = "The K3 Home";
char pass[] = "antisocialmachine";

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(11000L, CheckConnection);
}

BLYNK_WRITE(V1){   
  String r = param[0].asStr(); // getting first value
  String g = param[1].asStr(); // getting second value
  String b = param[2].asStr(); // getting N value
  Serial.print(r + "," + g + "," + b + ","+"\n");
}

void CheckConnection(){
  Connected2Blynk = Blynk.connected();
  if(!Connected2Blynk){
    //Serial.println("Not connected to Blynk server");
    Blynk.connectWiFi("ssid", "pass");
    Blynk.connect(3333);  // timeout set to 10 seconds and then continue without Blynk  
  }
  else{
    //Serial.println("Connected to Blynk server");     
  }
}

void loop() {
  if(Connected2Blynk){
    Blynk.run();
  }
  timer.run();
}

