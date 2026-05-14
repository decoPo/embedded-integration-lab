# 02 — Node-RED IMU dashboard

Live telemetry dashboard driven by an Arduino Nano ESP32 reading an MPU6500
accelerometer over I²C. The PC side is Node-RED with Dashboard 2.0 — a
real-time line chart for AX/AY/AZ and a small "spirit level" widget that
follows board tilt.

```
 ┌──────────────────┐     USB CDC      ┌────────────────────────────┐
 │ Nano ESP32       │ ── ASCII ─────▶  │ Node-RED + Dashboard 2.0   │
 │  + MPU6500 (I²C) │  AX=…;AY=…;AZ=…  │  • line chart (AX/AY/AZ)   │
 └──────────────────┘                  │  • spirit level (tilt)     │
                                       └────────────────────────────┘
```

## Hardware

| Item        | What                                              |
| ----------- | ------------------------------------------------- |
| MCU board   | Arduino **Nano ESP32** (ESP32-S3, 3.3 V)          |
| IMU         | **MPU6500** breakout (also sold as MPU6050/9250)  |
| Pull-ups    | **2× 4.7 kΩ** on SDA/SCL to 3V3 (external)        |
| Wires       | Breadboard + 6 jumpers                            |
| USB cable   | USB-C to the board                                |

Wiring:

```
Nano ESP32        MPU6500
3V3       ─────── VCC
GND       ─────── GND
A4 (SDA)  ─────── SDA  ── 4.7 kΩ ── 3V3
A5 (SCL)  ─────── SCL  ── 4.7 kΩ ── 3V3
```

Notes:

- Always use external pull-ups for I²C — internal MCU pull-ups are too weak.
- Nano ESP32 is 3.3 V native, so no level shifter is needed. A classic 5 V
  Uno/Nano R3 with a 3.3 V MPU6500 would need one.

## Layout

```
demos/02-node-red-imu-dashboard/
├── README.md
├── node-red/
│   ├── flows-live.json   ← serial in (real board)
│   └── flows-sim.json    ← inject-driven simulator (no hardware)
├── sketches/
│   ├── 01-i2c-scan/      ← prove the sensor is alive
│   └── 02-mpu6500-stream/← stream AX/AY/AZ at ~20 Hz
└── scripts/
    └── fake_imu_data.py  ← TCP source for flows-sim, no hardware needed
```

## Quick start — with hardware

1. Install Arduino IDE 2.x and the **Arduino ESP32 Boards** package
   (Boards Manager → search `esp32` → install the one by *Arduino*, not
   Espressif). Select **Tools → Board → Arduino Nano ESP32**.
2. Open `sketches/01-i2c-scan/01-i2c-scan.ino`, upload, open Serial Monitor
   at **115200 baud** with **DTR** checked. You should see `device at 0x68`.
3. Upload `sketches/02-mpu6500-stream/02-mpu6500-stream.ino`. Serial Monitor
   should now stream lines like:
   ```
   AX=0.010;AY=0.020;AZ=0.940
   ```
4. Install Node-RED + Dashboard 2.0 + serialport
   (see [`docs/setup-windows.md`](../../docs/setup-windows.md)).
5. In Node-RED, **Import** → paste `node-red/flows-live.json` → **Import**
   → **Deploy**.
6. Edit the *serial in* node — set **Serial Port** to your Nano ESP32's COM
   port, keep **DTR=high**, **RTS=low**. Deploy again.
7. Open <http://127.0.0.1:1880/dashboard> — chart and tilt widget should be
   live.

## Quick start — without hardware

Same Node-RED install, but use the simulator:

1. **Import** `node-red/flows-sim.json` → **Deploy**. This already runs an
   inject + JS function generating synthetic AX/AY/AZ.
2. Open <http://127.0.0.1:1880/dashboard> — the chart moves on its own.

Or, to exercise the same TCP path the real board uses, run:

```powershell
python scripts/fake_imu_data.py
```

(standard library only, Python 3.8+; the sim flow listens on TCP `127.0.0.1:5000`).

## Common pitfalls

- **Serial Monitor blank on Nano ESP32**: native USB-CDC; firmware buffers
  output until DTR is asserted. Tick the **DTR** checkbox in Arduino IDE,
  or set DTR=high in the Node-RED serial config.
- **Board stuck in "waiting for download"**: ESP32-S3 latched into ROM
  bootloader. Double-tap the white **RESET** button → it enters Arduino DFU
  mode → upload again.
- **Chart draws only one line instead of three**: the chart needs one `msg`
  per series with `msg.topic` = series name and `msg.payload` = number.
  The flow's *Split AX/AY/AZ* function does that — make sure it is wired
  between the parser and the chart.
- **`serial in` node greyed out after import**: install
  `node-red-node-serialport` from **Manage palette → Install**.
- **Dashboard tab is blank**: the widget probably has no group assigned —
  open it and pick (or create) a group.

## Status

Built around a 2026-05 community talk; talk material will be added back
once it has been presented and incorporates feedback.
