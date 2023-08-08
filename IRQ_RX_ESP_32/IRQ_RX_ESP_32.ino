/*

Demonstrates simple RX operation with an ESP32.
Any of the Basic_TX examples can be used as a transmitter.

ESP's require the use of '__attribute__((packed))' on the RadioPacket data structure
to ensure the bytes within the structure are aligned properly in memory.

The ESP32 SPI library supports configurable SPI pins and NRFLite's mechanism to support this is shown.

Radio    ESP32 module
CE    -> 4
CSN   -> 5
MOSI  -> 23
MISO  -> 19
SCK   -> 18
IRQ   -> No connection
VCC   -> No more than 3.6 volts
GND   -> GND

*/

#include "SPI.h"
#include "NRFLite.h"
#include <esp_sleep.h>


const static uint8_t RADIO_ID = 0;
const static uint8_t PIN_RADIO_CE = 4;
const static uint8_t PIN_RADIO_CSN = 5;
const static uint8_t PIN_RADIO_MOSI = 23;
const static uint8_t PIN_RADIO_MISO = 19;
const static uint8_t PIN_RADIO_SCK = 18;
const static uint8_t PIN_RADIO_IRQ = 17;


struct __attribute__((packed)) RadioPacket // Note the packed attribute.
{
    uint8_t FromRadioId;
    uint32_t OnTimeMillis;
    uint32_t FailedTxCount;
};


NRFLite _radio;
RadioPacket _radioData;

volatile uint8_t _dataWasReceived; // Note usage of volatile since the variable is used in the radio interrupt
                                   // while also being used outside the interrupt.

void setup()
{   
  Serial.begin(115200);
    
  // Configure SPI pins.
  SPI.begin(PIN_RADIO_SCK, PIN_RADIO_MISO, PIN_RADIO_MOSI, PIN_RADIO_CSN);
  
  // Indicate to NRFLite that it should not call SPI.begin() during initialization since it has already been done.
  uint8_t callSpiBegin = 0;
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE2MBPS, 100, callSpiBegin))
  {
      Serial.println("Cannot communicate with radio");
      while (1); // Wait here forever.
  }

  pinMode(PIN_RADIO_IRQ, INPUT_PULLUP);
  // Configure the wakeup source and sleep for the first time
  esp_sleep_enable_ext0_wakeup((gpio_num_t)PIN_RADIO_IRQ, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_RADIO_IRQ), radioInterrupt, FALLING);
  //lcd.noBacklight();  // Turn off LCD backlight before going to sleep
    
  Serial.println("Going to sleep");
  delay(20000);
  esp_light_sleep_start();

}



void loop()
{
  esp_sleep_enable_ext0_wakeup((gpio_num_t)PIN_RADIO_IRQ, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_RADIO_IRQ), radioInterrupt, FALLING);
  //lcd.noBacklight();  // Turn off LCD backlight before going to sleep
    
  Serial.println("Going to sleep");
  delay(20000);
  

  sleepagain();
}

void radioInterrupt()
{
  Serial.println("I'm waken up");
  detachInterrupt(digitalPinToInterrupt(PIN_RADIO_IRQ));
  // Serial.println("I'm going to sleep now");
  attachInterrupt(digitalPinToInterrupt(PIN_RADIO_IRQ), sleepagain, FALLING);
   delay(10000);
  //esp_light_sleep_start();
}
void sleepagain()
{ 
  Serial.println("I'm going to sleep now");
  detachInterrupt(digitalPinToInterrupt(PIN_RADIO_IRQ));
  attachInterrupt(digitalPinToInterrupt(PIN_RADIO_IRQ), radioInterrupt, FALLING);
  delay(5000);
  esp_light_sleep_start();

}
