#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <NRFLite.h>

#define LED_PIN 14

const static uint8_t RADIO_ID = 0;
const static uint8_t PIN_RADIO_CE = 4;
const static uint8_t PIN_RADIO_CSN = 5;
const static uint8_t PIN_RADIO_SCK = 18;
const static uint8_t PIN_RADIO_IRQ = 17;
const static uint8_t PIN_RADIO_MISO = 19;
const static uint8_t PIN_RADIO_MOSI = 23;

//LiquidCrystal_I2C lcd(0x27, 16, 2);
NRFLite _radio;
volatile uint8_t _dataWasReceived;

void setup() {
  // lcd.init();
  // lcd.backlight();
  Serial.begin(115200);
  Wire.begin();
  pinMode(LED_PIN, OUTPUT);

  // NRF24L01 initialization
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)) {
    Serial.println("Cannot communicate with radio");
    while (1); // Wait here forever.
  }

  // Attach interrupt to the IRQ pin of NRF24L01
  attachInterrupt(digitalPinToInterrupt(PIN_RADIO_IRQ), radioInterrupt, FALLING);

  // Configure the wakeup source and sleep for the first time
  esp_sleep_enable_ext0_wakeup((gpio_num_t)PIN_RADIO_IRQ, FALLING);
 // lcd.noBacklight();  // Turn off LCD backlight before going to sleep
  esp_deep_sleep_start();
}

void loop() {
  // if (_dataWasReceived) {
  //   _dataWasReceived = false;

  //   while (_radio.hasDataISR()) {
  //     uint8_t data;
  //     _radio.readData(&data);
  //     lcd.clear();
  //     lcd.print("Received data:");
  //     lcd.setCursor(0, 1);
  //     lcd.print(data);
      
  // }
}

void radioInterrupt() {
  // Ask the radio what caused the interrupt. This also resets the IRQ pin on the
  // radio so a new interrupt can be triggered.

  uint8_t txOk, txFail, rxReady;
  _radio.whatHappened(txOk, txFail, rxReady);
  // Serial.print("Received data:");
  //     Serial.println(data);
  //   }

   // lcd.backlight(); // Turn on LCD backlight when ESP32 wakes up
    // Go back to sleep
    esp_sleep_enable_ext0_wakeup((gpio_num_t)PIN_RADIO_IRQ, FALLING);
    esp_deep_sleep_start();
    digitalWrite(LED_PIN, 1);

//   if (rxReady) {
//     _dataWasReceived = true;
//   }
 }
