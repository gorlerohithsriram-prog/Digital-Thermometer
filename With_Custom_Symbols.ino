#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

  byte thermoChar[8]{
    0b00100,
    0b01010,
    0b01010,
    0b01110,
    0b01110,
    0b11111,
    0b11111,
    0b01110
  };

  byte dropChar[8]{
    0b00100,
    0b00100,
    0b01010,
    0b01010,
    0b10001,
    0b10001,
    0b10001,
    0b01110
  };
   
  void setup(){
    lcd.init();
    lcd.backlight();
    dht.begin();

    lcd.createChar(0,thermoChar);
    lcd.createChar(1,dropChar);

    }

  void loop(){
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();

  if (isnan(tempC) || isnan(humidity)) {
    lcd.clear();
    lcd.print("Sensor Error");
    delay(1000);
    return;
  }

  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  lcd.print(" ");
  lcd.print(tempC,1);
  lcd.print(char(223));
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.write(byte(1));
  lcd.print(" ");
  lcd.print(humidity,0);
  lcd.print("% ");

  delay(2000);
  }

