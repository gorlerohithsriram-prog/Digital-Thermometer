#include<Wire.h>
#include<DHT.h>
#include<LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

float minTemp = 1000;
float maxTemp = -1000;

unsigned long lastSwitch = 0;
int displayMode = 0;

void setup(){
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop(){
  float tempC = dht.readTemperature();

  if(!isnan(tempC)){
    if(tempC<minTemp) minTemp = tempC;
    if(tempC>maxTemp) maxTemp = tempC;
  }

  if (millis() - lastSwitch > 3000) {
    displayMode = (displayMode + 1) % 2;
    lastSwitch = millis();
    lcd.clear();
  }

  if(displayMode==0){
    // Print Current Temp
    lcd.setCursor(0,0);
    lcd.print("Curr Temp:");
    lcd.setCursor(0,1);
    lcd.print(tempC,1);
    lcd.print((char)223);
    lcd.print("C  ");
  }
  else
  {
    // Print max/min temp
    lcd.setCursor(0,0);
    lcd.print("Min:");
    lcd.print(minTemp,1);
    lcd.print((char)223);
    lcd.print("C ");
    
    lcd.setCursor(0,1);
    lcd.print("Max:");
    lcd.print(maxTemp,1);
    lcd.print((char)223);
    lcd.print("C ");
  }

  delay(1000);
}
