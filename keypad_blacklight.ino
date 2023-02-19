#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = { {'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'} };
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
String pincode = "233";
String combinatie = "";
int ledPin = 13;
int buzzerPin = 11;
bool hasWon = false;

void setup() {
  Serial.flush();
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (hasWon)
  {
    char customKey = customKeypad.getKey();
    if (customKey == '*')
    {
      digitalWrite(ledPin, LOW);      
      combinatie = "";
      hasWon = false;
    }
    return;
  }
  
  char customKey = customKeypad.getKey();
  if (customKey) {
    if (customKey == '#')
    {
      if (combinatie == pincode)
      {
        hasWon = true;
        digitalWrite(ledPin, HIGH);
        analogWrite(buzzerPin, 50);
        delay(300);
        analogWrite(buzzerPin, 0);
        digitalWrite(ledPin, LOW);
        delay(300);
        analogWrite(buzzerPin, 50);
        digitalWrite(ledPin, HIGH);
        delay(300);
        analogWrite(buzzerPin, 0);
        digitalWrite(ledPin, LOW);
        delay(300);
        analogWrite(buzzerPin, 50);
        digitalWrite(ledPin, HIGH);
        delay(300);
        analogWrite(buzzerPin, 0);
      }
      else
      {
        combinatie = "";
        analogWrite(buzzerPin, 80);
        delay(1000);
        analogWrite(buzzerPin, 0);
      }
    }
    else
    {
        analogWrite(buzzerPin, 100);
        delay(100);
        analogWrite(buzzerPin, 0);
        combinatie += customKey;
    }
  }

  Serial.println(combinatie);

}