/**
 * @example simple_example.ino
 */
#include <Arduino.h>
#include <Wire.h>

#include "speech_recognizer.h"
namespace {
emakefun::SpeechRecognizer g_speech_recognizer(emakefun::SpeechRecognizer::kDefaultI2cAddress);
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("setup"));
  Wire.begin();
  const auto ret = g_speech_recognizer.Initialize(&Wire);
  if (0 == ret) {
    Serial.println(F("speech recognizer initialization was successful"));
  } else {
    Serial.println(String(F("speech recognizer initialization failed: ")) + ret);
    while (true)
      ;
  }
  g_speech_recognizer.AddKeyword(0, F("xiao yi xiao yi"));
  g_speech_recognizer.AddKeyword(1, F("bei jing"));
  g_speech_recognizer.AddKeyword(2, F("shang hai"));
  g_speech_recognizer.AddKeyword(3, F("cheng du"));
  Serial.println(F("setup was successful"));
}

void loop() {
  const auto result = g_speech_recognizer.Recognize();
  if (result >= 0) {
    Serial.print(F("result: "));
    Serial.println(result);
  }
}
