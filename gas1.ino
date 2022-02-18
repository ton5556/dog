#include <TridentTD_LineNotify.h>
#include <ESP8266WiFi.h>
#define SSID        "..............................."//ชื่อ WIFI ที่ต้องการใช้
#define PASSWORD    "......................."//ระหัส WIFI
#define LINE_TOKEN  ".............................."//Token ที่ได้จากการออก
int SensorPin = A0;
int SensorValue = 0;
void setup() {
  Serial.begin(9600); Serial.println();
  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
}
void loop() {
  int SensorValue = analogRead (SensorPin);
  Serial.print("ค่าตรวจจับแก๊ส:   ");
  Serial.println(SensorValue);
  delay(2000);
  if (SensorValue >= 300)
  {
    Serial.println("Line");
    LINE.notify("ระดับเกินแก๊สกำหนดแล้ว");
    while ( SensorValue = analogRead (SensorPin) >= 300) delay(1000);
  } else {}
}
