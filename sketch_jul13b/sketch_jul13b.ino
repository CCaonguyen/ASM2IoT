#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Servo.h>

#define BLYNK_PRINT Serial

char auth[] = "weCh7gVjUKSCATBFDJnN3IJh8mbBeOuA"; //replace with your Auth code here
const char* ssid = "Nam"; // replace with Your SSID
const char* password = "1234567891"; // replace with your wifi Password

#define SS_PIN D2
#define RST_PIN D1

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myServo;
#define BUZZER 15
#define LED_PIN D4
#define BUTTON_PIN V3

SimpleTimer timer;
bool cardDetected = false;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, password);
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  myServo.attach(D3);
  myServo.write(0);
  
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  
  SPI.begin();
  mfrc522.PCD_Init();
  
  Serial.println("Put your card to the reader...");
  timer.setInterval(1000L, checkCard);
}

void loop()
{
  timer.run();
  Blynk.run();
}

void checkCard()
{
  if (mfrc522.PICC_IsNewCardPresent())
  {
    mfrc522.PICC_ReadCardSerial();
    cardDetected = true;
    Serial.println("Card detected!");
    
    Blynk.virtualWrite(V2, "Card detected!");
    
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(BUZZER, LOW);
    delay(250);
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED_PIN, LOW);
    myServo.write(180);
    delay(3000);
    myServo.write(0);
    
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
  else if (!mfrc522.PICC_IsNewCardPresent() && cardDetected)
  {
    cardDetected = false;
    Serial.println("Card removed!");
    
    Blynk.virtualWrite(V2, "Card removed!");
  }
  
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW) {
    Blynk.virtualWrite(V1, 1);
  } else {
    Blynk.virtualWrite(V1, 0);
  }
}
