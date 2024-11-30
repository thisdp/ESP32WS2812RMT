#include <vector>

#include <Arduino.h>
#include <Ticker.h>

#include <esp32WS2812.h>

WS2812 WS2812(18, 50);
std::vector<WS2812Effect*> effects;
Ticker timer;

void nextEffect() {
  Serial.print("starting next effect\n");
  WS2812.startEffect(effects[random(0, effects.size())]);
}

void setup() {
  delay(5000);
  Serial.begin(115200);
  Serial.println("Booting");

  // add effects
  effects.push_back(new Circus(1000));
  effects.push_back(new SnowSparkle({82, 56, 13}, 3, 100, 500));
  effects.push_back(new Aurora);

  // output enable level shifter
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);

  // start led strip
  WS2812.begin();

  // effect starts in 15 seconds...
  timer.attach(15, nextEffect);
}

void loop() {
  // nothing to do here
  delay(1);
}
