// =======================================================
// ESP32 + Sensor de Chuva/Água + 3 LEDs
// Sistema de detecção de possíveis vazamentos
// =======================================================

// -------------------------
// Pinos
// -------------------------
const int PINO_SENSOR_AO = 34;

const int LED_VERDE      = 25;
const int LED_AMARELO    = 26;
const int LED_VERMELHO   = 27;

// -------------------------
// Limiares calibrados
// -------------------------
// Sensor seco = aproximadamente 4095
// Sensor completamente molhado = aproximadamente 1500

const int LIMIAR_SECO = 3500;
const int LIMIAR_ALERTA = 2000;


// =======================================================
// SETUP
// =======================================================
void setup() {

  Serial.begin(115200);

  // Configura o ADC da ESP32
  analogSetPinAttenuation(PINO_SENSOR_AO, ADC_11db);

  // LEDs como saída
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  // Todos começam desligados
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  Serial.println("=================================");
  Serial.println(" SISTEMA DE DETECCAO DE VAZAMENTO");
  Serial.println(" ESP32 + SENSOR DE AGUA");
  Serial.println("=================================");
}


// =======================================================
// LOOP
// =======================================================
void loop() {

  // Faz a leitura do sensor
  int valorSensor = analogRead(PINO_SENSOR_AO);

  // Mostra o valor no Monitor Serial
  Serial.print("Valor do sensor: ");
  Serial.println(valorSensor);

  // Desliga todos os LEDs antes de determinar o estado
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);


  // =====================================================
  // SENSOR SECO
  // =====================================================
  if (valorSensor >= LIMIAR_SECO) {

    digitalWrite(LED_VERDE, HIGH);

    Serial.println("Estado: SEM AGUA");
    Serial.println("Status: NORMAL");

  }


  // =====================================================
  // PRESENCA DE POUCA AGUA
  // =====================================================
  else if (valorSensor >= LIMIAR_ALERTA) {

    digitalWrite(LED_AMARELO, HIGH);

    Serial.println("Estado: ATENCAO");
    Serial.println("Status: PRESENCA DE AGUA");

  }


  // =====================================================
  // POSSIVEL VAZAMENTO
  // =====================================================
  else {

    digitalWrite(LED_VERMELHO, HIGH);

    Serial.println("Estado: ALERTA");
    Serial.println("Status: POSSIVEL VAZAMENTO DETECTADO");

  }


  Serial.println("---------------------------------");

  // Aguarda meio segundo
  delay(500);
}
