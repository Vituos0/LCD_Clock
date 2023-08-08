
#define us_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP 5

RTC_DATA_ATTR int bootCount = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * us_TO_S_FACTOR);
  bootCount++;
  Serial.println("Boot count" + String(bootCount));
  delay(1000);
  esp_deep_sleep_start();
  Serial.println("Is this okay?");


}

void loop() {
  // put your main code here, to run repeatedly:

}
