#include "Effect.h"

WS2812Effect::WS2812Effect() :
  _task(nullptr),
  _ledstrip(nullptr) {}

WS2812Effect::~WS2812Effect() {
  stop();
}

void WS2812Effect::start(WS2812* ledstrip) {
  _ledstrip = ledstrip;
  xTaskCreate((TaskFunction_t)&_effectTask, "effectTask", 2048, this, 1, &_task);
}

void WS2812Effect::stop() {
  if (!_task) return;
  vTaskDelete(_task);
  _cleanup();
}

void WS2812Effect::_effectTask(WS2812Effect* e) {
  e->_setup();
  while(1) {
    e->_loop();
  }
  vTaskDelete(nullptr);
}
