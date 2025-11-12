# JPEG to RGB565 C Array Converter

A Python utility that converts JPEG images into RGB565 format C arrays suitable for embedded systems with TFT displays (ESP32, Arduino, etc.).

## Description

This tool reads a JPEG image file and converts it into a C array containing RGB565-formatted pixel data. The output is written to a `.c` file with the same name as the input image, making it easy to include in your embedded projects.

The RGB565 format uses 16 bits per pixel (5 bits red, 6 bits green, 5 bits blue), which is commonly used in embedded TFT displays to balance color quality with memory efficiency.

## Features

- Converts JPEG images to RGB565 C arrays
- Output format: `const unsigned char` array
- Little-endian byte order (low byte first, high byte second)
- Automatic output file naming (input.jpg → input.c)
- Includes image dimensions in output file comments
- Formatted output with 6 pixels per line for readability

## Requirements

- Python 3.x
- Pillow library

## Installation

Install the required Pillow library:

```bash
pip install Pillow
```

## Usage

```bash
python convert_to_rgb565.py <image_file>
```

### Example

```bash
python convert_to_rgb565.py logo.jpg
```

This will create a file named `logo.c` containing the RGB565 array data.

## Output Format

The generated C file contains:

```c
// RGB565 C array
// Image size: 128x64
const unsigned char image[16384] = {
    0xF8, 0x00, 0x1F, 0x00, 0xE0, 0x07, 0xFF, 0xFF, 0x00, 0x00, 0xF8, 0x00,
    // ... more data
};
```

## Integration with ESP32/TFT Projects

To use the generated array in your ESP32 project:

1. Include the generated `.c` file in your project
2. Declare the array as `extern` in your main code:
   ```cpp
   extern const unsigned char image[];
   ```
3. Use with TFT libraries like TFT_eSPI or Adafruit_GFX:
   ```cpp
   tft.pushImage(x, y, width, height, (uint16_t*)image);
   ```

## Technical Details

- **Color Conversion**: RGB888 → RGB565
  - Red: 8 bits → 5 bits (0xF8 mask)
  - Green: 8 bits → 6 bits (0xFC mask)
  - Blue: 8 bits → 5 bits (shift right 3)
- **Byte Order**: Little-endian (LSB first)
- **Array Size**: width × height × 2 bytes

## Author

**Reinaldo Torres**  
Email: reyco2000@gmail.com  
Date: July 2024

## License

This code is free and open source, and can be used and modified for any purpose.

## Notes

- Ensure your input images are not too large for your target microcontroller's memory
- For ESP32 with PSRAM, larger images are possible
- Consider using PROGMEM or SPIFFS for storing large image arrays on ESP32
