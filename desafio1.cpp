#include <LiquidCrystal.h>

// === Definições dos Pinos ===
const int pinBuzzer = 6;
const int pinTempSensor = A0;
const int pinHumiditySensor = A1;
const int pinLightSensor = A2;
const int pinLedRed = 9;
const int pinLedYellow = 8;
const int pinLedGreen = 7;
const int pinBacklight = 13;

// LCD
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

// Controle de tempo de exibição
unsigned long previousMillis = 0;
const long interval = 3000;  // 3 segundos
int etapa = 0;

// Variáveis globais dos sensores
float temperatura = 0;
float umidade = 0;
float luz = 0;

// Variáveis para leitura assíncrona dos sensores
unsigned long leituraMillis = 0;
int leituraEtapa = 0;
const int totalLeituras = 5;

float somaTemp = 0;
float somaHum = 0;
float somaLuz = 0;

// === Classes ===

class Sensor {
  public:
    virtual float rawRead() = 0;
};

class TemperatureSensor : public Sensor {
  int pin;
public:
  TemperatureSensor(int p) : pin(p) {}
  float rawRead() {
    int raw = analogRead(pin);
    float voltage = (raw / 1023.0) * 5000;
    return (voltage - 500) * 0.1;
  }
};

class HumiditySensor : public Sensor {
  int pin;
public:
  HumiditySensor(int p) : pin(p) {}
  float rawRead() {
    int raw = analogRead(pin);
    return map(raw, 0, 1023, 0, 100);
  }
};

class LightSensor : public Sensor {
  int pin;
public:
  LightSensor(int p) : pin(p) {}
  float rawRead() {
    int raw = analogRead(pin);
    return map(raw, 54, 974, 0, 100);
  }
};

class Actuators {
public:
  void leds(bool red, bool yellow, bool green) {
    digitalWrite(pinLedRed, red);
    digitalWrite(pinLedYellow, yellow);
    digitalWrite(pinLedGreen, green);
  }

  void buzzer(bool state) {
    if (state) tone(pinBuzzer, 1000);
    else noTone(pinBuzzer);
  }
};

// === Objetos ===
TemperatureSensor tempSensor(pinTempSensor);
HumiditySensor humSensor(pinHumiditySensor);
LightSensor lightSensor(pinLightSensor);
Actuators actuators;

// === Setup ===
void setup() {
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinHumiditySensor, INPUT);
  pinMode(pinLightSensor, INPUT);
  pinMode(pinBacklight, OUTPUT);
  digitalWrite(pinBacklight, HIGH);

  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedYellow, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();

  Serial.begin(9600);

  leituraMillis = millis();
}

// Função de leitura assíncrona
void realizarLeitura() {
  if (millis() - leituraMillis >= 100) {
    leituraMillis = millis();

    somaTemp += tempSensor.rawRead();
    somaHum += humSensor.rawRead();
    somaLuz += lightSensor.rawRead();
    leituraEtapa++;

    if (leituraEtapa >= totalLeituras) {
      temperatura = somaTemp / totalLeituras;
      umidade = somaHum / totalLeituras;
      luz = somaLuz / totalLeituras;

      // Zera acumuladores para próxima leitura
      somaTemp = 0;
      somaHum = 0;
      somaLuz = 0;
      leituraEtapa = 0;

      Serial.println("=================");
      Serial.print("Temp: ");
      Serial.println(temperatura);
      Serial.print("Umidade: ");
      Serial.println(umidade);
      Serial.print("Luz: ");
      Serial.println(luz);
    }
  }
}

// === Loop ===
void loop() {
  realizarLeitura();

  // Só atualiza a exibição se já concluiu as 5 leituras
  if (leituraEtapa == 0 && millis() - previousMillis >= interval) {
    previousMillis = millis();

    lcd.clear();

    switch (etapa) {
      case 0: // Temperatura
        if (temperatura < 10) {
          lcd.print("Temp. Baixa:");
          lcd.setCursor(0, 1);
          lcd.print(temperatura, 1);
          lcd.print("C");
          actuators.buzzer(true);
          actuators.leds(LOW, HIGH, LOW);
        } else if (temperatura > 15) {
          lcd.print("Temp. Alta:");
          lcd.setCursor(0, 1);
          lcd.print(temperatura, 1);
          lcd.print("C");
          actuators.buzzer(true);
          actuators.leds(LOW, HIGH, LOW);
        } else {
          lcd.print("Temp. OK:");
          lcd.setCursor(0, 1);
          lcd.print(temperatura, 1);
          lcd.print("C");
          actuators.buzzer(false);
          actuators.leds(LOW, LOW, HIGH);
        }
        break;

      case 1: // Umidade
        if (umidade < 50) {
          lcd.print("Umidade Baixa:");
          lcd.setCursor(0, 1);
          lcd.print(umidade, 0);
          lcd.print("%");
          actuators.buzzer(true);
          actuators.leds(HIGH, LOW, LOW);
        } else if (umidade > 70) {
          lcd.print("Umidade Alta:");
          lcd.setCursor(0, 1);
          lcd.print(umidade, 0);
          lcd.print("%");
          actuators.buzzer(true);
          actuators.leds(HIGH, LOW, LOW);
        } else {
          lcd.print("Umidade OK:");
          lcd.setCursor(0, 1);
          lcd.print(umidade, 0);
          lcd.print("%");
          actuators.buzzer(false);
          actuators.leds(LOW, LOW, HIGH);
        }
        break;

      case 2: // Luminosidade
        if (luz <= 30) {
          lcd.print("Ambiente Escuro");
          actuators.leds(LOW, LOW, HIGH);
          actuators.buzzer(false);
        } else if (luz <= 70) {
          lcd.print("Meia Luz");
          actuators.leds(LOW, HIGH, LOW);
          actuators.buzzer(false);
        } else {
          lcd.print("Muito Claro");
          actuators.leds(HIGH, LOW, LOW);
          actuators.buzzer(true);
        }
        break;
    }

    etapa = (etapa + 1) % 3;
  }
}
