String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int i = 0; //this is the iterator used the get value loop

#define red_pin 9
#define green_pin 10
#define blue_pin 11

void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  analogWrite(red_pin, 0);
  analogWrite(green_pin, 0);
  analogWrite(blue_pin, 0);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  serialEvent(); //call the function
  // print the string when a newline arrives:
  if (stringComplete) {
    byte r;
    byte g;
    byte b;
    r = getValue(',');
    i++;
    g = getValue(',');
    i++;
    b = getValue(',');
    analogWrite(red_pin, r);
    analogWrite(green_pin, g);
    analogWrite(blue_pin, b);
    i=0;
    inputString = "";
    stringComplete = false;
  }
}

byte getValue(char check){
  String integer="";
  long returner;
  while(inputString.charAt(i)!=check){
    integer+= inputString.charAt(i);   
    i++;
    }
    returner = integer.toInt();
    return returner;
  }

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
