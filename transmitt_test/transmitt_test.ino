

#include <Arduino.h>

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Samsung.h>
 
// eeprom
#define EEPROM_SIZE 150
#include <EEPROM.h>
int address = 100;
int state = 0;

int cycleaddres = 90;
int cycles = 1;


  const uint16_t kSendPin = 4;  // GPIO with IR LED
  const int kTransmissionDelay = 100;   // Delay duration after IR command
  
  char serial_input; // Stores serial input

IRsend irsend(kSendPin);

void send_ir_code(char serial_input) {
  
  if (serial_input == 'p') {
    Serial.println("transmitting command for off");
    irsend.sendSAMSUNG(0xE0E019E6, 32, 1); // off
    delay(kTransmissionDelay);
  } else if (serial_input == 'o') {
    // menu
    irsend.sendSAMSUNG(0xE0E09966, 32, 1); // on
    delay(kTransmissionDelay);
    Serial.println("sent: on");
  } else if (serial_input == 'l') {
    // menu
    irsend.sendSAMSUNG(0xE0E0807F, 32, 1); // source
    delay(kTransmissionDelay);
    Serial.println("sent: source");
  } else if (serial_input == 'm') {
    // menu
    irsend.sendSAMSUNG(0xE0E058A7, 32, 1); // menu
    delay(kTransmissionDelay);
    Serial.println("sent: menu");
  } else if (serial_input == 'e') {
    // menu
    irsend.sendSAMSUNG(0xE0E016E9, 32, 1); // enter
    delay(kTransmissionDelay);
    Serial.println("sent: enter");
  } else if (serial_input == 'r') {
    // menu
    irsend.sendSAMSUNG(0xE0E01AE5, 32, 1); // return
    delay(kTransmissionDelay);
    Serial.println("sent: return");
  } else if (serial_input == 'q') {
    // menu
    irsend.sendSAMSUNG(0xE0E0B44B, 32, 1); // exit
    delay(kTransmissionDelay);
    Serial.println("sent: exit");
  } else if (serial_input == 'w') {
    // menu
    irsend.sendSAMSUNG(0xE0E006F9, 32, 1); // up
    delay(kTransmissionDelay);
    Serial.println("sent: up");
  } else if (serial_input == 'a') {
    // menu
    irsend.sendSAMSUNG(0xE0E0A659, 32, 1); // left
    delay(kTransmissionDelay);
    Serial.println("sent: left");
  } else if (serial_input == 's') {
    // menu
    irsend.sendSAMSUNG(0xE0E08679, 32, 1); // down
    delay(kTransmissionDelay);
    Serial.println("sent: down");
  } else if (serial_input == 'd') {
    // menu
    irsend.sendSAMSUNG(0xE0E046B9, 32, 1); // right
    delay(kTransmissionDelay);
    Serial.println("sent: right");
  } 
    

}

void setup() {
  Serial.begin(115200);  // todo: try Serial.begin(115200, SERIAL_8N1);
  Serial.println(F("Initialize System"));
  EEPROM.begin(EEPROM_SIZE);


  
  
  EEPROM.get(address, state);
  Serial.print("Read status = ");
  Serial.println(state);


  EEPROM.get(cycleaddres, cycles);
  Serial.print("Write cycles = ");
  Serial.println(cycles);
  cycles++;
  EEPROM.put(cycleaddres, cycles);
  EEPROM.commit();



  irsend.begin();
  int delayDuration = 100; // Define the delay duration
  send_ir_code('o');
  delay(1500);
  send_ir_code('l');
  delay(delayDuration);
  send_ir_code('a');
  delay(delayDuration);
  send_ir_code('a');
  delay(delayDuration);
  send_ir_code('a');

  if(state == 0){
    delay(delayDuration);
    send_ir_code('d');
  }

  delay(delayDuration);
  send_ir_code('e');
  delay(delayDuration);
  send_ir_code('r');

  if (state < 1) {
    state = 1;
  }else if (state > 0){
    state = 0;
  }
  EEPROM.put(address, state);
  EEPROM.commit();
  Serial.print("new state writen to eeprom: ");
  Serial.println(state);

}

void loop() {
  Serial.println("deep sleep");
    ESP.deepSleep(30e6); 
}