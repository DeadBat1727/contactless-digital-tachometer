# contactless-digital-tachometer
Arduino-based contactless digital tachometer (RPM meter) using an IR sensor and I2C LCD.

# Contactless Digital Tachometer Using Microcontroller

> Course project (EE 3200 — Electrical & Electronic Project Design), B.Sc. in EEE, Khulna University of Engineering & Technology (KUET)

![Platform](https://img.shields.io/badge/platform-Arduino-00979D?logo=arduino&logoColor=white)
![Language](https://img.shields.io/badge/code-C%2FC%2B%2B-A8B9CC?logo=c&logoColor=black)
![Status](https://img.shields.io/badge/status-working%20prototype-success)
![Domain](https://img.shields.io/badge/domain-Embedded%20Systems-blue)

---

## 📖 Overview

A low-cost, **contactless digital tachometer (RPM meter)** that measures the rotational speed of a shaft or disk without any physical contact. An infrared (IR) sensor detects a reflective patch on the rotating object, an **Arduino Uno** calculates the RPM, and the result is shown on a **16×2 I2C LCD**. The whole system runs on a 9V battery, making it portable and self-contained.

The design deliberately uses pre-assembled modules — no breadboard, soldering, or external resistors required — making it simple, robust, and easy to reproduce.

---

## ⚙️ How It Works

The system is based on **infrared reflection and pulse counting**:

1. **Sensing** — The TCRT5000 module's IR LED emits infrared light; its phototransistor detects the reflection.
2. **Reflection** — A small piece of reflective tape is placed on the rotating object (motor shaft, fan blade, etc.).
3. **Pulse generation** — Each time the tape passes the sensor, the module's digital output toggles, producing one pulse per revolution.
4. **Processing** — The Arduino reads these pulses on an interrupt pin (D2) and measures the time between consecutive pulses.
5. **Calculation** — RPM is computed as:

   ```
   RPM = 60000 / (time between pulses in milliseconds)
   ```

6. **Display** — The RPM value is sent to the I2C LCD in real time.

---

## 🧩 Components

| Component | Qty | Specification / Notes |
|-----------|-----|-----------------------|
| Arduino Uno | 1 | ATmega328P microcontroller board |
| IR Sensor Module | 1 | TCRT5000 (built-in resistors + sensitivity potentiometer) |
| 16×2 LCD with I2C adapter | 1 | I2C interface — only 4 wires (VCC, GND, SDA, SCL) |
| 9V Battery + Clip | 1 | Portable power source |
| Jumper Wires | 4–5 | Male-to-female recommended |
| Reflective Tape | 1 | Marks the rotating object |

---

## 🔌 Circuit Connections

| From Component | Pin | To Arduino Uno |
|----------------|-----|----------------|
| TCRT5000 Module | VCC | 5V |
| | GND | GND |
| | OUT | Digital Pin 2 *(interrupt pin for accurate counting)* |
| I2C LCD Module | VCC | 5V |
| | GND | GND |
| | SDA | A4 |
| | SCL | A5 |
| 9V Battery | + / − | Barrel Jack |


---

## 💻 Code

The full Arduino sketch is in [`tachometer.ino`](tachometer.ino). It uses a hardware interrupt on pin D2 for accurate pulse timing, a simple debounce filter, and the `LiquidCrystal_I2C` library to drive the display.

**Libraries required:**
- `Wire.h` (built-in)
- `LiquidCrystal_I2C.h`

---

## 🛠️ Build & Test

1. **Assembly** — Connect all modules per the circuit table using jumper wires (no soldering needed for a prototype).
2. **Power** — Connect the 9V battery to the Arduino's barrel jack.
3. **Setup** — Stick reflective tape on the object whose RPM you want to measure (e.g., a CPU fan, drill chuck).
4. **Operation** — Position the TCRT5000 sensor 1–2 cm from the tape, facing it directly. Adjust the module's potentiometer until the indicator LED flickers only as the tape passes.
5. **Reading** — The LCD displays the real-time RPM.

---

## ✅ Advantages & Applications

**Advantages:** contactless (safe for high-speed objects) · portable · simple module-based construction · low cost

**Applications:**
- Measuring speed of PC fans, drill machines, and other motors
- Educational demonstration of sensor interfacing and RPM calculation
- Basic industrial maintenance and troubleshooting

---

## 🚀 Possible Improvements

- Data logging to SD card
- Wireless RPM monitoring (Bluetooth / Wi-Fi)
- Support for readings beyond 999 RPM with a wider display
- Reduced sensitivity to direct sunlight

---

## 👤 Author

**Mohammad Tanzid Ahmed**
B.Sc. in Electrical & Electronic Engineering, KUET
Supervisor: Dr. Md. Shahjahan, Professor, Dept. of EEE, KUET
📧 tanzidvai39@gmail.com &nbsp;·&nbsp; 🔗 [LinkedIn](https://www.linkedin.com/in/tanzid-ahmed-517666343)

---

## 📝 License

Released under the [MIT License](LICENSE).
