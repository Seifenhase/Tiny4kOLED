/*
 * Tiny4kOLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x32 displays
 *
 * Based on ssd1306xled, re-written and extended by Stephen Denne
 * from 2017-04-25 at https://github.com/datacute/Tiny4kOLED
 *
 */
/*
 * SSD1306xLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x64 displays
 *
 * @created: 2014-08-12
 * @author: Neven Boyanov
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 */

// ----------------------------------------------------------------------------

#include <avr/pgmspace.h>

// ----------------------------------------------------------------------------

/* Font Information:
/* Modern DOS is a raster monospace serif based on IBM and Verite, extracted from VGA ROM typefaces
 * in real machines by various manufacturers, created with FontForge.
 * Source files available on NotABug: https://notabug.org/HarvettFox96/ttf-moderndos
 *
 * This typeface is made by Jayvee Enaguas (HarvettFox96), licensed under a Creative Commons Zero 
 * (CC0) 1.0. © 2009-2018.
 */ 
 
const uint8_t ssd1306xled_font8x8mdos [] PROGMEM = { 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x06, 0x5f, 0x5f, 0x06, 0x00, 0x00,
    0x00, 0x01, 0x07, 0x00, 0x01, 0x07, 0x00, 0x00,
    0x14, 0x7f, 0x7f, 0x14, 0x7f, 0x7f, 0x14, 0x00,
    0x24, 0x2e, 0x2a, 0x7f, 0x2a, 0x3a, 0x10, 0x00,
    0x4c, 0x6a, 0x36, 0x18, 0x6c, 0x56, 0x32, 0x00,
    0x30, 0x7a, 0x4d, 0x4d, 0x7f, 0x32, 0x50, 0x00,
    0x00, 0x00, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1c, 0x3e, 0x63, 0x41, 0x00, 0x00, 0x00,
    0x00, 0x41, 0x63, 0x3e, 0x1c, 0x00, 0x00, 0x00,
    0x08, 0x2a, 0x3e, 0x1c, 0x1c, 0x3e, 0x2a, 0x08,
    0x08, 0x08, 0x3e, 0x3e, 0x08, 0x08, 0x00, 0x00,
    0x00, 0x00, 0xa0, 0x60, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x00,
    0x3e, 0x7f, 0x79, 0x4d, 0x47, 0x7f, 0x3e, 0x00,
    0x00, 0x44, 0x46, 0x7f, 0x7f, 0x40, 0x40, 0x00,
    0x62, 0x73, 0x51, 0x59, 0x49, 0x6f, 0x66, 0x00,
    0x22, 0x63, 0x49, 0x49, 0x49, 0x7f, 0x36, 0x00,
    0x18, 0x1c, 0x16, 0x53, 0x7f, 0x7f, 0x50, 0x00,
    0x27, 0x67, 0x45, 0x45, 0x45, 0x7d, 0x39, 0x00,
    0x3e, 0x7f, 0x49, 0x49, 0x49, 0x7b, 0x32, 0x00,
    0x03, 0x03, 0x71, 0x79, 0x0d, 0x07, 0x03, 0x00,
    0x36, 0x7f, 0x49, 0x49, 0x49, 0x7f, 0x36, 0x00,
    0x26, 0x6f, 0x49, 0x49, 0x49, 0x7f, 0x3e, 0x00,
    0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xa2, 0x62, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x1c, 0x36, 0x63, 0x41, 0x00, 0x00,
    0x00, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x00,
    0x00, 0x41, 0x63, 0x36, 0x1c, 0x08, 0x00, 0x00,
    0x02, 0x03, 0x51, 0x59, 0x0f, 0x06, 0x00, 0x00,
    0x3e, 0x41, 0x49, 0x55, 0x55, 0x5d, 0x1e, 0x00,
    0x7e, 0x7f, 0x09, 0x09, 0x09, 0x7f, 0x7e, 0x00,
    0x41, 0x7f, 0x7f, 0x49, 0x49, 0x7f, 0x36, 0x00,
    0x3e, 0x7f, 0x41, 0x41, 0x41, 0x63, 0x22, 0x00,
    0x41, 0x7f, 0x7f, 0x41, 0x41, 0x7f, 0x3e, 0x00,
    0x41, 0x7f, 0x7f, 0x49, 0x5d, 0x41, 0x63, 0x00,
    0x41, 0x7f, 0x7f, 0x49, 0x1d, 0x01, 0x03, 0x00,
    0x3e, 0x7f, 0x41, 0x41, 0x51, 0x77, 0x76, 0x00,
    0x7f, 0x7f, 0x08, 0x08, 0x08, 0x7f, 0x7f, 0x00,
    0x00, 0x00, 0x41, 0x7f, 0x7f, 0x41, 0x00, 0x00,
    0x30, 0x70, 0x40, 0x41, 0x7f, 0x3f, 0x01, 0x00,
    0x41, 0x7f, 0x7f, 0x08, 0x1c, 0x77, 0x63, 0x00,
    0x41, 0x7f, 0x7f, 0x41, 0x40, 0x60, 0x70, 0x00,
    0x7f, 0x7e, 0x0c, 0x18, 0x0c, 0x7e, 0x7f, 0x00,
    0x7f, 0x7f, 0x06, 0x0c, 0x18, 0x7f, 0x7f, 0x00,
    0x3e, 0x7f, 0x41, 0x41, 0x41, 0x7f, 0x3e, 0x00,
    0x41, 0x7f, 0x7f, 0x49, 0x09, 0x0f, 0x06, 0x00,
    0x3e, 0x7f, 0x41, 0x71, 0x61, 0xff, 0xbe, 0x00,
    0x41, 0x7f, 0x7f, 0x09, 0x09, 0x7f, 0x76, 0x00,
    0x26, 0x6f, 0x49, 0x49, 0x49, 0x7b, 0x32, 0x00,
    0x00, 0x07, 0x41, 0x7f, 0x7f, 0x41, 0x07, 0x00,
    0x3f, 0x7f, 0x40, 0x40, 0x40, 0x7f, 0x3f, 0x00,
    0x0f, 0x1f, 0x30, 0x60, 0x30, 0x1f, 0x0f, 0x00,
    0x7f, 0x3f, 0x18, 0x0c, 0x18, 0x3f, 0x7f, 0x00,
    0x41, 0x63, 0x3e, 0x1c, 0x3e, 0x63, 0x41, 0x00,
    0x00, 0x07, 0x4f, 0x78, 0x78, 0x4f, 0x07, 0x00,
    0x47, 0x63, 0x71, 0x59, 0x4d, 0x67, 0x73, 0x00,
    0x00, 0x7f, 0x7f, 0x41, 0x41, 0x00, 0x00, 0x00,
    0x01, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x00,
    0x00, 0x41, 0x41, 0x7f, 0x7f, 0x00, 0x00, 0x00,
    0x08, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x08, 0x00,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x00, 0x00, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x74, 0x54, 0x54, 0x3c, 0x78, 0x40, 0x00,
    0x01, 0x7f, 0x7f, 0x48, 0x48, 0x78, 0x30, 0x00,
    0x38, 0x7c, 0x44, 0x44, 0x44, 0x6c, 0x28, 0x00,
    0x30, 0x78, 0x48, 0x49, 0x3f, 0x7f, 0x40, 0x00,
    0x38, 0x7c, 0x54, 0x54, 0x54, 0x5c, 0x18, 0x00,
    0x00, 0x48, 0x7e, 0x7f, 0x49, 0x03, 0x02, 0x00,
    0x18, 0xbc, 0xa4, 0xa4, 0xf8, 0x7c, 0x04, 0x00,
    0x41, 0x7f, 0x7f, 0x08, 0x04, 0x7c, 0x78, 0x00,
    0x00, 0x00, 0x44, 0x7d, 0x7d, 0x40, 0x00, 0x00,
    0x40, 0xc0, 0x80, 0x88, 0xfa, 0x7a, 0x00, 0x00,
    0x41, 0x7f, 0x7f, 0x10, 0x38, 0x6c, 0x44, 0x00,
    0x00, 0x00, 0x41, 0x7f, 0x7f, 0x40, 0x00, 0x00,
    0x7c, 0x7c, 0x08, 0x78, 0x0c, 0x7c, 0x78, 0x00,
    0x04, 0x7c, 0x78, 0x04, 0x04, 0x7c, 0x78, 0x00,
    0x38, 0x7c, 0x44, 0x44, 0x44, 0x7c, 0x38, 0x00,
    0x84, 0xfc, 0xf8, 0xa4, 0x24, 0x3c, 0x18, 0x00,
    0x18, 0x3c, 0x24, 0xa4, 0xfc, 0xfc, 0x80, 0x00,
    0x44, 0x7c, 0x78, 0x4c, 0x04, 0x0c, 0x0c, 0x00,
    0x08, 0x5c, 0x54, 0x54, 0x54, 0x74, 0x20, 0x00,
    0x04, 0x04, 0x3e, 0x7f, 0x44, 0x24, 0x00, 0x00,
    0x3c, 0x7c, 0x40, 0x40, 0x3c, 0x7c, 0x40, 0x00,
    0x0c, 0x1c, 0x30, 0x60, 0x30, 0x1c, 0x0c, 0x00,
    0x3c, 0x7c, 0x60, 0x38, 0x60, 0x7c, 0x3c, 0x00,
    0x44, 0x6c, 0x38, 0x10, 0x38, 0x6c, 0x44, 0x00,
    0x9c, 0xbc, 0xa0, 0xa0, 0xfc, 0x7c, 0x00, 0x00,
    0x4c, 0x64, 0x74, 0x5c, 0x4c, 0x64, 0x00, 0x00,
    0x00, 0x00, 0x08, 0x3e, 0x77, 0x41, 0x41, 0x00,
    0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x41, 0x41, 0x77, 0x3e, 0x08, 0x00,
    0x02, 0x03, 0x01, 0x03, 0x02, 0x03, 0x01, 0x00
};


// ----------------------------------------------------------------------------

const DCfont TinyOLED4kfont8x8mdos = {
  (uint8_t *)ssd1306xled_font8x8mdos,
  8, // character width in pixels
  1, // character height in pages (8 pixels)
  32,126 // ASCII extents
  };

// for backwards compatibility
#define FONT8X8MDOS (&TinyOLED4kfont8x8mdos)
