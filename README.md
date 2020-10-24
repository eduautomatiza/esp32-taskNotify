# esp32-task-example

Example of taskNotify(), freeRTOS, for ESP32 running two tasks.


The project uses [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode), [Visual Studio Code](https://code.visualstudio.com/) and [arduino framework for espressif32 platform](https://github.com/espressif/arduino-esp32);


**first task, main.cpp:**
```C++
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

```


**second task, task_2.cpp:**
```C++
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
```
