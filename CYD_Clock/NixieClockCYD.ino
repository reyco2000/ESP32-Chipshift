/*******************************************************************************
 * NixieClock (C) 2024 By Reinaldo Torres (reyco2000@gmail.com)
 * Code is for Clock that syncs thru NTP, output is display using
 * a Nixie Font for a TFT 320x240 Screen
 * Ported to TFT_eSPI library for CYD 10.5.2025
 * Optimized with millis() time tracking
 ******************************************************************************/
#include "nixiefont.h"
#include <WiFi.h>
#include <TFT_eSPI.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Network credentials
const char* ssid = "YOURSSID";
const char* password = "YOURPASS";

// NTP Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -5 * 3600, 3600000); // Sync every hour

// Timing constants
const unsigned long NTP_SYNC_INTERVAL = 3600000;  // Sync with NTP every hour
const unsigned long COLON_BLINK_INTERVAL = 1000;  // Blink every second

// Screen layout constants
const uint8_t SCREEN_WIDTH = 320;
const uint8_t SCREEN_HEIGHT = 240;
const uint8_t DIGIT_WIDTH = 64;
const uint8_t DIGIT_HEIGHT = 106;
const uint8_t Y_POSITION = (SCREEN_HEIGHT - DIGIT_HEIGHT) / 2;

// Digit positions
const uint16_t POS_HOUR_1 = 0;
const uint16_t POS_HOUR_2 = 64;
const uint16_t POS_COLON = 128;
const uint16_t POS_MIN_1 = 192;
const uint16_t POS_MIN_2 = 256;

// TFT and font
TFT_eSPI tft = TFT_eSPI();
const unsigned char* nixieFont[] = {
  numero_0, numero_1, numero_2, numero_3, numero_4, 
  numero_5, numero_6, numero_7, numero_8, numero_9, 
  punto, dospuntos
};

// Time tracking variables
unsigned long lastNtpSync = 0;
unsigned long baseEpochTime = 0;
unsigned long baseMillis = 0;

// Display state
unsigned long lastColonBlink = 0;
bool colonVisible = true;
int lastMinute = -1;
int lastHour = -1;

void setup() {
  Serial.begin(115200);
  Serial.println("Nixie Clock - Starting...");

  // Initialize display
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.invertDisplay(false);
  tft.fillScreen(TFT_BLACK);

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi Connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Initialize NTP and get initial time
  timeClient.begin();
  syncTimeWithNTP();
  
  Serial.println("Nixie Clock Ready!");
}

void syncTimeWithNTP() {
  Serial.print("Syncing with NTP...");
  timeClient.update();
  
  // Store the base time reference
  baseEpochTime = timeClient.getEpochTime();
  baseMillis = millis();
  lastNtpSync = millis();
  
  Serial.println(" Done!");
  Serial.printf("Synced time: %02d:%02d:%02d\n", 
    timeClient.getHours(), 
    timeClient.getMinutes(), 
    timeClient.getSeconds());
}

void getCurrentTime(int &hours, int &minutes, int &seconds) {
  // Calculate elapsed seconds since last NTP sync
  unsigned long elapsedMillis = millis() - baseMillis;
  unsigned long elapsedSeconds = elapsedMillis / 1000;
  
  // Calculate current time
  unsigned long currentEpoch = baseEpochTime + elapsedSeconds;
  
  hours = (currentEpoch % 86400L) / 3600;
  minutes = (currentEpoch % 3600) / 60;
  seconds = currentEpoch % 60;
}

void drawDigit(uint16_t x, uint8_t digit) {
  if (digit < 10) {
    tft.pushImage(x, Y_POSITION, DIGIT_WIDTH, DIGIT_HEIGHT, (uint16_t*)nixieFont[digit]);
  }
}

void drawColon(bool visible) {
  uint8_t symbol = visible ? 11 : 10;  // dospuntos : punto
  tft.pushImage(POS_COLON, Y_POSITION, DIGIT_WIDTH, DIGIT_HEIGHT, (uint16_t*)nixieFont[symbol]);
}

void updateDisplay() {
  int hours, minutes, seconds;
  getCurrentTime(hours, minutes, seconds);
  
  // Only update hour digits if changed
  if (hours != lastHour) {
    drawDigit(POS_HOUR_1, hours / 10);
    drawDigit(POS_HOUR_2, hours % 10);
    lastHour = hours;
  }
  
  // Only update minute digits if changed
  if (minutes != lastMinute) {
    drawDigit(POS_MIN_1, minutes / 10);
    drawDigit(POS_MIN_2, minutes % 10);
    lastMinute = minutes;
    
    Serial.printf("Time: %02d:%02d:%02d\n", hours, minutes, seconds);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Sync with NTP server periodically (every hour)
  if (currentMillis - lastNtpSync >= NTP_SYNC_INTERVAL) {
    syncTimeWithNTP();
  }
  
  // Update display when minute changes
  static unsigned long lastDisplayUpdate = 0;
  if (currentMillis - lastDisplayUpdate >= 1000) {  // Check every second
    lastDisplayUpdate = currentMillis;
    updateDisplay();
  }
  
  // Blink colon every second
  if (currentMillis - lastColonBlink >= COLON_BLINK_INTERVAL) {
    lastColonBlink = currentMillis;
    colonVisible = !colonVisible;
    drawColon(colonVisible);
  }
}

