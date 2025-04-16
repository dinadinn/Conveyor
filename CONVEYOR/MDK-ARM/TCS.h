#ifndef __TCS_H__
#define __TCS_H__

#include "stm32f4xx_hal.h"

#define TCS34725_ADDRESS          (0x29 << 1)
#define TCS34725_COMMAND_BIT      (0x80)
#define TCS34725_ENABLE           (0x00)
#define TCS34725_ENABLE_AEN       (0x02)
#define TCS34725_ENABLE_PON       (0x01)
#define TCS34725_ATIME            (0x01)
#define TCS34725_CONTROL          (0x0F)
#define TCS34725_ID               (0x12)
#define TCS34725_CDATAL           (0x14)
#define TCS34725_CDATAH           (0x15)
#define TCS34725_RDATAL           (0x16)
#define TCS34725_RDATAH           (0x17)
#define TCS34725_GDATAL           (0x18)
#define TCS34725_GDATAH           (0x19)
#define TCS34725_BDATAL           (0x1A)
#define TCS34725_BDATAH           (0x1B)

#define TCS34725_INTEGRATIONTIME_50MS   0xEB
#define TCS34725_GAIN_4X                0x01

extern I2C_HandleTypeDef hi2c1;

void write8(uint8_t reg, uint32_t value);
uint8_t read8(uint8_t reg);
uint16_t read16(uint8_t reg);
void enable(void);
void disable(void);
void setIntegrationTime(uint8_t it);
void setGain(uint8_t gain);
void tcs34725_init(void);
void getRawData(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c);
void getRGB(int *R, int *G, int *B);

#endif
