#include "TCS.h"

uint8_t _tcs34725Initialised = 0;

void write8(uint8_t reg, uint32_t value) {
    uint8_t txBuffer[2];
    txBuffer[0] = TCS34725_COMMAND_BIT | reg;
    txBuffer[1] = value & 0xFF;
    HAL_I2C_Master_Transmit(&hi2c1, TCS34725_ADDRESS, txBuffer, 2, 100);
}

uint8_t read8(uint8_t reg) {
    uint8_t value;
    uint8_t tx = TCS34725_COMMAND_BIT | reg;
    HAL_I2C_Master_Transmit(&hi2c1, TCS34725_ADDRESS, &tx, 1, 100);
    HAL_I2C_Master_Receive(&hi2c1, TCS34725_ADDRESS, &value, 1, 100);
    return value;
}

uint16_t read16(uint8_t reg) {
    uint8_t tx = TCS34725_COMMAND_BIT | reg;
    uint8_t rx[2];
    HAL_I2C_Master_Transmit(&hi2c1, TCS34725_ADDRESS, &tx, 1, 100);
    HAL_I2C_Master_Receive(&hi2c1, TCS34725_ADDRESS, rx, 2, 100);
    return (rx[1] << 8) | rx[0];
}

void enable(void) {
    write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);
    HAL_Delay(3);
    write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
}

void disable(void) {
    uint8_t reg = read8(TCS34725_ENABLE);
    write8(TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
}

void setIntegrationTime(uint8_t it) {
    write8(TCS34725_ATIME, it);
}

void setGain(uint8_t gain) {
    write8(TCS34725_CONTROL, gain);
}

void tcs34725_init(void) {
    uint8_t id = read8(TCS34725_ID);
    if (id != 0x44 && id != 0x10) return;
    _tcs34725Initialised = 1;
    setIntegrationTime(TCS34725_INTEGRATIONTIME_50MS);
    setGain(TCS34725_GAIN_4X);
    enable();
}

void getRawData(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c) {
    *c = read16(TCS34725_CDATAL);
    *r = read16(TCS34725_RDATAL);
    *g = read16(TCS34725_GDATAL);
    *b = read16(TCS34725_BDATAL);
}

void getRGB(int *R, int *G, int *B) {
    uint16_t r, g, b, c;
    getRawData(&r, &g, &b, &c);

    if (c == 0) c = 1;

    *R = (int)((float)r / c * 255.0);
    *G = (int)((float)g / c * 255.0);
    *B = (int)((float)b / c * 255.0);
}

