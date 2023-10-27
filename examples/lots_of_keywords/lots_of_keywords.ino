/**
 * @example lots_of_keywords.ino
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
  g_speech_recognizer.Initialize();
  g_speech_recognizer.SetRecognitionMode(emakefun::SpeechRecognizer::kRecognitionAuto);
  g_speech_recognizer.AddKeyword(0, F("xiao yi xiao yi"));
  g_speech_recognizer.AddKeyword(1, F("bei jing"));
  g_speech_recognizer.AddKeyword(2, F("chong qin"));
  g_speech_recognizer.AddKeyword(3, F("cheng du"));
  g_speech_recognizer.AddKeyword(4, F("shang hai"));
  g_speech_recognizer.AddKeyword(5, F("tian jin"));
  g_speech_recognizer.AddKeyword(6, F("wu han"));
  g_speech_recognizer.AddKeyword(7, F("nan jing"));
  g_speech_recognizer.AddKeyword(8, F("lan zhou"));
  g_speech_recognizer.AddKeyword(9, F("xian yang"));
  g_speech_recognizer.AddKeyword(10, F("cheng de"));
  g_speech_recognizer.AddKeyword(11, F("hang zhou"));
  g_speech_recognizer.AddKeyword(12, F("shen zhen"));
  g_speech_recognizer.AddKeyword(13, F("su zhou"));
  g_speech_recognizer.AddKeyword(14, F("taizhou"));
  g_speech_recognizer.AddKeyword(15, F("dalian"));
  g_speech_recognizer.AddKeyword(16, F("wu xi"));
  g_speech_recognizer.AddKeyword(17, F("he fei"));
  g_speech_recognizer.AddKeyword(18, F("chang sha"));
  g_speech_recognizer.AddKeyword(19, F("zheng zhou"));
  g_speech_recognizer.AddKeyword(20, F("qin huang dao"));
  g_speech_recognizer.AddKeyword(21, F("huaian"));
  g_speech_recognizer.AddKeyword(22, F("yan tai"));
  g_speech_recognizer.AddKeyword(23, F("zhu hai"));
  g_speech_recognizer.AddKeyword(24, F("sha men"));
  g_speech_recognizer.AddKeyword(25, F("fuzhou"));
  g_speech_recognizer.AddKeyword(26, F("nanning"));
  g_speech_recognizer.AddKeyword(27, F("lan zhou"));
  g_speech_recognizer.AddKeyword(28, F("gui lin"));
  g_speech_recognizer.AddKeyword(29, F("kun ming"));
  g_speech_recognizer.AddKeyword(30, F("xiang gang"));
  g_speech_recognizer.AddKeyword(31, F("ao men"));
  g_speech_recognizer.AddKeyword(32, F("tai bei"));
  g_speech_recognizer.AddKeyword(33, F("xin jiang"));
  g_speech_recognizer.AddKeyword(34, F("nei mong gu"));
  g_speech_recognizer.AddKeyword(35, F("liao ning"));
  g_speech_recognizer.AddKeyword(36, F("chao zhou"));
  g_speech_recognizer.AddKeyword(37, F("sui ning"));
  g_speech_recognizer.AddKeyword(38, F("qiqihaer"));
  g_speech_recognizer.AddKeyword(39, F("huang gang"));
  g_speech_recognizer.AddKeyword(40, F("wu lu mu qi"));
  g_speech_recognizer.AddKeyword(41, F("yan shan"));
  g_speech_recognizer.AddKeyword(42, F("xin xiang"));
  g_speech_recognizer.AddKeyword(43, F("da tuan"));
  g_speech_recognizer.AddKeyword(44, F("en shi"));
  g_speech_recognizer.AddKeyword(45, F("jiu jiang"));
  g_speech_recognizer.AddKeyword(46, F("fu yang"));
  g_speech_recognizer.AddKeyword(47, F("ji nan"));
  g_speech_recognizer.AddKeyword(48, F("jin hua"));
  g_speech_recognizer.AddKeyword(49, F("xi an"));
  Serial.println("setup done");
}

void loop() {
  const auto result = g_speech_recognizer.Recognize();
  if (result >= 0) {
    Serial.print("result: ");
    Serial.println(result);
  }

  if (g_speech_recognizer.GetEvent() != emakefun::SpeechRecognizer::kEventNone) {
    Serial.print("event: ");
    Serial.println(EventToString(g_speech_recognizer.GetEvent()));
  }
}
