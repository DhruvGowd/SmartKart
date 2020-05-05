#include "SPILCD.h"
#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include <stdbool.h>

#define _width 320
#define _height 320

//adapted from https://gist.github.com/postmodern/ed6e670999f456ad9f13
// and https://github.com/adafruit/Adafruit_ILI9341/blob/master/Adafruit_ILI9341.cpp
const bool wrap = true;

const unsigned char font[] = {
			0x00, 0x00, 0x00, 0x00, 0x00,
			0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
			0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
			0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
			0x18, 0x3C, 0x7E, 0x3C, 0x18,
			0x1C, 0x57, 0x7D, 0x57, 0x1C,
			0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
			0x00, 0x18, 0x3C, 0x18, 0x00,
			0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
			0x00, 0x18, 0x24, 0x18, 0x00,
			0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
			0x30, 0x48, 0x3A, 0x06, 0x0E,
			0x26, 0x29, 0x79, 0x29, 0x26,
			0x40, 0x7F, 0x05, 0x05, 0x07,
			0x40, 0x7F, 0x05, 0x25, 0x3F,
			0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
			0x7F, 0x3E, 0x1C, 0x1C, 0x08,
			0x08, 0x1C, 0x1C, 0x3E, 0x7F,
			0x14, 0x22, 0x7F, 0x22, 0x14,
			0x5F, 0x5F, 0x00, 0x5F, 0x5F,
			0x06, 0x09, 0x7F, 0x01, 0x7F,
			0x00, 0x66, 0x89, 0x95, 0x6A,
			0x60, 0x60, 0x60, 0x60, 0x60,
			0x94, 0xA2, 0xFF, 0xA2, 0x94,
			0x08, 0x04, 0x7E, 0x04, 0x08,
			0x10, 0x20, 0x7E, 0x20, 0x10,
			0x08, 0x08, 0x2A, 0x1C, 0x08,
			0x08, 0x1C, 0x2A, 0x08, 0x08,
			0x1E, 0x10, 0x10, 0x10, 0x10,
			0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
			0x30, 0x38, 0x3E, 0x38, 0x30,
			0x06, 0x0E, 0x3E, 0x0E, 0x06,
			0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x5F, 0x00, 0x00,
			0x00, 0x07, 0x00, 0x07, 0x00,
			0x14, 0x7F, 0x14, 0x7F, 0x14,
			0x24, 0x2A, 0x7F, 0x2A, 0x12,
			0x23, 0x13, 0x08, 0x64, 0x62,
			0x36, 0x49, 0x56, 0x20, 0x50,
			0x00, 0x08, 0x07, 0x03, 0x00,
			0x00, 0x1C, 0x22, 0x41, 0x00,
			0x00, 0x41, 0x22, 0x1C, 0x00,
			0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
			0x08, 0x08, 0x3E, 0x08, 0x08,
			0x00, 0x80, 0x70, 0x30, 0x00,
			0x08, 0x08, 0x08, 0x08, 0x08,
			0x00, 0x00, 0x60, 0x60, 0x00,
			0x20, 0x10, 0x08, 0x04, 0x02,
			0x3E, 0x51, 0x49, 0x45, 0x3E,
			0x00, 0x42, 0x7F, 0x40, 0x00,
			0x72, 0x49, 0x49, 0x49, 0x46,
			0x21, 0x41, 0x49, 0x4D, 0x33,
			0x18, 0x14, 0x12, 0x7F, 0x10,
			0x27, 0x45, 0x45, 0x45, 0x39,
			0x3C, 0x4A, 0x49, 0x49, 0x31,
			0x41, 0x21, 0x11, 0x09, 0x07,
			0x36, 0x49, 0x49, 0x49, 0x36,
			0x46, 0x49, 0x49, 0x29, 0x1E,
			0x00, 0x00, 0x14, 0x00, 0x00,
			0x00, 0x40, 0x34, 0x00, 0x00,
			0x00, 0x08, 0x14, 0x22, 0x41,
			0x14, 0x14, 0x14, 0x14, 0x14,
			0x00, 0x41, 0x22, 0x14, 0x08,
			0x02, 0x01, 0x59, 0x09, 0x06,
			0x3E, 0x41, 0x5D, 0x59, 0x4E,
			0x7C, 0x12, 0x11, 0x12, 0x7C,
			0x7F, 0x49, 0x49, 0x49, 0x36,
			0x3E, 0x41, 0x41, 0x41, 0x22,
			0x7F, 0x41, 0x41, 0x41, 0x3E,
			0x7F, 0x49, 0x49, 0x49, 0x41,
			0x7F, 0x09, 0x09, 0x09, 0x01,
			0x3E, 0x41, 0x41, 0x51, 0x73,
			0x7F, 0x08, 0x08, 0x08, 0x7F,
			0x00, 0x41, 0x7F, 0x41, 0x00,
			0x20, 0x40, 0x41, 0x3F, 0x01,
			0x7F, 0x08, 0x14, 0x22, 0x41,
			0x7F, 0x40, 0x40, 0x40, 0x40,
			0x7F, 0x02, 0x1C, 0x02, 0x7F,
			0x7F, 0x04, 0x08, 0x10, 0x7F,
			0x3E, 0x41, 0x41, 0x41, 0x3E,
			0x7F, 0x09, 0x09, 0x09, 0x06,
			0x3E, 0x41, 0x51, 0x21, 0x5E,
			0x7F, 0x09, 0x19, 0x29, 0x46,
			0x26, 0x49, 0x49, 0x49, 0x32,
			0x03, 0x01, 0x7F, 0x01, 0x03,
			0x3F, 0x40, 0x40, 0x40, 0x3F,
			0x1F, 0x20, 0x40, 0x20, 0x1F,
			0x3F, 0x40, 0x38, 0x40, 0x3F,
			0x63, 0x14, 0x08, 0x14, 0x63,
			0x03, 0x04, 0x78, 0x04, 0x03,
			0x61, 0x59, 0x49, 0x4D, 0x43,
			0x00, 0x7F, 0x41, 0x41, 0x41,
			0x02, 0x04, 0x08, 0x10, 0x20,
			0x00, 0x41, 0x41, 0x41, 0x7F,
			0x04, 0x02, 0x01, 0x02, 0x04,
			0x40, 0x40, 0x40, 0x40, 0x40,
			0x00, 0x03, 0x07, 0x08, 0x00,
			0x20, 0x54, 0x54, 0x78, 0x40,
			0x7F, 0x28, 0x44, 0x44, 0x38,
			0x38, 0x44, 0x44, 0x44, 0x28,
			0x38, 0x44, 0x44, 0x28, 0x7F,
			0x38, 0x54, 0x54, 0x54, 0x18,
			0x00, 0x08, 0x7E, 0x09, 0x02,
			0x18, 0xA4, 0xA4, 0x9C, 0x78,
			0x7F, 0x08, 0x04, 0x04, 0x78,
			0x00, 0x44, 0x7D, 0x40, 0x00,
			0x20, 0x40, 0x40, 0x3D, 0x00,
			0x7F, 0x10, 0x28, 0x44, 0x00,
			0x00, 0x41, 0x7F, 0x40, 0x00,
			0x7C, 0x04, 0x78, 0x04, 0x78,
			0x7C, 0x08, 0x04, 0x04, 0x78,
			0x38, 0x44, 0x44, 0x44, 0x38,
			0xFC, 0x18, 0x24, 0x24, 0x18,
			0x18, 0x24, 0x24, 0x18, 0xFC,
			0x7C, 0x08, 0x04, 0x04, 0x08,
			0x48, 0x54, 0x54, 0x54, 0x24,
			0x04, 0x04, 0x3F, 0x44, 0x24,
			0x3C, 0x40, 0x40, 0x20, 0x7C,
			0x1C, 0x20, 0x40, 0x20, 0x1C,
			0x3C, 0x40, 0x30, 0x40, 0x3C,
			0x44, 0x28, 0x10, 0x28, 0x44,
			0x4C, 0x90, 0x90, 0x90, 0x7C,
			0x44, 0x64, 0x54, 0x4C, 0x44,
			0x00, 0x08, 0x36, 0x41, 0x00,
			0x00, 0x00, 0x77, 0x00, 0x00,
			0x00, 0x41, 0x36, 0x08, 0x00,
			0x02, 0x01, 0x02, 0x04, 0x02,
			0x3C, 0x26, 0x23, 0x26, 0x3C,
			0x1E, 0xA1, 0xA1, 0x61, 0x12,
			0x3A, 0x40, 0x40, 0x20, 0x7A,
			0x38, 0x54, 0x54, 0x55, 0x59,
			0x21, 0x55, 0x55, 0x79, 0x41,
			0x22, 0x54, 0x54, 0x78, 0x42,
			0x21, 0x55, 0x54, 0x78, 0x40,
			0x20, 0x54, 0x55, 0x79, 0x40,
			0x0C, 0x1E, 0x52, 0x72, 0x12,
			0x39, 0x55, 0x55, 0x55, 0x59,
			0x39, 0x54, 0x54, 0x54, 0x59,
			0x39, 0x55, 0x54, 0x54, 0x58,
			0x00, 0x00, 0x45, 0x7C, 0x41,
			0x00, 0x02, 0x45, 0x7D, 0x42,
			0x00, 0x01, 0x45, 0x7C, 0x40,
			0x7D, 0x12, 0x11, 0x12, 0x7D,
			0xF0, 0x28, 0x25, 0x28, 0xF0,
			0x7C, 0x54, 0x55, 0x45, 0x00,
			0x20, 0x54, 0x54, 0x7C, 0x54,
			0x7C, 0x0A, 0x09, 0x7F, 0x49,
			0x32, 0x49, 0x49, 0x49, 0x32,
			0x3A, 0x44, 0x44, 0x44, 0x3A,
			0x32, 0x4A, 0x48, 0x48, 0x30,
			0x3A, 0x41, 0x41, 0x21, 0x7A,
			0x3A, 0x42, 0x40, 0x20, 0x78,
			0x00, 0x9D, 0xA0, 0xA0, 0x7D,
			0x3D, 0x42, 0x42, 0x42, 0x3D,
			0x3D, 0x40, 0x40, 0x40, 0x3D,
			0x3C, 0x24, 0xFF, 0x24, 0x24,
			0x48, 0x7E, 0x49, 0x43, 0x66,
			0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
			0xFF, 0x09, 0x29, 0xF6, 0x20,
			0xC0, 0x88, 0x7E, 0x09, 0x03,
			0x20, 0x54, 0x54, 0x79, 0x41,
			0x00, 0x00, 0x44, 0x7D, 0x41,
			0x30, 0x48, 0x48, 0x4A, 0x32,
			0x38, 0x40, 0x40, 0x22, 0x7A,
			0x00, 0x7A, 0x0A, 0x0A, 0x72,
			0x7D, 0x0D, 0x19, 0x31, 0x7D,
			0x26, 0x29, 0x29, 0x2F, 0x28,
			0x26, 0x29, 0x29, 0x29, 0x26,
			0x30, 0x48, 0x4D, 0x40, 0x20,
			0x38, 0x08, 0x08, 0x08, 0x08,
			0x08, 0x08, 0x08, 0x08, 0x38,
			0x2F, 0x10, 0xC8, 0xAC, 0xBA,
			0x2F, 0x10, 0x28, 0x34, 0xFA,
			0x00, 0x00, 0x7B, 0x00, 0x00,
			0x08, 0x14, 0x2A, 0x14, 0x22,
			0x22, 0x14, 0x2A, 0x14, 0x08,
			0x55, 0x00, 0x55, 0x00, 0x55,
			0xAA, 0x55, 0xAA, 0x55, 0xAA,
			0xFF, 0x55, 0xFF, 0x55, 0xFF,
			0x00, 0x00, 0x00, 0xFF, 0x00,
			0x10, 0x10, 0x10, 0xFF, 0x00,
			0x14, 0x14, 0x14, 0xFF, 0x00,
			0x10, 0x10, 0xFF, 0x00, 0xFF,
			0x10, 0x10, 0xF0, 0x10, 0xF0,
			0x14, 0x14, 0x14, 0xFC, 0x00,
			0x14, 0x14, 0xF7, 0x00, 0xFF,
			0x00, 0x00, 0xFF, 0x00, 0xFF,
			0x14, 0x14, 0xF4, 0x04, 0xFC,
			0x14, 0x14, 0x17, 0x10, 0x1F,
			0x10, 0x10, 0x1F, 0x10, 0x1F,
			0x14, 0x14, 0x14, 0x1F, 0x00,
			0x10, 0x10, 0x10, 0xF0, 0x00,
			0x00, 0x00, 0x00, 0x1F, 0x10,
			0x10, 0x10, 0x10, 0x1F, 0x10,
			0x10, 0x10, 0x10, 0xF0, 0x10,
			0x00, 0x00, 0x00, 0xFF, 0x10,
			0x10, 0x10, 0x10, 0x10, 0x10,
			0x10, 0x10, 0x10, 0xFF, 0x10,
			0x00, 0x00, 0x00, 0xFF, 0x14,
			0x00, 0x00, 0xFF, 0x00, 0xFF,
			0x00, 0x00, 0x1F, 0x10, 0x17,
			0x00, 0x00, 0xFC, 0x04, 0xF4,
			0x14, 0x14, 0x17, 0x10, 0x17,
			0x14, 0x14, 0xF4, 0x04, 0xF4,
			0x00, 0x00, 0xFF, 0x00, 0xF7,
			0x14, 0x14, 0x14, 0x14, 0x14,
			0x14, 0x14, 0xF7, 0x00, 0xF7,
			0x14, 0x14, 0x14, 0x17, 0x14,
			0x10, 0x10, 0x1F, 0x10, 0x1F,
			0x14, 0x14, 0x14, 0xF4, 0x14,
			0x10, 0x10, 0xF0, 0x10, 0xF0,
			0x00, 0x00, 0x1F, 0x10, 0x1F,
			0x00, 0x00, 0x00, 0x1F, 0x14,
			0x00, 0x00, 0x00, 0xFC, 0x14,
			0x00, 0x00, 0xF0, 0x10, 0xF0,
			0x10, 0x10, 0xFF, 0x10, 0xFF,
			0x14, 0x14, 0x14, 0xFF, 0x14,
			0x10, 0x10, 0x10, 0x1F, 0x00,
			0x00, 0x00, 0x00, 0xF0, 0x10,
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
			0xFF, 0xFF, 0xFF, 0x00, 0x00,
			0x00, 0x00, 0x00, 0xFF, 0xFF,
			0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
			0x38, 0x44, 0x44, 0x38, 0x44,
			0xFC, 0x4A, 0x4A, 0x4A, 0x34,
			0x7E, 0x02, 0x02, 0x06, 0x06,
			0x02, 0x7E, 0x02, 0x7E, 0x02,
			0x63, 0x55, 0x49, 0x41, 0x63,
			0x38, 0x44, 0x44, 0x3C, 0x04,
			0x40, 0x7E, 0x20, 0x1E, 0x20,
			0x06, 0x02, 0x7E, 0x02, 0x02,
			0x99, 0xA5, 0xE7, 0xA5, 0x99,
			0x1C, 0x2A, 0x49, 0x2A, 0x1C,
			0x4C, 0x72, 0x01, 0x72, 0x4C,
			0x30, 0x4A, 0x4D, 0x4D, 0x30,
			0x30, 0x48, 0x78, 0x48, 0x30,
			0xBC, 0x62, 0x5A, 0x46, 0x3D,
			0x3E, 0x49, 0x49, 0x49, 0x00,
			0x7E, 0x01, 0x01, 0x01, 0x7E,
			0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
			0x44, 0x44, 0x5F, 0x44, 0x44,
			0x40, 0x51, 0x4A, 0x44, 0x40,
			0x40, 0x44, 0x4A, 0x51, 0x40,
			0x00, 0x00, 0xFF, 0x01, 0x03,
			0xE0, 0x80, 0xFF, 0x00, 0x00,
			0x08, 0x08, 0x6B, 0x6B, 0x08,
			0x36, 0x12, 0x36, 0x24, 0x36,
			0x06, 0x0F, 0x09, 0x0F, 0x06,
			0x00, 0x00, 0x18, 0x18, 0x00,
			0x00, 0x00, 0x10, 0x10, 0x00,
			0x30, 0x40, 0xFF, 0x01, 0x01,
			0x00, 0x1F, 0x01, 0x01, 0x1E,
			0x00, 0x19, 0x1D, 0x17, 0x12,
			0x00, 0x3C, 0x3C, 0x3C, 0x3C,
			0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint32_t initcmd[] = {
  0xEF, 3, 0x03, 0x80, 0x02,
  0xCF, 3, 0x00, 0xC1, 0x30,
  0xED, 4, 0x64, 0x03, 0x12, 0x81,
  0xE8, 3, 0x85, 0x00, 0x78,
  0xCB, 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
  0xF7, 1, 0x20,
  0xEA, 2, 0x00, 0x00,
  ILI9341_PWCTR1  , 1, 0x23,
  ILI9341_PWCTR2  , 1, 0x10,
  ILI9341_VMCTR1  , 2, 0x3e, 0x28,
  ILI9341_VMCTR2  , 1, 0x86,
  ILI9341_MADCTL  , 1, 0x48,
  ILI9341_VSCRSADD, 1, 0x00,
  ILI9341_PIXFMT  , 1, 0x55,
  ILI9341_FRMCTR1 , 2, 0x00, 0x18,
  ILI9341_DFUNCTR , 3, 0x08, 0x82, 0x27,
  0xF2, 1, 0x00,
  ILI9341_GAMMASET , 1, 0x01,
  ILI9341_GMCTRP1 , 15, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
    0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
  ILI9341_GMCTRN1 , 15, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
    0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
  ILI9341_SLPOUT  , 0x80,
  ILI9341_DISPON  , 0x80,
  0x00
};



void sendCommand(uint8_t cmd) {
	while((SPI2 -> SR & SPI_SR_BSY));
	GPIOA -> BRR = 1 << 8;
    write8Bits(cmd);
	while((SPI2 -> SR & SPI_SR_BSY));
	GPIOA -> BSRR = 1 << 8;
}



void sendPixel(int16_t x, int16_t y, uint16_t color) {
    if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height)){
    	return;
    }
    setAddressWindow(x, y, 1, 1);
    write16Bits(color);
}


void sendColor(uint16_t color, uint32_t length) {
    uint8_t upper = color >> 8;
    uint8_t lower = color;
    for (uint32_t i = length; i; i--) {
    	write8Bits(upper);
    	write8Bits(lower);
    }
    return;
}


void GPIOBinit(){
	RCC -> AHBENR  |= RCC_AHBENR_GPIOBEN;

	GPIOB -> MODER &= ~(0x3) << (2*12);
	GPIOB -> MODER &= ~(0x3) << (2*13);
	GPIOB -> MODER &= ~(0x3) << (2*14);
	GPIOB -> MODER &= ~(0x3) << (2*15);

	GPIOB -> MODER |=  (0x2) << (2*12);
	GPIOB -> MODER |=  (0x2) << (2*13);
	GPIOB -> MODER |=  (0x2) << (2*14);
	GPIOB -> MODER |=  (0x2) << (2*15);

	GPIOB->AFR[1] &= ~0xFFFFFFFF;
}

void SPIinit(void) {
	RCC -> APB1ENR |= RCC_APB1ENR_SPI2EN;
	GPIOBinit();

	SPI2 -> CR1 |= SPI_CR1_BIDIMODE;
	SPI2 -> CR1 |= SPI_CR1_BIDIOE;
	SPI2 -> CR1 |= SPI_CR1_MSTR;
	SPI2 -> CR1 &= ~SPI_CR1_BR;

	SPI2 -> CR2 |= SPI_CR2_DS_0;
	SPI2 -> CR2 |= SPI_CR2_DS_1;
	SPI2 -> CR2 |= SPI_CR2_DS_2;
	SPI2 -> CR2 |= SPI_CR2_SSOE;
	SPI2 -> CR2 |= SPI_CR2_NSSP;

	SPI2 -> CR1 |= SPI_CR1_SPE;
}

void write16Bits(uint16_t tx_data) {
	while((SPI2 -> SR & SPI_SR_TXE) != SPI_SR_TXE);
	SPI2 -> DR = tx_data;
}

void write8Bits(uint8_t tx_data) {
	while((SPI2 -> SR & SPI_SR_TXE) != SPI_SR_TXE);
	*((char *) &(SPI2 -> DR)) = tx_data;
}


void reset(){//hard reset
	while((SPI2 -> SR & SPI_SR_BSY));
	//Pull LOW
	GPIOA -> ODR &= ~(1 << 9);
	nano_wait(1E8);
	GPIOA -> ODR |= 1  << 9;
	nano_wait(1E8);
}


void GPIOAinit(void) {
	RCC -> AHBENR  |= RCC_AHBENR_GPIOAEN;
	GPIOA -> MODER |= 1 << 16; // PA8 set to output D/C
	GPIOA -> MODER |= 1 << 18; // PA9 IS RST
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR8_0;
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR9_0;
	GPIOA -> ODR   |= 1 << 9;
}

void write32Bits(uint32_t tx_data) {
	write8Bits((tx_data) >> 24);
	write8Bits((tx_data) >> 16);
	write8Bits((tx_data) >> 8);
	write8Bits((tx_data));
}


void begin(void) {
	uint32_t  cmd, x, numArgs;
	const uint32_t *addr = initcmd;
	while((cmd = readAddr(addr++)) > 0) {
		sendCommand(cmd);
		x = *addr;
		addr++;
		numArgs = x & 0x7F;
		while(numArgs--) {
			write8Bits(*addr);
			addr++;
		}
		if(x & 0x80){
			nano_wait(120000);
		}

	}
}

void nano_wait(int t) {
    asm("       mov r0,%0\n"
        "repeat:\n"
        "       sub r0,#83\n"
        "       bgt repeat\n"
        : : "r"(t) : "r0", "cc");
}

uint32_t readAddr(const uint32_t* addr) {
	return *addr;
}


void lcd_clear(uint16_t color){
	uint16_t i, j;
	setAddressWindow(0, 0, _width-1, _height-1);

	for(i=0; i<_width; i++){
		for (j=0; j<_height; j++){
			write16Bits(color);
		}
	}
}



void setDisplay(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    if((x >= _width) || (y >= _height)){
    	return;
    }

    int16_t x2 = x + w - 1, y2 = y + h - 1;

    if((x2 < 0) || (y2 < 0)){
    	return;
    }

    if(x < 0) {
        x = 0;
        w = x2 + 1;
    }

    if(y < 0) {
        y = 0;
        h = y2 + 1;
    }

    if(x2 >= _width){
    	w = _width  - x;
    }

    if(y2 >= _height){
    	h = _height - y;
    }

    int32_t len = (int32_t)w * h;
    setAddressWindow(x, y, w, h);
    sendColor(color, len);
}


void dispChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {
	if((x >= _width) ||	(y >= _height) || ((x + 6 * size - 1) < 0) || ((y + 8 * size - 1) < 0)){
		return;
	}

	for(int8_t i=0; i<5; i++ ) {
		uint8_t* array_hold =  &font[c * 5 + i];
		uint8_t line = (*array_hold);
		for(int8_t j=0; j<8; j++, line >>= 1) {
			if(line & 1) {
				if(size == 1){
					sendPixel(y-j, x+i, color);
				}
				else{
					setDisplay(y-j*size, x+i*size, size, size, color);
				}

			}
		}
	}
}

void setAddressWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    uint32_t xa = ((uint32_t)x << 16) | (x+w-1);
    uint32_t ya = ((uint32_t)y << 16) | (y+h-1);
    sendCommand(ILI9341_CASET); // Column addr set
    write32Bits(xa);
    sendCommand(ILI9341_PASET); // Row addr set
    write32Bits(ya);
    sendCommand(ILI9341_RAMWR); // write to RAM
}
