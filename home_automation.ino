//LIBRARY INCLUDED
#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

//Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = "UtOLhoshQ2GSAlI9rhUl52I6R4pCOTPp";//Enter your Auth token
char ssid[] = "Goblin clash";//Enter your WIFI name
char pass[] = "llama999";//Enter your WIFI password

DHT dht(D3, DHT11); //(sensor pin,sensor type)
BlynkTimer timer;

// Define component pins
#define relay1 D5
#define relay2 D6
#define relay3 D7
#define relay4 D8


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Home Automation");
  lcd.setCursor(4, 1);
  lcd.print("System");
  delay(4000);
  lcd.clear();

 //Call the functions
 
  timer.setInterval(100L, DHT11sensor);
  
}

//Get the DHT11 sensor values
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V5, h);

  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("Humi : ");
  lcd.print(h);

}

//Get buttons values
BLYNK_WRITE(V1) {
 bool RelayOne = param.asInt();
  if (RelayOne == 1) {
    digitalWrite(relay1, LOW);
  } else {
    digitalWrite(relay1, HIGH);
  }
}

//Get buttons values
BLYNK_WRITE(V2) {
 bool RelayTwo = param.asInt();
  if (RelayTwo == 1) {
    digitalWrite(relay2, LOW);
  } else {
    digitalWrite(relay2, HIGH);
  }
}

//Get buttons values
BLYNK_WRITE(V3) {
 bool RelayOne = param.asInt();
  if (RelayOne == 1) {
    digitalWrite(relay3, LOW);
  } else {
    digitalWrite(relay3, HIGH);
  }
}

//Get buttons values
BLYNK_WRITE(V4) {
 bool RelayTwo = param.asInt();
  if (RelayTwo == 1) {
    digitalWrite(relay4, LOW);
  } else {
    digitalWrite(relay4, HIGH);
  }
}

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}