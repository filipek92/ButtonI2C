/*

*/
#ifndef ButtonI2C_h
#define ButtonI2C_h

#include "Arduino.h"
#include <Wire.h>

#define REGISTER_STATE      0
#define REGISTER_PRESSED    1
#define REGISTER_RELEASED   2
#define REGISTER_LED        3
#define REGISTER_VALUE      8

class ButtonI2C
{
  public:
    ButtonI2C(uint8_t address=0x70, uint8_t irq_pin=-1);
    void begin();

    int32_t value();
    int32_t value(int32_t val);
    uint8_t state();

    void setMax(int32_t max);
    void setMin(int32_t min);

    bool button(int8_t id);

    uint8_t buttons();
    uint8_t pressed();
    uint8_t released();

    void led(uint8_t val);

    void doWork();
    void dump(Print &stream);
  private:
    uint8_t adr;
    uint8_t irq;

    uint8_t readReg(uint8_t reg, void *data, uint8_t len=1);
    void writeReg(uint8_t reg, void *data, uint8_t len=1);
};

#endif
