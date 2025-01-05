#include <SPI.h>
#include <MFRC522.h>
#include "LiquidCrystal.h"

LiquidCrystal lcd(8, 7, 5, 4, 3, 2);

#define RFID_SS_PIN 10
#define RFID_RST_PIN 9

MFRC522 rfidReader(RFID_SS_PIN, RFID_RST_PIN);

void setup() {
  Serial.begin(9600); // Initialize serial communication
  SPI.begin(); // Initialize SPI bus
  rfidReader.PCD_Init(); // Initialize RFID reader
  lcd.begin(16, 2); // Initialize LCD display
}

void loop() {
  // Check if a new RFID card is present
  if (!rfidReader.PICC_IsNewCardPresent()) {
    lcd.setCursor(3, 0);
    lcd.print("SHOW YOUR");
    lcd.setCursor(4, 1);
    lcd.print("ID CARD");
    return;
  } else {
    lcd.clear();
  }

  // Read the card's UID
  if (!rfidReader.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on serial monitor
  Serial.print("UID tag: ");
  String cardUID = "";
  for (byte i = 0; i < rfidReader.uid.size; i++) {
    Serial.print(rfidReader.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfidReader.uid.uidByte[i], HEX);
    cardUID.concat(String(rfidReader.uid.uidByte[i] < 0x10 ? " 0" : " "));
    cardUID.concat(String(rfidReader.uid.uidByte[i], HEX));
  }
  Serial.println();
  cardUID.toUpperCase();

  // Check the UID against authorized cards
  if (cardUID.substring(1) == "21B46626") {
    lcd.print("STUDENT 01");
    lcd.setCursor(0, 1);
    lcd.print("PRESENT");
    lcd.clear();
  } else if (cardUID.substring(1) == "81934043") {
    lcd.print("STUDENT 02");
    lcd.setCursor(0, 1);
    lcd.print("PRESENT");
    lcd.clear();
  } else if (cardUID.substring(1) == "91693E43") {
    lcd.print("STUDENT 03");
    lcd.setCursor(0, 1);
    lcd.print("PRESENT");
    lcd.clear();
  } else {
    lcd.print("UNAUTHORIZED");
    lcd.setCursor(0, 1);
    lcd.print("ACCESS");
    lcd.clear();
  }
}
