#include <Arduino.h>
#include <esp_task_wdt.h>

#include "task_manager.h"

extern TaskHandle_t loop2TaskHandle;

void setup() {
  esp_task_wdt_init(60, true);  // time in seconds
  enableLoopWDT();

  Serial.begin(115200);
  delay(100);

  // put your setup code here, to run once:
  Serial.println("Setup 1");
  createTask2();
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t valueToSend = 0;
  uint32_t receivedValue;

  if (xTaskNotify(loop2TaskHandle, valueToSend, eSetValueWithoutOverwrite) ==
      pdTRUE) {
    valueToSend++;
    if (xTaskNotifyWait(0, ULONG_MAX, &receivedValue, 1000) == pdFAIL) {
      Serial.println("error, task2 do not response");
    }
  }
}
