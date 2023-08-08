#include <esp_sleep.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define LED_PIN 14
#define BUTTON_PIN 34
//#define LCD_POWER_PIN 25

volatile bool Awake = false;
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.noBacklight();
  // pinMode(LCD_POWER_PIN, OUTPUT);
  // digitalWrite(LCD_POWER_PIN, HIGH);  // Bật nguồn cung cấp cho LCD

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  // Serial.begin(115200);
  // Serial.println("ESP is being awaken, just a moment!");
  // print message
  lcd.print("Waking...");
  // delay(5000);
  digitalWrite(LED_PIN, 1);
  //Serial.println("Welcome!");
  lcd.clear();
  lcd.print("Welcome!");
  // delay(2000);
  lcd.clear();
  lcd.print("Password");
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonClicked, FALLING);
  //esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, FALLING); //1 = High, 0 = Low
  //esp_deep_sleep_start();
  delay(30000);
  Sleeping();
}

void loop(){
  //Nothing to loop
}

void buttonClicked(){
  Sleeping();
  
  // digitalWrite(LED_PIN, 0);
  

}

void Sleeping() {
  
  //Serial.println("ESP going to sleep");
  //digitalWrite(LCD_POWER_PIN, LOW);
  //lcd.print("Sleep!");
  lcd.noBacklight();
  lcd.noDisplay();
  Awake = !Awake;
  lcd.print(" ");
  digitalWrite(LED_PIN, 0);
  if(!Awake)
  esp_deep_sleep_start();

}