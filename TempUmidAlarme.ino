#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7      // Pino de dados do DS18B20
#define MOTION_PIN 2        // Pino do sensor de movimento
#define BUZZER_PIN 8        // Pino do buzzer

// Inicializa o barramento OneWire e o sensor de temperatura
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

DeviceAddress thermometerAddress; // Armazena o endereço do DS18B20

int ledTemp = 3; // Pino para controle do LED associado à temperatura (opcional)

unsigned long previousMillis = 0;
const unsigned long interval = 1000; // Intervalo de 1 segundo

bool showJiboia = true; // Flag para alternar entre exibir JIBÓIA e CACTO

void setup() {
  Serial.begin(9600);
  
  // Configura os pinos
  pinMode(ledTemp, OUTPUT);
  pinMode(MOTION_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);  // LED para indicar detecção de movimento
  pinMode(BUZZER_PIN, OUTPUT);   // Configura o buzzer como saída
  
  Serial.println("Teste dos sensores:");
  Serial.println("JIBÓIA (Umidade, Temp, Movimento) e CACTO (Umidade)");
  
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
    
    // Leitura dos sensores de umidade
    int moistureJib = analogRead(A0); // JIBÓIA
    int moistureCact = analogRead(A1); // CACTO
    
    // Leitura do sensor de movimento
    int motionState = digitalRead(MOTION_PIN);
    
    // Detecção de presença é feita sempre:
    if (motionState == HIGH) {
      digitalWrite(LED_BUILTIN, HIGH);      // Acende o LED se houver movimento
      tone(BUZZER_PIN, 220, 100);            // Apita 220 Hz por 100 ms
    } else {
      digitalWrite(LED_BUILTIN, LOW);         // Apaga o LED se não houver movimento
      noTone(BUZZER_PIN);                    // Garante que o buzzer esteja desligado
    }
    
    if (showJiboia) {
      // Linha para JIBÓIA: exibe umidade (A0), temperatura e movimento
      Serial.print("JIBÓIA: Umidade: ");
      Serial.print(moistureJib);
      if (moistureJib < 300) {
        Serial.print(" (ALTA)");
      } else if (moistureJib >= 300 && moistureJib <= 900) {
        Serial.print(" (MÉDIA)");
      } else {
        Serial.print(" (BAIXA)");
      }
      
      Serial.print(" | Temp: ");
      Serial.print(temperature, 2);
      Serial.print("°C ");
      Serial.print(DallasTemperature::toFahrenheit(temperature), 2);
      Serial.print("°F");
      
      Serial.print(" | Movimento: ");
      if (motionState == HIGH) {
        Serial.print("Detectado");
      } else {
        Serial.print("Não Detectado");
      }
      Serial.println();
    } else {
      // Linha para CACTO: exibe umidade (A1) com classificação
      Serial.print("CACTO: Umidade: ");
      Serial.print(moistureCact);
      if (moistureCact < 300) {
        Serial.print(" (ALTA)");
      } else if (moistureCact >= 300 && moistureCact <= 900) {
        Serial.print(" (MÉDIA)");
      } else {
        Serial.print(" (BAIXA)");
      }
      Serial.print(" | Movimento: ");
      if (motionState == HIGH) {
        Serial.print("Detectado");
      } else {
        Serial.print("Não Detectado");
      }
      Serial.println();
    }
    
    // Controle opcional do LED associado à temperatura:
    // Acende se a temperatura for superior a 18°C
    if (temperature > 18) {
      digitalWrite(ledTemp, HIGH);
    } else {
      digitalWrite(ledTemp, LOW);
    }
    
    // Alterna entre exibir dados da JIBÓIA e do CACTO na próxima iteração
    showJiboia = !showJiboia;
  }
}

// Função para imprimir o endereço do DS18B20
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
