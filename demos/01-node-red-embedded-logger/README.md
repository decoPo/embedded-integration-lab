# 01 — Node-RED embedded logger

A minimal end-to-end demo that turns Node-RED into a live telemetry dashboard,
CSV logger and control panel for a small STM32 board.

## What it does

```
 ┌──────────────┐    USB CDC    ┌──────────────────────┐
 │ Black Pill   │ ─ telemetry ▶ │ Node-RED on the PC   │
 │ STM32F411    │               │  • chart             │
 │ + sensor*    │ ◀ commands ── │  • gauge             │
 └──────────────┘               │  • status text       │
                                │  • CSV file logger   │
                                │  • LED on/off button │
                                └──────────────────────┘
```

The board sends ASCII telemetry once per ~100 ms, e.g.

```
AX=0.12;AY=-0.45;AZ=0.98
```

A small JavaScript parser in a Node-RED Function node turns it into a
structured object that drives the dashboard widgets and the CSV logger.
A dashboard button publishes a short command (`LED:ON` / `LED:OFF`) back to
the same serial port; the firmware reacts by toggling an on-board LED.

\* The exact sensor is intentionally left open for now — any I²C IMU
(MPU-6050, ICM-20948, LSM6DS3, …) works because the FW just emits ASCII
key/value pairs and the dashboard does not assume a fixed schema.

## Hardware

- STM32 Black Pill (STM32F411) — the same demo will work on a Nucleo F4 or any
  STM32 with USB CDC, with minor pin/clock changes.
- One I²C IMU on `PB6/PB7` (subject to confirmation when the board is on the bench).
- USB-C / micro-USB cable straight to the PC.

## Software

- **Firmware:** STM32CubeIDE, HAL, USB Device CDC class, plain `printf` over
  CDC. Kept deliberately simple — no FreeRTOS, no protobuf, no binary
  protocol.
- **PC side:** Node.js LTS, `node-red`, `node-red-dashboard`,
  `node-red-node-serialport`. See [`docs/setup-windows.md`](../../docs/setup-windows.md).

## Layout (planned)

```
demos/01-node-red-embedded-logger/
├── README.md            ← this file
├── node-red/
│   └── flows.json       ← importable Node-RED flow
├── scripts/
│   └── fake_imu_data.py ← stand-in telemetry source for attendees without HW
├── firmware/
│   └── blackpill-f411-imu/  ← CubeIDE project (added during talk prep)
└── data/
    └── example_log.csv  ← short sample capture
```

Subfolders are added as each piece lands.

## How to try it

1. Install Node.js LTS, then Node-RED + the dashboard plugin
   ([Windows guide](../../docs/setup-windows.md)).
2. Start `node-red` and open `http://127.0.0.1:1880`.
3. Import `node-red/flows.json` (Menu → Import).
4. Either:
   - plug in a pre-flashed board and select its COM port in the *serial in*
     and *serial out* nodes, or
   - run `python scripts/fake_imu_data.py` and point the flow at the virtual
     port it creates.
5. Open `http://127.0.0.1:1880/ui` and watch the chart move.

## Status

Work in progress. The talk on 2026-05-14 will be the first public airing.
