#define TRIG_PIN 9
#define ECHO_PIN 10
#define LED_RED 2
#define LED_YELLOW 3
#define LED_GREEN 4
#define LED_PUMP 5
#define BUZZER 6

long duration;
int distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_PUMP, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void loop() {
  distance = getDistance();

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);

  if (distance > 250) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_PUMP, HIGH);
    tone(BUZZER, 1000);
    Serial.println("CRITICAL: Water very low! Pump ON, Alert ON");
  } else if (distance > 150) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_PUMP, HIGH);
    noTone(BUZZER);
    Serial.println("LOW: Water low. Pump ON");
  } else if (distance > 80) {
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_PUMP, HIGH);
    noTone(BUZZER);
    Serial.println("MEDIUM: Filling... Pump ON");
  } else {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_PUMP, LOW);
    noTone(BUZZER);
    Serial.println("FULL: Tank full. Pump OFF");
  }

  delay(500);
}