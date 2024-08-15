#include <microDS3231.h>
MicroDS3231 rtc;

#define CLOCK_SCL 
#define CLOCK_SDA 

#define RELAY_OPEN 3
#define RELAY_CLOSE 4

#define RAIN_SENSOR_INPUT 12

#define CLOSE_TIME_HOUR 19
#define CLOSE_TIME_MINUTE 0

#define OPEN_TIME_HOUR 8
#define OPEN_TIME_MINUTE 0

unsigned long startTime = 0;
const unsigned long waitTime = 90000; 
const unsigned long freeTime = 300000;

bool rain_flag = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_CLOSE, INPUT);  // Устанавливаем RELAY_CLOSE как выход
  pinMode(RELAY_CLOSE, HIGH);  // Устанавливаем RELAY_CLOSE как выход
  pinMode(RAIN_SENSOR_INPUT, INPUT_PULLUP); // Устанавливаем RAIN_SENSOR_INPUT как вход

  digitalWrite(RELAY_CLOSE, 1);

  if (!rtc.begin()) {
    Serial.println("DS3231 not found");
    for(;;);
  }

  if (rtc.lostPower()) {            // выполнится при сбросе батарейки
    Serial.println("lost power!");
    // тут можно однократно установить время == времени компиляции
  }

  // rtc.setTime(0, 0, 19, 14, 8, 2024);
}
  

void loop() {
  DateTime now = rtc.getTime();

  if (digitalRead(RAIN_SENSOR_INPUT) == LOW) {
    Serial.println("Work");
    digitalWrite(RELAY_CLOSE, 0);
    delay(waitTime);
    digitalWrite(RELAY_CLOSE, 1);
    // delay(freeTime);
  } else {
    digitalWrite(RELAY_CLOSE, 1);
  }
  delay(100);
}
