# 📡 Ground Station – Qt Quick (Qt 6.8.2)

This is a **Ground Station Telemetry Viewer** built with **Qt 6.8.2** using **Qt Quick (QML + C++)**. The application reads telemetry data from a serial port, detects the active port automatically, and displays the data in a modern, responsive UI.

> ⚠️ This project is under active development. More features will be added soon.

---

## ✨ Features

- 🛰️ Real-time telemetry display over serial port
- 🔌 **Auto-detection of active COM port** (based on live data stream)
- 💡 Built using **Qt Quick (QML)** for modern UI
- 🌙 Light & Dark mode support (planned)
- 🧩 Modular C++ backend connected to QML frontend

---

## 📦 Project Structure

```
GroundStation/
├── qml/
│   ├── Main.qml
│   └── components/
│       └── TelemetryView.qml
├── src/
│   ├── main.cpp
│   ├── SerialManager.cpp
│   └── SerialManager.h
├── assets/
│   └── icons, fonts, etc.
├── CMakeLists.txt / GroundStation.pro
└── README.md
```

---

## ⚙️ Requirements

- Qt 6.8.2 or higher (with Qt Quick modules installed)
- Qt Creator (recommended)
- USB-to-Serial driver installed
- Windows or Linux

---

## 🚀 Getting Started

### ▶️ Run via Qt Creator

1. Open the `.pro` or `CMakeLists.txt` file in **Qt Creator**.
2. Make sure Qt 6.8.2 is set as the active kit.
3. Build and run the project.
4. The app automatically scans serial ports and connects to the one receiving valid telemetry.

### 💻 Run from Terminal (if using CMake)

```bash
mkdir build
cd build
cmake ..
make
./GroundStation
```

---

## 🔌 Serial Port Auto-Detection

The app automatically scans available serial ports and selects the one receiving valid telemetry. Detection is based on:

- Known baud rate (e.g. 57600, 115200)
- Message patterns or framing
- Stability of incoming data

Once detected, the app connects and begins streaming data to the UI.

---

## 🧩 Planned Features

- [ ] Log telemetry to CSV or JSON
- [ ] Display location data on an interactive map (Mapbox or Qt Location)
- [ ] Uplink commands to drone/vehicle
- [ ] Realtime charts and analytics
- [ ] Light/Dark theme switch

---

## 🧑💻 Author

- Developer: [Your Name]
- Contact: [your_email@example.com] or [GitHub Profile]

---

## 📜 License

This project is open-source. License: **MIT** *(or specify your own)*

