#include "DHT.h"

#define lightSensKitchen 2
#define releLightKitchen 3
#define lightSensBar 4
#define releLightBar 5
#define DHTPIN 6
#define releAirKitch 7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHT22);

int MoveKitchenCount = 0;
int MoveBarCount = 0;
int kitchenAirPin = A0;
int kitchenAirValue = 0;
float kitchenHumidity = 0;
float kitchenTemperature = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(lightSensKitchen, INPUT);
  pinMode(releLightKitchen, OUTPUT);
  pinMode(lightSensBar, INPUT);
  pinMode(releLightBar, OUTPUT);
  pinMode(kitchenAirPin, INPUT);
  pinMode(releAirKitch, OUTPUT);
  dht.begin();
}

void loop()
{
  delay(1000);
  kitchenHumidity = dht.readHumidity();
  kitchenTemperature = dht.readTemperature();
  kitchenAirValue = analogRead(kitchenAirPin);
  Serial.print("air_");
  Serial.print(kitchenAirValue);
  Serial.print("  ");
  Serial.print("humidity_");
  Serial.print(kitchenHumidity);
  Serial.print("  ");
  Serial.print("temperature_");
  Serial.println(kitchenTemperature);
  motionKitchen(30);
  motionBar(30);
  cleanAir(kitchenAirValue);
}

void cleanAir(int kitchenAirValue) {
  if (kitchenAirValue > 45) {
    digitalWrite(releAirKitch, HIGH);
  }
  if (kitchenAirValue <= 45) {
    digitalWrite(releAirKitch, LOW);
  }
};

void motionKitchen(int seconds) {
  if (digitalRead(lightSensKitchen) == HIGH) {
    digitalWrite(releLightKitchen, HIGH);
    MoveKitchenCount = 0;
  }
  if (digitalRead(lightSensKitchen) == LOW) {
    MoveKitchenCount++;
    if (MoveKitchenCount == seconds) {
      digitalWrite(releLightKitchen, LOW);
      MoveKitchenCount = 0;
    }
  }
}

void motionBar(int seconds) {
  if (digitalRead(lightSensBar) == HIGH) {
    digitalWrite(releLightBar, HIGH);
    MoveBarCount = 0;
  }
  if (digitalRead(lightSensBar) == LOW) {
    MoveBarCount++;
    if (MoveBarCount == seconds) {
      digitalWrite(releLightBar, LOW);
      MoveBarCount = 0;
    }
  }
}
