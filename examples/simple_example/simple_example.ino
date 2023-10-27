/**
 * @example simple_example.ino
 */
#include <Arduino.h>
#include <Wire.h>

#include "speech_recognizer.h"

emakefun::SpeechRecognizer g_speech_recognizer(emakefun::SpeechRecognizer::kDefaultI2cAddress);

void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  g_speech_recognizer.Initialize();
  g_speech_recognizer.AddKeyword(0, F("xiao yi xiao yi"));
  g_speech_recognizer.AddKeyword(1, F("bei jing"));
  g_speech_recognizer.AddKeyword(2, F("shang hai"));
  g_speech_recognizer.AddKeyword(3, F("cheng du"));
  Serial.println("setup done");
}

void loop() {
  const auto result = g_speech_recognizer.Recognize();
  if (result >= 0) {
    Serial.print("result: ");
    Serial.println(result);
  }
}
