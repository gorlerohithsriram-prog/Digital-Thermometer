#include<DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define LED_GREEN 8
#define LED_YELLOW 9
#define LED_RED 10
#define BUZZER 11

#define TEMP_COOL 20
#define TEMP_WARM 28
#define TEMP_HOT 35

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_YELLOW,OUTPUT);
  pinMode(LED_RED,OUTPUT);
  pinMode(BUZZER,OUTPUT);

  dht.begin();
}

void updateAlerts(float tempC){
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_YELLOW,LOW);
  digitalWrite(LED_RED,LOW);
  digitalWrite(BUZZER,LOW);

  if (tempC < TEMP_WARM) {
    digitalWrite(LED_GREEN, HIGH);
  } else if (tempC < TEMP_HOT) {
    digitalWrite(LED_YELLOW, HIGH);
  } else {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  }
}

void loop(){
  float tempC = dht.readTemperature();

  if (isnan(tempC)) {
    return;
  }

  updateAlerts(tempC);

  delay(500);
}
