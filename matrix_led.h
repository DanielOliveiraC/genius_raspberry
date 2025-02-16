#ifndef MATRIX_LED_H
#define MATRIX_LED_H

void npInit(uint pin);
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);
void npClear();
void npWrite();
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);

#endif