# Adaptive-Street-Light-Control-LPC2148
LPC2148-based adaptive streetlight control using internal RTC scheduling, 10-bit ADC-based LDR sensing, and an external interrupt-driven keypad menu for configurable time boundaries.
# 🌃 Adaptive Street Light Control Using RTC and Environmental Illumination
### LPC2148 | ARM7 | Embedded C | Keil µVision

An intelligent streetlight automation system implemented using the LPC2148 microcontroller, featuring internal RTC-based time scheduling, 10-bit ADC-based LDR illumination sensing, and an external interrupt-driven configuration menu.

The system automatically controls streetlight operation based on user-configurable time boundaries and surrounding illumination levels.

---

## 📌 Project Overview

This project implements an adaptive streetlight control system using the LPC2148 ARM7 microcontroller.

The system integrates the internal Real-Time Clock (RTC) and ADC peripherals to monitor real-time information and environmental illumination.

A 4×4 keypad allows users to configure RTC parameters and streetlight operating boundaries. An external interrupt is connected to GPIO pin P0.1. When a falling-edge signal is detected, the external interrupt flag is set, the interrupt condition is cleared, and the system enters the configuration menu.

During normal operation, the 16×2 LCD displays the current RTC values, LDR illumination value, and streetlight ON/OFF status.

The streetlight is switched ON only when:
1. The current RTC time is within the configured starting and ending time boundaries.
2. The measured LDR value satisfies the predefined illumination threshold condition.

This provides time-dependent and environment-dependent automatic streetlight control.

## 🎯 Project Objectives

- Implement automatic streetlight control using the LPC2148 internal RTC.
- Monitor environmental illumination using an LDR sensor.
- Convert LDR analog readings using the 10-bit internal ADC.
- Configure RTC parameters through a keypad-based menu.
- Configure streetlight starting and ending time boundaries.
- Implement an external interrupt-driven editing interface.
- Display real-time information and streetlight status on a 16×2 LCD.
- Reduce unnecessary energy consumption through adaptive lighting control.

## 🧩 Hardware Requirements

| Component | Description |
|---|---|
| LPC2148 | ARM7 microcontroller |
| 16×2 LCD | Parallel interface LCD display |
| 4×4 Keypad | User input and menu navigation |
| LDR Sensor | Environmental illumination sensing |
| 5 kΩ Fixed Resistor | LDR voltage divider |
| LED | Streetlight representation |
| 32.768 kHz Crystal | RTC clock source |
| 3.3 V CMOS Backup Battery | RTC backup supply |
| External Interrupt Button | Configuration menu activation |

## 💻 Software Requirements

- Embedded C Programming
- Keil µVision IDE
- Flash Magic
- LPC2148 Microcontroller

## ⚙️ System Architecture

The project uses the following LPC2148 peripherals:

| Peripheral | Application |
|---|---|
| Internal RTC | Time and date tracking |
| 10-bit ADC | LDR analog value measurement |
| External Interrupt | Configuration menu activation |
| GPIO | LED and keypad interfacing |
| GPIO | 16×2 LCD parallel interfacing |

**RTC Clock Configuration:**

The RTC supports operation using its internal oscillator or an external 32.768 kHz crystal clock source. A backup supply is provided for maintaining RTC operation when the main supply is unavailable.

**LDR Interface:**

The LDR and 5 kΩ fixed resistor form a voltage divider. The resulting analog voltage is connected to the LPC2148 ADC input at physical pin 28.

The ADC provides a 10-bit digital result (0–1023).

## 🖥️ Normal Display Operation

During normal operation, the 16×2 LCD displays:

- Current hour, minute, and second.
- Date, month, year, and day.
- LDR measured illumination value (ADC reading).
- Streetlight ON/OFF indication using a symbol.

The LCD continuously updates the RTC information and environmental illumination status.

## 🔔 External Interrupt-Driven Configuration

An external interrupt button is connected to LPC2148 GPIO pin P0.1.

**Interrupt Configuration:**
- Interrupt trigger: Falling edge (HIGH to LOW).
- On interrupt detection, an editing flag is set.
- The interrupt condition is cleared.
- The main program detects the flag and enters the configuration menu.

Only the external interrupt is used for entering editing mode.

### Main Configuration Menu

When the external interrupt button is pressed, the following menu is displayed:

| Option | Function |
|---|---|
| 1 | RTC Edit |
| 2 | Time Boundaries Edit |
| 3 | Display Present Time Boundaries |
| 4 | Exit Editing Mode |

### 1. RTC Editing Menu

The RTC editing menu allows individual modification of date and time parameters.

| Option | Parameter |
|---|---|
| 1 | Hour |
| 2 | Minute |
| 3 | Second |
| 4 | Day |
| 5 | Date |
| 6 | Month |
| 7 | Year |
| 8 | Exit |

### 2. Time Boundaries Editing

The user can configure the streetlight operating schedule by modifying the starting and ending time.

**Starting Time Configuration:**

| Option | Parameter |
|---|---|
| 1 | Starting Hour (S_H) |
| 2 | Starting Minute (S_M) |
| 3 | Starting Second (S_S) |
| 4 | Exit |

**Ending Time Configuration:**

| Option | Parameter |
|---|---|
| 1 | Ending Hour (E_H) |
| 2 | Ending Minute (E_M) |
| 3 | Ending Second (E_S) |
| 4 | Exit |

### 3. Display Present Time Boundaries

Displays the currently configured starting and ending time boundaries for monitoring.

### 4. Exit Editing Mode

Exits the configuration menu and returns the system to normal automatic streetlight operation.

## 🔄 Working Principle

The system follows a combination of RTC-based scheduling and environmental illumination sensing.

1. Initialize the LPC2148 peripherals, RTC, ADC, LCD, keypad, and GPIO.
2. Display the current RTC information on the LCD.
3. Continuously read the LDR analog value through the 10-bit ADC.
4. Check whether the current RTC time falls within the configured starting and ending time boundaries.
5. If the current time is outside the configured operating period, switch OFF the streetlight.
6. If the current time is within the operating period, compare the LDR ADC reading with the predefined threshold.
7. If the measured illumination satisfies the low-light condition, switch ON the LED.
8. If sufficient ambient illumination is available, switch OFF the LED.
9. Continuously update the LCD with RTC values, LDR readings, and LED status.
10. When the external interrupt button is pressed, enter the configuration menu to edit RTC values and time boundaries.

## ✨ Key Features

- RTC-based automatic time scheduling.
- 10-bit ADC-based environmental illumination measurement.
- External interrupt-driven configuration mode.
- Individual RTC parameter editing.
- User-configurable starting and ending time boundaries.
- 4×4 keypad-based menu navigation.
- Real-time LCD monitoring.
- Automatic LED control based on time and illumination conditions.
- RTC backup power support.

## 📂 Repository Structure

```text
Adaptive-Street-Light-Control-LPC2148/
│
├── README.md
│
├── Images/
│   ├── project_setup.jpg
│   ├── block_diagram.png
│   ├── circuit_diagram.png
│   └── lcd_output.jpg
│
├── Source_Code/
│   ├── main.c
│   ├── rtc.c
│   ├── rtc.h
│   ├── adc.c
│   ├── adc.h
│   ├── lcd.c
│   ├── lcd.h
│   ├── keypad.c
│   ├── keypad.h
│   └── Other source files
│
└── Documentation/
    └── Project_Report.pdf
```

## 📸 Project Demonstration

Project hardware setup, circuit connections, LCD display outputs, and working demonstration photographs will be included in the Images folder.

## 🚀 Future Enhancements

- IoT-based remote streetlight monitoring.
- Wireless communication between streetlight systems.
- Automatic fault detection.
- Energy consumption monitoring.
- Solar-powered streetlight integration.

## 👨‍💻 Author

**G. Jaswanth Kumar**

Embedded Systems | ARM7 | LPC2148 | Embedded C | Microcontroller Programming

---

⭐ If you find this project useful, consider giving this repository a star!

