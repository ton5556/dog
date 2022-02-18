#include <TridentTD_LineNotify.h>
#include <ESP8266WiFi.h>
#define SSID        "Galaxy A02s4139"
#define PASSWORD    "nxnt6567"
#define LINE_TOKEN  "PBQSJxnyjQ2fiPUL4dW1pznJj11LExSuOMqN12yVfYi"

#define Green_LED D2
#define Red_LED D3
#define Relay D4

bool detect = true;
bool buzz = false;
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 180000;
const int sensetive=500;
void setup() {
  Serial.begin(115200); Serial.println();
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

  LINE.notify("โปรเจคตรวจจับควันพร้อมทำงาน");

  pinMode(Green_LED, OUTPUT);
  digitalWrite(Green_LED, LOW);

  pinMode(Red_LED, OUTPUT);
  digitalWrite(Red_LED, LOW);

  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
}

void loop() {
  int GAS = analogRead(A0);
  unsigned long currentMillis = millis();
  Serial.println(GAS);
  if (GAS > sensetive && detect == false) {
    Serial.println("GAS>200");
    LINE.notify("! ! ! ตรวจพบแก็ส ! ! !");
    digitalWrite(Green_LED, LOW);
    digitalWrite(Red_LED, HIGH);
    digitalWrite(Relay, HIGH);
    detect = true;
    buzz = true;
    previousMillis = currentMillis;
  }
  if (GAS <= sensetive && detect == true) {
    Serial.println("GAS OK");
    LINE.notify("แก็สปกติ");
    digitalWrite(Green_LED, HIGH);
    digitalWrite(Red_LED, LOW);
    //digitalWrite(Relay, LOW);
    detect = false;
  }
  
  if (buzz == true) {
    if (currentMillis - previousMillis <= interval) {
      digitalWrite(Relay, HIGH);
      Serial.println("Buzz On");
    }
    else {
      digitalWrite(Relay, LOW);
      buzz = false;
      Serial.println("Buzz Off");
    }
  }
  delay(500);
}
