#include "i2c_device.h"

#include <Arduino.h>
#include <Wire.h>

namespace emakefun {

I2cDevice::I2cDevice(const uint8_t i2c_address) : i2c_address_(i2c_address) {
}

bool I2cDevice::Initialize() {
  Wire.begin();
  return true;
}

size_t I2cDevice::WriteByte(const uint8_t address, const uint8_t data) {
  Wire.beginTransmission(i2c_address_);
  Wire.write(address);
  Wire.write(data);
  if (0 != Wire.endTransmission()) {
    return 0;
  } else {
    return 1;
  }
}

size_t I2cDevice::WriteBytes(const uint8_t address, const void* data, const size_t length) {
  Wire.beginTransmission(i2c_address_);
  Wire.write(address);
  size_t ret = Wire.write(reinterpret_cast<const uint8_t*>(data), length);
  if (0 != Wire.endTransmission()) {
    return 0;
  } else {
    return ret;
  }
}

uint8_t I2cDevice::ReadByte(const uint8_t address) {
  Wire.beginTransmission(i2c_address_);
  Wire.write(address);
  if (0 != Wire.endTransmission()) {
    return 0;
  }

  Wire.requestFrom(i2c_address_, static_cast<uint8_t>(1));
  if (Wire.available()) {
    return Wire.read();
  }

  return 0;
}

size_t I2cDevice::ReadBytes(const uint8_t address, void* const buffer, const size_t length) {
  Wire.beginTransmission(i2c_address_);
  Wire.write(address);
  if (0 != Wire.endTransmission()) {
    return 0;
  }

  Wire.requestFrom(i2c_address_, length);
  if (Wire.available()) {
    return Wire.readBytes(reinterpret_cast<uint8_t*>(buffer), length);
  }

  return 0;
}

}  // namespace emakefun