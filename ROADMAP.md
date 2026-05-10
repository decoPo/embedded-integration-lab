# Roadmap

Planned demos and topics. Order is indicative, not committed.

## Demos

- [ ] **01 — Node-RED embedded logger.** STM32 Black Pill F411 + IMU over USB CDC.
      Dashboard with chart, gauge, status, CSV logging and a control button back to the device.
- [ ] **02 — RTT-based telemetry.** SEGGER J-Link RTT as the transport instead of UART/USB CDC,
      bridged into Node-RED.
- [ ] **03 — STM32CubeMonitor demo.** Out-of-the-box ST tooling, compared with the Node-RED route.
- [ ] **04 — SCPI bench controller.** Programmable PSU / DMM driven from a small dashboard for repeatable
      measurements.
- [ ] **05 — Saleae Logic 2 automation.** Triggering captures and pulling protocol decodes from a
      validation workflow.
- [ ] **06 — CAN bus monitor.** Live frame view with filters, error counters and CSV export.
- [ ] **07 — MQTT gateway.** Multi-device telemetry, centralised dashboard.
- [ ] **08 — Automated validation reporting.** Pass/fail runs, structured logs, generated report.

## Cross-cutting topics

- [ ] Zephyr-based variants of selected demos (parallel to the dedicated Zephyr lab).
- [ ] Power profiling integration.
- [ ] Manufacturing-style test panel (serial number, run, pass/fail).

This list will move as the work progresses; see [`PROGRESS.md`](PROGRESS.md) for what has
actually shipped.
