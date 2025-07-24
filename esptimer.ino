#include "esp_timer.h"

hw_timer_t *timer = NULL; // Timer handle
volatile bool flag = false; // Example flag

// Interrupt Service Routine (ISR)
void IRAM_ATTR onTimer() {
  flag = true; // Set flag to indicate timer interrupt
}

void setup() {
  Serial.begin(115200);

  // Initialize timer
  timer = timerBegin(0, 80, true); // Timer 0, prescaler 80 (1 MHz frequency), count up
  timerAttachInterrupt(timer, &onTimer, true); // Attach ISR
  timerAlarmWrite(timer, 10000000, true); // Set alarm to 1 second (1,000,000 ticks)
  timerAlarmEnable(timer); // Enable the alarm

}

void loop() {
      if (flag) {
    Serial.println("Timer Interrupt Triggered!");
    flag = false;
    }

}
