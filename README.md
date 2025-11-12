# ESP32-Chipshift

A collection of ESP32 and Arduino tools and utilities for embedded systems development, focusing on display interfaces and digital potentiometer control.

## 📋 Overview

This repository contains three distinct projects designed to simplify embedded systems development:

1. **SD1306 Image Editor** - Image to bitmap converter for OLED displays
2. **TFT Display Bitmaps Tool** - JPEG to RGB565 converter for TFT displays
3. **TPL-0501-100 ESP32** - Digital potentiometer control library

## 🛠️ Projects

### 1. SD1306 Image Editor

A bitmap converter tool for SD1306 OLED displays compatible with Arduino, ESP32, and ESP8266 using the Adafruit GFX Library.

**Features:**
- Convert images to C arrays for SD1306 displays
- Built with Python tkinter for easy GUI interaction
- Direct integration with Adafruit GFX Library
- Visual image preview and editing

**Location:** [`SD1306-Image-Editor/`](SD1306-Image-Editor/)

**Quick Start:**
```bash
python editor3.py
```

[Read more →](SD1306-Image-Editor/README.md)

---

### 2. TFT Display Bitmaps Tool

A Python utility that converts JPEG images into RGB565 format C arrays suitable for embedded systems with TFT displays.

**Features:**
- JPEG to RGB565 C array conversion
- Little-endian byte order for ESP32 compatibility
- Automatic output file generation
- Optimized for TFT_eSPI and Adafruit_GFX libraries
- Memory-efficient 16-bit color format

**Location:** [`TFT_Display_Bitmats_Tool/`](TFT_Display_Bitmats_Tool/)

**Requirements:**
- Python 3.x
- Pillow library

**Quick Start:**
```bash
pip install Pillow
python rbg.py <image_file.jpg>
```

[Read more →](TFT_Display_Bitmats_Tool/README.md)

---

### 3. TPL-0501-100 ESP32

Arduino sample code for controlling the TPL0501 Digital Potentiometer with ESP32. Includes examples for both single and dual digital potentiometer configurations.

**Features:**
- Single digital potentiometer control
- Dual digital potentiometer control
- I2C communication examples
- Part of a next-generation joystick project for the Color Computer

**Location:** [`TPL-0501-100ESP32/`](TPL-0501-100ESP32/)

**Files:**
- `singledigipot.ino` - Single digipot example
- `dualdigipotTPL0501.ino` - Dual digipot example

**Quick Start:**
1. Open `.ino` file in Arduino IDE
2. Select your ESP32 board
3. Upload to your device

[Read more →](TPL-0501-100ESP32/README.md)

---

## 🎯 Use Cases

- **Embedded Display Development**: Convert images for OLED and TFT displays
- **Retro Computing**: Digital potentiometer control for vintage hardware interfaces
- **ESP32 Projects**: Ready-to-use utilities for common ESP32 display and I/O tasks
- **Arduino Development**: Cross-platform tools for Arduino-based projects

## 📦 Requirements

### General
- ESP32 or Arduino-compatible board
- Arduino IDE or PlatformIO

### For Image Tools
- Python 3.x
- Pillow library (for TFT tool)
- tkinter (for SD1306 editor)

### For Hardware Projects
- TPL0501 Digital Potentiometer (for digipot project)
- SD1306 OLED Display (128x64) or TFT Display

## 🚀 Getting Started

1. Clone this repository:
   ```bash
   git clone https://github.com/reyco2000/ESP32-Chipshift.git
   cd ESP32-Chipshift
   ```

2. Navigate to the project folder you need:
   ```bash
   cd SD1306-Image-Editor     # For SD1306 tools
   cd TFT_Display_Bitmats_Tool # For TFT tools
   cd TPL-0501-100ESP32       # For digital potentiometer
   ```

3. Follow the specific README in each folder for detailed instructions

## 👤 Author

**Reinaldo Torres**
Email: reyco2000@gmail.com

## 📄 License

This project is open source and available under the terms specified in the [LICENSE](LICENSE) file.

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! Feel free to check the issues page or submit a pull request.

## 📝 Notes

- Ensure your images are appropriately sized for your target microcontroller's memory
- For ESP32 with PSRAM, larger images are supported
- Consider using PROGMEM or SPIFFS for storing large image arrays
- Test digital potentiometer configurations with appropriate resistor values

---

Made with ❤️ for the embedded systems community
