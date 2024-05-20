/**
 * @example button_trigger_mode.ino
 */

#include <Arduino.h>
#include <Wire.h>

#include "speech_recognizer.h"

emakefun::SpeechRecognizer g_speech_recognizer(emakefun::SpeechRecognizer::kDefaultI2cAddress);

String EventToString(emakefun::SpeechRecognizer::Event event) {
  switch (event) {
    case emakefun::SpeechRecognizer::kEventStartWaitingForTrigger:
      return F("kEventStartWaitingForTrigger");
    case emakefun::SpeechRecognizer::kEventStartRecognizing:
      return F("kEventStartRecognizing");
    case emakefun::SpeechRecognizer::kEventSpeechRecognized:
      return F("kEventSpeechRecognized");
    case emakefun::SpeechRecognizer::kEventSpeechRecognitionTimedOut:
      return F("kEventSpeechRecognitionTimedOut");
    case emakefun::SpeechRecognizer::kEventButtonTriggered:
      return F("kEventButtonTriggered");
    case emakefun::SpeechRecognizer::kEventKeywordTriggered:
      return F("kEventKeywordTriggered");
    default:
      return F("");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  Wire.begin();
  const auto ret = g_speech_recognizer.Initialize(&Wire);
  if (0 == ret) {
    Serial.println(F("speech recognizer initialization was successful"));
  } else {
    Serial.println(String(F("speech recognizer initialization failed: ")) + ret);
    while (true)
      ;
  }
  g_speech_recognizer.SetRecognitionMode(emakefun::SpeechRecognizer::kButtonTrigger);
  g_speech_recognizer.SetTimeout(10000);
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

  if (g_speech_recognizer.GetEvent() != emakefun::SpeechRecognizer::kEventNone) {
    Serial.print("event: ");
    Serial.println(EventToString(g_speech_recognizer.GetEvent()));
  }
}
