# 🕰️ Nixie Clock for ESP32 CYD

A beautiful Nixie-style clock display for ESP32 with TFT display that syncs time via NTP (Network Time Protocol).

![Nixie Clock](https://img.shields.io/badge/Platform-ESP32-blue)
![Display](https://img.shields.io/badge/Display-TFT%20320x240-green)
![Library](https://img.shields.io/badge/Library-TFT__eSPI-orange)

## ✨ Features

- 📡 **Automatic NTP Time Sync** - Syncs with internet time servers
- 🎨 **Nixie Tube Style Display** - Retro aesthetic with custom font
- ⚡ **Optimized Performance** - Uses millis() for efficient time tracking
- 🌍 **Timezone Support** - Configured for Bogotá (GMT-5), easily customizable
- 💡 **Blinking Colon Separator** - Classic clock animation
- 🔄 **Smart Updates** - Only redraws digits when they change
- ⏱️ **Hourly NTP Sync** - Minimal network calls, maximum accuracy

## 🛠️ Hardware Requirements

- **ESP32 Development Board** (ESP32 Dev Module or CYD - Cheap Yellow Display)
- **TFT Display** ST7789 320x240 pixels
- **WiFi Connection**

### Tested On
- ESP32-2432S028R (Cheap Yellow Display - CYD)
- Generic ESP32 Dev Modules with compatible TFT displays

## 📚 Software Requirements

### Arduino IDE Setup
1. **Arduino IDE** 1.8.19 or newer
2. **ESP32 Board Support**
   - Add to Board Manager URLs: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Install "ESP32 by Espressif Systems"

### Required Libraries
Install via Arduino Library Manager:
- **TFT_eSPI** by Bodmer
- **NTPClient** by Fabrice Weinberg
- **WiFi** (included with ESP32 board package)

## 📦 Installation

### 1. Clone or Download
```bash
git clone https://github.com/yourusername/nixie-clock-esp32.git


### 2. Configure TFT_eSPI Library

Edit `TFT_eSPI/User_Setup.h` or create a custom setup:
```cpp
#define ST7789_DRIVER

#define TFT_WIDTH  320
#define TFT_HEIGHT 240

// Pin definitions for CYD (ESP32-2432S028R)
#define TFT_MOSI 13
#define TFT_SCLK 12
#define TFT_CS   10
#define TFT_DC   11
#define TFT_RST  1
#define TFT_BL   14

#define SPI_FREQUENCY 80000000


### 3. Update WiFi Credentials

Edit the code to add your WiFi credentials:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";


### 4. Set Your Timezone

Modify the UTC offset for your location:
```cpp
// Current: Bogotá, Colombia (GMT-5)
NTPClient timeClient(ntpUDP, "pool.ntp.org", -5 * 3600, 3600000);

// Examples for other timezones:
// New York (GMT-5):     -5 * 3600
// London (GMT+0):        0 * 3600
// Tokyo (GMT+9):         9 * 3600
// Sydney (GMT+10):      10 * 3600


### 5. Add Nixie Font File

Ensure `nixiefont.h` is in the same directory as your sketch. This file contains the digit bitmaps.

### 6. Upload

1. Select **Board**: "ESP32 Dev Module"
2. Select correct **Port**
3. Click **Upload**

## 🎯 Usage

1. Power on your ESP32
2. The clock will automatically:
   - Connect to WiFi
   - Sync with NTP server
   - Display current time
3. Time updates every minute
4. NTP re-sync occurs every hour

## 🔧 Pin Configuration

### Default CYD Pinout
| Function | GPIO Pin |
|----------|----------|
| TFT_MOSI | 13       |
| TFT_SCLK | 12       |
| TFT_CS   | 10       |
| TFT_DC   | 11       |
| TFT_RST  | 1        |
| TFT_BL   | 14       |

## ⚙️ Configuration Options

### Change Update Intervals
```cpp
// In the code, modify these constants:
const unsigned long NTP_SYNC_INTERVAL = 3600000;  // 1 hour (in ms)
const unsigned long COLON_BLINK_INTERVAL = 1000;  // 1 second (in ms)


### Change NTP Server
```cpp
// Default: "pool.ntp.org"
// Alternatives:
// - "time.nist.gov"
// - "time.google.com"
// - "time.windows.com"


### Adjust Display Brightness

If using PWM backlight control, add to setup:
```cpp
ledcSetup(0, 5000, 8);
ledcAttachPin(TFT_BL, 0);
ledcWrite(0, 128);  // 0-255, where 255 is brightest


## 🐛 Troubleshooting

### Colors Look Wrong
Try these combinations in `setup()`:
```cpp
tft.setSwapBytes(true);   // or false
tft.invertDisplay(false); // or true


### Display is Blank
- Check TFT_eSPI configuration matches your hardware
- Verify SPI pins in User_Setup.h
- Check backlight pin connection

### Time Not Syncing
- Verify WiFi credentials
- Check internet connection
- Try different NTP se




