# Smart Water Tank Level Monitoring and Pump Control System

An Arduino-based embedded system that monitors water tank levels using an ultrasonic sensor and automatically controls a pump indicator with visual and audio alerts.

---

## Problem Statement

Water wastage and shortages are common due to lack of automated water level monitoring. Manual checking is unreliable and inefficient. This system solves that by continuously monitoring water levels and activating a pump indicator automatically — no human intervention required.

---

## System Description

The system:
- Detects water level using an HC-SR04 ultrasonic sensor mounted at the top of the tank
- Displays level status via colour-coded LEDs (Red, Yellow, Green)
- Controls a pump indicator (Blue LED) automatically
- Activates a buzzer alert when water level is critically low
- Outputs real-time status messages via Serial Monitor

---

## Components

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno | 1 | Microcontroller — system brain |
| HC-SR04 Ultrasonic Sensor | 1 | Measures water level (distance) |
| Red LED | 1 | Critical / Low level indicator |
| Yellow LED | 1 | Medium level indicator |
| Green LED | 1 | Full tank indicator |
| Blue LED | 1 | Pump indicator |
| Piezo Buzzer | 1 | Critical level audio alert |
| 220Ω Resistor | 5 | Current limiting for LEDs and buzzer |
| Breadboard | 1 | Component connections |
| Jumper Wires | — | Circuit connections |

---

## Circuit Wiring

### HC-SR04 Ultrasonic Sensor
| Sensor Pin | Arduino Pin |
|------------|-------------|
| VCC | 5V |
| GND | GND |
| TRIG | Pin 9 |
| ECHO | Pin 10 |

### LEDs (each with 220Ω resistor in series)
| LED | Arduino Pin |
|-----|-------------|
| Red (Critical/Low) | Pin 2 |
| Yellow (Medium) | Pin 3 |
| Green (Full) | Pin 4 |
| Blue (Pump) | Pin 5 |

### Buzzer
| Buzzer Pin | Arduino Pin |
|------------|-------------|
| + (through 220Ω) | Pin 6 |
| − | GND |

**Wiring rule:** Arduino pin → 220Ω resistor → LED anode (long leg) → LED cathode (short leg) → GND

---

## System Logic

| Distance (cm) | Water Level | Red LED | Yellow LED | Green LED | Pump LED | Buzzer |
|---------------|-------------|---------|------------|-----------|----------|--------|
| > 250 | Critical | ON | OFF | OFF | ON | ON |
| 150 – 250 | Low | ON | OFF | OFF | ON | OFF |
| 80 – 150 | Medium | OFF | ON | OFF | ON | OFF |
| < 80 | Full | OFF | OFF | ON | OFF | OFF |

> The pump activates at **medium level** — early enough to prevent the tank from ever reaching critical under normal conditions. This is preventive control, not reactive.

---

## Arduino Source Code

```cpp
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
```

---

## How Distance Maps to Water Level

The HC-SR04 is mounted at the **top** of the tank facing downward. Distance and water level are inversely related:

```
Large distance  =  Low water  (sensor far from water surface)
Small distance  =  High water (sensor close to water surface)
```

---

## Simulation

Built and tested in [Tinkercad Circuits](https://www.tinkercad.com/things/75XCtipFoz3-smart-water-tank-level-monitoring?sharecode=VsUiFhV2e1XgXPiefALdM7UmUVJG2-VdTOeFIn80ats).

To simulate:
1. Open the Tinkercad project link
2. Click **Start Simulation**
3. Click the HC-SR04 sensor — a distance slider appears
4. Drag the slider to different distances and observe LED and buzzer responses
5. Open the **Serial Monitor** to see real-time status output

---

## Repository Structure

```
smart-water-tank-level-monitoring/
│
├── README.md               — Project documentation
├── water_tank_monitor.ino  — Arduino source code
└── screenshots/
    ├── circuit_overview.jpeg
    ├── simulation_critical.jpeg
    ├── simulation_low.jpeg
    ├── simulation_medium.jpeg
    └── simulation_full.jpeg
```

---

## Demo Video

[YouTube — Smart Water Tank Level Monitoring System](#)  
*(Link to be added after upload)*

---

## Author

**Sserunjoji Marvin** 
Registration: 23/2/370/W/203

**Mukiibi Jumah** 
Registration: 23/2/370/W/537

Faculty of Science and Computing — Bachelor of Software Engineering  
Ndejje University  

