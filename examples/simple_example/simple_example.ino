/**
 * @example simple_example.ino
 */
#include <Arduino.h>
#include <Wire.h>

#include "speech_recognizer.h"

emakefun::SpeechRecognizer g_speech_recognizer(0x30);

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
  g_speech_recognizer.Recognize();
  if (g_speech_recognizer.GetResult() >= 0) {
    Serial.print("result: ");
    Serial.println(g_speech_recognizer.GetResult());
  }
}
