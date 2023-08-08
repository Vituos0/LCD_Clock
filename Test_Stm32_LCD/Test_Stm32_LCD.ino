#include <STM32RTC.h>
STM32RTC& rtc = STM32RTC::getInstance();

/*** Debug mode ***/
// #define SERIAL_MODE
#define LCD_MODE

#ifdef SERIAL_MODE
  HardwareSerial Serial2(PA10, PA9);
#endif

#ifdef LCD_MODE
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
  TwoWire Wire2(PB7, PB6); // SDA, SCL

  #define I2C_ADDRESS 0x27
  LiquidCrystal_I2C lcd(I2C_ADDRESS, 16, 2);
#endif

/*** Clock Setup ***/
#define CTRL_BUTTON_PIN PA2
#define SEL_BUTTON_PIN PA3

uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;
uint8_t pos = 0;

void changeHour() {
  hour += 1;
  if (hour > 23) hour = 0;
  rtc.setTime(hour, minute, second);
  String mess = String(hour) + ":" + String(minute) + ":"  +String (second);
  display(mess);
  delay(250);
}

void changeMinute() {
  minute += 1;
  if (minute > 59) minute = 0; 
  rtc.setTime(hour, minute, second);
  String mess = String(hour) + ":" + String(minute) + ":"  +String (second);
  display(mess);
  delay(250);
}

void changeSecond() {
  minute += 1;
  if (second > 59) second = 0; 
  rtc.setTime(hour, minute, second);
  String mess = String(hour) + ":" + String(minute) + ":"  +String (second);
  display(mess);
  delay(250);
}

// Pos:
// 0  -->  hour
// 1  -->  minute
// 2  -->  second
void changeNumber(uint8_t pos) {
  if (pos==1) {
    attachInterrupt(digitalPinToInterrupt(SEL_BUTTON_PIN), changeHour, FALLING); 
  }
  else if (pos==2) {
    attachInterrupt(digitalPinToInterrupt(SEL_BUTTON_PIN), changeMinute, FALLING); 
  }
  else if (pos==3) {
    attachInterrupt(digitalPinToInterrupt(SEL_BUTTON_PIN), changeSecond, FALLING); 
  }
}

void display(String mess) {
  #ifdef LCD_MODE
    lcd.setCursor(0, 0);
    lcd.print(mess);
  #endif

  #ifdef SERIAL_MODE
    Serial2.println(mess);
  #endif

}

void run() {
  hour = rtc.getHours();
  minute = rtc.getMinutes();
  second = rtc.getSeconds();
  String mess = String(rtc.getHours()) + ":" + String(rtc.getMinutes()) + ":" + String(rtc.getSeconds());
  display(mess);
  delay(950);
}

void control() {
  pos++;
  changeNumber(pos);
  delay(250);

  if (pos>3) {
    pos = 0;
    detachInterrupt(digitalPinToInterrupt(SEL_BUTTON_PIN));

    // Setup current date and time
    rtc.setTime(hour, minute, second);
    rtc.setDate(4, 9, 5, 23);

    // Run auto-update
    run();
  }
}

 void setup() {
  #ifdef SERIAL_MODE
    Serial2.begin(115200); 
  #endif

  #ifdef LCD_MODE
  // Initiate lcd
    Wire2.begin();
    lcd.begin();
    lcd.backlight();
  #endif

  // Initiate Rtc
  rtc.begin(); // initialize RTC 24H format
  rtc.setTime(hour, minute, second);

  // Enable interrupt
  pinMode(CTRL_BUTTON_PIN, INPUT_PULLUP); 
  pinMode(SEL_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CTRL_BUTTON_PIN), control, FALLING); // attach interrupt to the button pin, trigger on falling edge

}

void loop() {
  run();
}
