#include "speech_recognizer.h"

#include <Arduino.h>
#include <Wire.h>

#define VERSION (1)

namespace emakefun {
namespace {
enum DataAddress : uint8_t {
  kDataAddressVersion = 0x00,
  kDataAddressBusy = 0x01,
  kDataAddressReset = 0x02,
  kDataAddressRecognitionMode = 0x03,
  kDataAddressResult = 0x04,
  kDataAddressEvent = 0x06,
  kDataAddressTimeout = 0x08,
  kDataAddressKeywordIndex = 0x0C,
  kDataAddressKeywordData = 0x0D,
  kDataAddressKeywordLength = 0x3F,
  kDataAddressAddKeyword = 0x40,
  kDataAddressRecognize = 0x41,
};

enum Command : uint8_t {
  kCommandNone = 0,
  kReset,
  kAddIdentification,
  kSetTrigger,
  kSetTimeout,
};
}  // namespace

SpeechRecognizer::SpeechRecognizer(const uint8_t device_i2c_address) : i2c_device_(device_i2c_address) {
}

bool SpeechRecognizer::Initialize() {
  i2c_device_.Initialize();
  WaitUntilIdle();
  i2c_device_.WriteByte(kDataAddressReset, 1);
}

void SpeechRecognizer::SetRecognitionMode(const RecognitionMode recognition_mode) {
  WaitUntilIdle();
  i2c_device_.WriteByte(kDataAddressRecognitionMode, recognition_mode);
}

void SpeechRecognizer::SetTimeout(const uint32_t timeout_ms) {
  WaitUntilIdle();
  i2c_device_.WriteBytes(kDataAddressTimeout, &timeout_ms, sizeof(timeout_ms));
}

void SpeechRecognizer::AddKeyword(const uint8_t index, const String& identification) {
  WaitUntilIdle();
  i2c_device_.WriteByte(kDataAddressKeywordIndex, index);
  i2c_device_.WriteBytes(kDataAddressKeywordData, identification.c_str(), min(255, identification.length()));
  i2c_device_.WriteByte(kDataAddressKeywordLength, min(255, identification.length()));
  i2c_device_.WriteByte(kDataAddressAddKeyword, 1);
}

void SpeechRecognizer::Recognize() {
  WaitUntilIdle();
  i2c_device_.WriteByte(kDataAddressRecognize, 1);
}

int16_t SpeechRecognizer::GetResult() {
  uint8_t data[2] = {0};
  i2c_device_.ReadBytes(kDataAddressResult, data, sizeof(data));
  return ((int16_t)data[1] << 8) | data[0];
}

SpeechRecognizer::Event SpeechRecognizer::GetEvent() {
  return static_cast<SpeechRecognizer::Event>(i2c_device_.ReadByte(kDataAddressEvent));
}

void SpeechRecognizer::WaitUntilIdle() {
  while (i2c_device_.ReadByte(kDataAddressBusy) == 1) {
    yield();
  }
}
}  // namespace emakefun