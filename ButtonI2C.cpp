/*

*/
#include "ButtonI2C.h"

ButtonI2C::ButtonI2C(uint8_t address, uint8_t irq_pin){
  adr = address;
  irq = irq_pin;  
}

void ButtonI2C::begin(){
  Wire.begin();
  value(0);
  led(2);
}

int32_t ButtonI2C::value(){
  int32_t val;
  readReg(REGISTER_VALUE, &val, sizeof(val));
  return val;
}

int32_t ButtonI2C::value(int32_t val){
  writeReg(REGISTER_VALUE, &val, sizeof(val));
  return val;
}

uint8_t ButtonI2C::state(){
  return 0;
}

void ButtonI2C::setMax(int32_t max){}
void ButtonI2C::setMin(int32_t min){}

bool ButtonI2C::button(int8_t id){
  return buttons() & (1<< id);
}

uint8_t ButtonI2C::buttons(){
  uint8_t state;
  readReg(REGISTER_STATE, &state);
  return state;
}

uint8_t ButtonI2C::pressed(){
  uint8_t pressed;
  uint8_t nula = 0;
  readReg(REGISTER_PRESSED, &pressed);
  writeReg(REGISTER_PRESSED, &nula);
  return pressed;
}
uint8_t ButtonI2C::released(){
  uint8_t released;
  readReg(REGISTER_RELEASED, &released);
  return released;
}

void ButtonI2C::led(uint8_t val){
  writeReg(REGISTER_LED, &val);
}

void ButtonI2C::doWork(){}

void ButtonI2C::dump(Print &stream){
  byte buff[20];
  byte n;
  Wire.beginTransmission(adr);
  Wire.write(0);
  Wire.endTransmission();
  n = Wire.requestFrom(adr, (uint8_t) 20);
  Wire.readBytes(buff, n);
  for(byte i=0; i<n; i++){
    stream.print("0x");
    stream.print(buff[i], HEX);
    stream.print(", ");  
  }
  stream.println();
}

void ButtonI2C::writeReg(uint8_t reg, void *data, uint8_t len){
  Wire.beginTransmission(adr);
  Wire.write(reg);
  Wire.write((uint8_t*) data, len);
  Wire.endTransmission();
}

uint8_t ButtonI2C::readReg(uint8_t reg, void *data, uint8_t len){
  Wire.beginTransmission(adr);
  Wire.write(reg);
  Wire.endTransmission();
  uint8_t n = Wire.requestFrom(adr, len);
  Wire.readBytes((uint8_t*) data, n);
  return n;
}
