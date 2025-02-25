/*********************************************************************
  Este é um exemplo para ler a temperatura do sensor DS18B20 e
  exibir o resultado no Serial Monitor do Arduino IDE.

  A temperatura é exibida em °C e °F.

  Gadget Reboot

*********************************************************************/

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7               // O fio de dados do DS18B20 está conectado ao pino 7

DeviceAddress thermometerAddress;     // array customizado para armazenar o endereço de 64 bits do dispositivo

OneWire oneWire(ONE_WIRE_BUS);          // cria uma instância oneWire para comunicação com o sensor de temperatura
DallasTemperature tempSensor(&oneWire); // passa a referência oneWire para o DallasTemperature

int ledPin = 3;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
  Serial.println("Teste do IC de Temperatura DS18B20");
  Serial.println("Localizando dispositivos...");
  tempSensor.begin(); // inicializa o sensor de temperatura

  if (!tempSensor.getAddress(thermometerAddress, 0))
    Serial.println("Dispositivo não encontrado.");
  else {
    Serial.print("Endereço do dispositivo 0: ");
    printAddress(thermometerAddress);
    Serial.println();
  }

  tempSensor.setResolution(thermometerAddress, 9); // define a resolução da medição (9-12 bits)
}

void loop() {
  // Solicita a medição de temperatura
  tempSensor.requestTemperatures();                      
  float temperature = tempSensor.getTempC(thermometerAddress);
  
  // Exibe a temperatura no Serial Monitor
  displayTemp(temperature);

  // Acende o LED se a temperatura for maior que 20°C, caso contrário, apaga o LED
  if (temperature > 21) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(500); // atualiza a cada meio segundo
}

void displayTemp(float temperatureReading) {
  // Exibe a temperatura em °C
  Serial.print(temperatureReading);
  Serial.print("°C  ");
  
  // Exibe a temperatura em °F
  Serial.print(DallasTemperature::toFahrenheit(temperatureReading));
  Serial.print("°F");
  Serial.println();
}

// Função para imprimir o endereço do dispositivo
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
