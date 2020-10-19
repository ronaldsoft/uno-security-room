#include <Keypad.h>

#define ledPin 12
#define ledPinR 10
#define signalPin 11

#define Password_Length 10

char Data[Password_Length]; 
char Master[Password_Length] = "insert_code_here"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;

const byte ROWS = 4; 
const byte COLS = 4; 
  
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad cKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  digitalWrite(ledPin, HIGH);   // sets the LED on
  pinMode(ledPinR, OUTPUT);      // sets the digital pin as output
  pinMode(signalPin, OUTPUT);  // sets the digital pin as output relay
  Serial.println("Enter password:");
  cKeypad.addEventListener(keypadEvent); //add an event listener for this keypad
}
  
void loop(){
  char customKey = cKeypad.getKey();
  if (customKey){
    if (customKey != '*') {
      Data[data_count] = customKey; 
      data_count++;
      //Serial.println(customKey);
    }
  }
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (eKey){
    case '*': 
    Serial.println("Checking...");
    guessPassword(); 
    break;
    case '#': 
    Serial.println("Cleaning...");
    clearData();
    delay(100);
    break;
  }
}

//function to check allright password
void guessPassword(){
  Serial.print(Data);
  if (!strcmp(Data, Master)){
    Serial.println("OK");
    digitalWrite(ledPin, LOW); //led indicator on green
    digitalWrite(signalPin, HIGH); //Relay pin
    delay(500);//delay for wait a 6s before deleting a prev password
    digitalWrite(signalPin, LOW); //Relay pin
    digitalWrite(ledPin, HIGH); //led indicator green
    //digitalWrite(ledPinR, LOW); //led indicator red    
    delay(1000);
    clearData(); //Clean data array  
  } else {
    Serial.println("Incorrect");
    clearData();
  }
}
void clearData(){
  digitalWrite(ledPinR, HIGH); //led indicator red
  digitalWrite(ledPin, LOW); //led indicator green
  delay(500);
  digitalWrite(ledPinR, LOW); //led indicator red
  digitalWrite(ledPin, HIGH); //led indicator green  
  while(data_count != 0){
    Data[data_count--] = 0; 
  }
  return;
}
