#define SENSOR_UMIDADE 34  // Pino analógico do sensor de umidade
#define RELE_BOMBA 26      // Pino digital do relé


#define LIMIAR_UMIDADE 1000  

void setup() {
    Serial.begin(115200);
    pinMode(RELE_BOMBA, OUTPUT);
    digitalWrite(RELE_BOMBA, HIGH);  // Desliga a bomba no início
}

void loop() {
    int umidade = analogRead(SENSOR_UMIDADE);
    Serial.print("Umidade do solo: ");
    Serial.println(umidade);

    if (umidade > LIMIAR_UMIDADE) {  // Se o solo estiver seco
        Serial.println("Solo seco! Ligando bomba...");
        digitalWrite(RELE_BOMBA, LOW);  // Ativa o relé (liga a bomba)
    } else {
        Serial.println("Solo úmido! Desligando bomba...");
        digitalWrite(RELE_BOMBA, HIGH); // Desativa o relé (desliga a bomba)
    }

    delay(5000);  
}
