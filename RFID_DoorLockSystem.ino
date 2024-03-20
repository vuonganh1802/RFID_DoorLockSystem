#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_Y 4 // yellow LED pin
#define LED_R 5 // red LED pin
#define BUZZER 2 
#define lock 3
// Create MFRC522 instance.
MFRC522 mfrc522(SS_PIN, RST_PIN);   
int Btn = 6;
void setup() 
{
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  pinMode(Btn,INPUT);
  pinMode(lock,OUTPUT);
  Serial.println("Place your card on reader...");
  Serial.println();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print(" Scan Your RFID "); 
  lcd.setCursor(0,1); 
  lcd.print("   Door Locked   ");

 }
void loop() 
{
if(digitalRead(Btn) == HIGH){
    Serial.println("Access Granted");
    Serial.println();
    delay(500);
    digitalWrite(LED_Y, HIGH);
    lcd.setCursor(0,1); 
    lcd.print(" Door Un-Locked ");
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
    delay(50);
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
    digitalWrite(lock,HIGH);
    delay(3000);
    digitalWrite(lock,LOW);
    delay(100);
    digitalWrite(LED_Y, LOW);
    lcd.setCursor(0,1); 
    lcd.print("   Door Locked   ");
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
  delay(50);
  }
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase(); 
 if (content.substring(1) == "A3 DB 05 30") 
  {
    Serial.println("Access Granted");
    Serial.println();
    delay(500);
    digitalWrite(LED_Y, HIGH);
    lcd.setCursor(0,1); 
    lcd.print(" Door Un-Locked ");
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
    delay(50);
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
    digitalWrite(lock,HIGH);
    delay(3000);
    digitalWrite(lock,LOW);
    delay(100);
    digitalWrite(LED_Y, LOW);
    lcd.setCursor(0,1); 
    lcd.print("   Door Locked   ");
    tone(BUZZER, 2000);
    delay(100);
    noTone(BUZZER);
    delay(50);
  }

else
{
    lcd.setCursor(0,1); 
    lcd.print("Invalid RFID Tag");
    Serial.println(" Access denied ");
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 1500);
    delay(500);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
    delay(100);
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 1500);
    delay(500);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
    delay(100);
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 1500);
    delay(500);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
    lcd.setCursor(0,1); 
    lcd.print("   Door Locked   ");
 }
 }
