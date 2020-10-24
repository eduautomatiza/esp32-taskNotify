#include <Arduino.h>

#include "task_manager.h"

extern TaskHandle_t loopTaskHandle;

void setup2(void) {
  enableLoop2WDT();

  // put your setup code here, to run once:
  Serial.println("Setup 2");
}

void loop2(void) {
  // put your main code here, to run repeatedly:
  uint32_t receivedValue;

  if (xTaskNotifyWait(0, ULONG_MAX, &receivedValue, 1000) == pdPASS) {
    xTaskNotify(loopTaskHandle, receivedValue, eSetValueWithOverwrite);
  }
}
