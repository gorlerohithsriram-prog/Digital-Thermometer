#include<Wire.h>
#include<DHT.h>
#include<LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup(){
  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(0,0);
  lcd.print("Dig Therm");
  lcd.setCursor(0,1);
  lcd.print("Starting...");
  delay(2000);
  lcd.clear();
}

void loop(){
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();

  if(isnan(humidity) || isnan(tempC)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sensor Error!");
    delay(1000);
    return;
  }

  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(tempC,1);
  lcd.print((char)223);
  lcd.print("C ");

  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.print(humidity,0);
  lcd.print("%   ");

  delay(2000);
}
