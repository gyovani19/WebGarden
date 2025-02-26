#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7      // Pino de dados do DS18B20
#define MOTION_PIN 2        // Pino de entrada do sensor de movimento
#define BUZZER_PIN 8        // Pino do buzzer

// Inicializa o barramento OneWire e o sensor de temperatura
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

DeviceAddress thermometerAddress; // Armazena o endereço do DS18B20

int ledTemp = 3; // Pino para controle do LED associado à temperatura (opcional)

unsigned long previousMillis = 0;
const unsigned long interval = 1000; // Intervalo de 1 segundo

void setup() {
  Serial.begin(9600);
  
  // Configura os pinos
  pinMode(ledTemp, OUTPUT);
  pinMode(MOTION_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);  // LED para indicar detecção de movimento
  pinMode(BUZZER_PIN, OUTPUT);   // Configura o buzzer como saída
  
  Serial.println("Teste dos sensores: Temperatura, Umidade, Movimento e Buzzer");
  
  // Inicializa o sensor DS18B20
  tempSensor.begin();
  if (!tempSensor.getAddress(thermometerAddress, 0)) {
    Serial.println("DS18B20 não encontrado.");
  } else {
    Serial.print("Endereço do DS18B20: ");
    printAddress(thermometerAddress);
    Serial.println();
  }
  
  tempSensor.setResolution(thermometerAddress, 9); // Define a resolução para 9 bits
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Solicita a medição de temperatura
    tempSensor.requestTemperatures();
    float temperature = tempSensor.getTempC(thermometerAddress);
    
    // Leitura do sensor de umidade (pino A0)
    int moisture = analogRead(A0);
    
    // Leitura do sensor de movimento (pino MOTION_PIN)
    int motionState = digitalRead(MOTION_PIN);
    
    // Exibe os dados em uma única linha no Serial Monitor
    Serial.print("Umidade: ");
    Serial.print(moisture);
    if (moisture < 300) {
      Serial.print(" (ALTA)");
    } else if (moisture >= 300 && moisture <= 950) {
      Serial.print(" (MÉDIA)");
    } else {
      Serial.print(" (BAIXA)");
    }
    
    Serial.print(" | Temp: ");
    Serial.print(temperature);
    Serial.print("°C ");
    Serial.print(DallasTemperature::toFahrenheit(temperature));
    Serial.print("°F");
    
    Serial.print(" | Movimento: ");
    if (motionState == HIGH) {
      Serial.print("Detectado");
      digitalWrite(LED_BUILTIN, HIGH);  // Liga o LED do detector de movimento
      tone(BUZZER_PIN, 220, 100);        // Emite um tom de 220 Hz por 100 ms
    } else {
      Serial.print("Não Detectado");
      digitalWrite(LED_BUILTIN, LOW);   // Desliga o LED do detector de movimento
      noTone(BUZZER_PIN);               // Garante que o buzzer esteja desligado
    }
    
    Serial.println();
    
    // Controle opcional do LED associado à temperatura:
    // Acende se a temperatura for superior a 18°C
    if (temperature > 18) {
      digitalWrite(ledTemp, HIGH);
    } else {
      digitalWrite(ledTemp, LOW);
    }
  }
}

// Função para imprimir o endereço do DS18B20
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
