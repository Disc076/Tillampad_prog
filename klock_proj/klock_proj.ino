#include <RTClib.h>
#include <Wire.h>
#include <U8glib.h>

const int ledPin = 13;

RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();

  //init hardware
  pinMode(ledPin, OUTPUT);

  //setting
  u8g.setFont(u8g_font_unifont);
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
void loop() {
  Serial.println(getTime());
  oledWrite(0, 20, getTime(), String(getTemp()));
  ledControl();

  delay(100);
}

String getTime() {
  DateTime now = rtc.now();
  return "Time: " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}

float getTemp() {
  return rtc.getTemperature();
}


void oledWrite(int x, int y, String text1, String text2) {
  u8g.firstPage();
  do {
    u8g.drawStr(x, y, text1.c_str());
    u8g.drawStr(x, y + 20, text2.c_str());
  } while (u8g.nextPage());
}

void ledControl() {
  if (getTemp() > 22.75) {
    digitalWrite(ledPin, HIGH);
   
  }else {
    digitalWrite(ledPin, LOW);
  }
}
