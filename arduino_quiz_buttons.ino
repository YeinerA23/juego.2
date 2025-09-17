
// Arduino Quiz + Luces
// Botones en pines 2-5 (INPUT_PULLUP, conectados a GND)
// Luces verdes en 6-10, rojas en 11-15

const int BTN_A = 2;
const int BTN_B = 3;
const int BTN_C = 4;
const int BTN_D = 5;

const int verdes[5] = {6,7,8,9,10};
const int rojas[5]  = {11,12,13,A0,A1}; // puedes usar A0 y A1 como digitales

const unsigned long DEBOUNCE = 80;
unsigned long lastPress = 0;

void setup() {
  Serial.begin(9600);

  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);
  pinMode(BTN_C, INPUT_PULLUP);
  pinMode(BTN_D, INPUT_PULLUP);

  for (int i=0; i<5; i++) {
    pinMode(verdes[i], OUTPUT);
    pinMode(rojas[i], OUTPUT);
    digitalWrite(verdes[i], LOW);
    digitalWrite(rojas[i], LOW);
  }
}

void loop() {
  // --- Enviar pulsaciones ---
  if (millis() - lastPress > DEBOUNCE) {
    if (digitalRead(BTN_A) == LOW) { Serial.println("A"); lastPress = millis(); }
    if (digitalRead(BTN_B) == LOW) { Serial.println("B"); lastPress = millis(); }
    if (digitalRead(BTN_C) == LOW) { Serial.println("C"); lastPress = millis(); }
    if (digitalRead(BTN_D) == LOW) { Serial.println("D"); lastPress = millis(); }
  }

  // --- Recibir comandos ---
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "CORRECTO") {
      encenderLuces(verdes);
    }
    else if (cmd == "INCORRECTO") {
      encenderLuces(rojas);
    }
  }
}

void encenderLuces(const int pines[5]) {
  // Enciende las 5 luces 1 segundo
  for (int i=0; i<5; i++) digitalWrite(pines[i], HIGH);
  delay(1000);
  for (int i=0; i<5; i++) digitalWrite(pines[i], LOW);
}
