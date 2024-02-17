#include <Arduino.h>

const int togglePin = 2;
bool current_state;
bool preveous_state = false;

unsigned long change_time_list[100] = {0};
unsigned long change_value_list[100] = {0};
uint16_t change_index = 0;
unsigned long last_state_change = 0;

void setup() {
  Serial.begin(1000000);
  while (!Serial) {

  }

  Serial.println("Starting");

  pinMode(togglePin, INPUT);
  current_state = digitalRead(togglePin);
  preveous_state = current_state;
  last_state_change = micros();
}

void loop() {
  current_state = digitalRead(togglePin);
  if (preveous_state != current_state) {
    change_time_list[change_index] = micros();
    change_value_list[change_index] = current_state;
    preveous_state = current_state;
    last_state_change = micros();
    change_index++;
    if(change_index > 100){
      change_index = 0;
      for (uint16_t i = 0; i < change_index; i++) {
        Serial.print(change_time_list[i]);
        Serial.print("\t");
        Serial.println(change_value_list[i]);
      }
      change_index = 0;
      memset(change_time_list, 0, sizeof(change_time_list));
      memset(change_value_list, 0, sizeof(change_value_list));
    }
  }
  if(micros() - last_state_change > 1000000 && change_index > 0){
    Serial.println("CAPTURED PACKET:");
    for (uint16_t i = 0; i < change_index; i++) {
      Serial.print(change_time_list[i]);
      Serial.print("\t");
      Serial.println(change_value_list[i]);
    }
    change_index = 0;
    memset(change_time_list, 0, sizeof(change_time_list));
    memset(change_value_list, 0, sizeof(change_value_list));
  }
}