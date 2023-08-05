#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <MFRC522.h>
#include <Servo.h>

#define BLYNK_PRINT Serial

char auth[] = "RLtvF2TLyHIqvsmiRDgAuuv7tZvPyDnz"; //replace with your Auth code here
const char* ssid = "Nam"; // replace with Your SSID
const char* password = "1234567891";

#define SS_PIN D2    // Define the SDA pin for RC522
#define RST_PIN D1   // Define the RST pin for RC522

MFRC522 mfrc522;   // Create MFRC522 instance.

Servo myServo; // define servo name
#define SERVO_PIN D3 // servo control pin

#define BUZZER_PIN D4 // buzzer control pin
#define LED_PIN D5    // LED control pin

SimpleTimer timer;
bool cardDetected = false; // Flag to track if card is detected

void setup() 
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, password);
  
  myServo.attach(SERVO_PIN); // servo control pin
  myServo.write(0); // servo start position
  
  pinMode(BUZZER_PIN, OUTPUT); // Use BUZZER_PIN instead of BUZZER
  pinMode(LED_PIN, OUTPUT);    // Define LED pin as OUTPUT
  
  noTone(BUZZER_PIN);
  
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init(SS_PIN, RST_PIN);   // Initiate MFRC522 with custom pins
  
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
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent()) 
  {
    mfrc522.PICC_ReadCardSerial(); // Read card serial
    cardDetected = true;
    Serial.println("Card detected!");
    
    Blynk.virtualWrite(V1, "1"); // Send signal to Blynk to trigger servo
    
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    
    delay(250);
    
    digitalWrite(BUZZER_PIN, LOW);
    delay(250);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(250);
    digitalWrite(BUZZER_PIN, LOW);
    
    myServo.write(180);
    delay(3000);
    myServo.write(0);
    
    digitalWrite(LED_PIN, LOW); // Turn off LED
    
    mfrc522.PICC_HaltA(); // Halt PICC
    mfrc522.PCD_StopCrypto1(); // Stop encryption on PCD
    
    Blynk.virtualWrite(V1, "0"); // Reset the signal to Blynk
  }
  else if (!mfrc522.PICC_IsNewCardPresent() && cardDetected)
  {
    cardDetected = false;
    Serial.println("Card removed!");
  }
}

BLYNK_WRITE(V2)
{
  int buttonState = param.asInt(); // Đọc trạng thái nút bấm (0 hoặc 1)
  
  if (buttonState == HIGH) // Nếu nút bấm được nhấn
  {
    // Gửi tín hiệu mở servo
    myServo.write(180);
    
    // Bật còi báo
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    delay(250);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(250);
    digitalWrite(BUZZER_PIN, LOW); // Use BUZZER_PIN instead of BUZZER
  }
  else // Nếu nút bấm được thả ra
  {
    // Đóng servo
    myServo.write(0);
    
    // Tắt còi báo
    digitalWrite(BUZZER_PIN, LOW); // Use BUZZER_PIN instead of BUZZER
  }
}
BLYNK_WRITE(V3)
{
  int ledState = param.asInt(); // Đọc trạng thái nút bấm (0 hoặc 1)
  
  if (ledState == HIGH) // Nếu nút bấm được nhấn
  {
    // Bật đèn LED
    digitalWrite(LED_PIN, HIGH);
  }
  else // Nếu nút bấm được thả ra
  {
    // Tắt đèn LED
    digitalWrite(LED_PIN, LOW);
  }
}
