# Node-RED as a rapid integration layer for embedded

Community talk, 2026-05-14, ~20–30 minutes, with an optional ~1 hour hands-on
workshop afterwards for anyone who brought a laptop.

## Pitch

> An embedded developer can build a working telemetry dashboard, logger and
> control panel for a real device in a single evening — without writing a
> frontend, a backend or a cloud stack.

The goal of the talk is not to teach Node-RED in depth. It is to show where it
fits in an embedded engineer's toolbox: as a glue layer between the device
under test and the rest of the validation/observation infrastructure.

## Audience

Embedded / firmware engineers and makers. No assumed Node-RED experience.

## Outline (target ~25 min)

1. **What Node-RED is, in one slide** — flow-based runtime on top of Node.js,
   nodes for serial, MQTT, HTTP, dashboards, files, functions. *(~2 min)*
2. **Why it is interesting for embedded** — rapid prototyping, validation,
   logging, manufacturing test panels, instrument glue. *(~3 min)*
3. **Architecture of today's demo** — Black Pill F411 → USB CDC → Node-RED →
   dashboard + CSV. *(~2 min)*
4. **Live demo.** This is the bulk of the value. *(~10–12 min)*
   - Telemetry from the board on a chart and a gauge
   - Dashboard button → command back to the device (LED control)
   - CSV log being written in real time
5. **Where this scales to** — RTT, MQTT, SCPI instruments, Saleae automation,
   manufacturing test, power monitoring. *(~3 min)*
6. **Limits and honest caveats** — not real-time, can become a "spaghetti
   flow" at scale, not a firmware replacement. *(~2 min)*
7. **Q&A and pointer to the workshop / repo.** *(~2 min)*

## Live demo notes

- Bring a pre-flashed Black Pill so the talk does not depend on the build
  toolchain working on the venue Wi-Fi.
- Have the dashboard at `http://127.0.0.1:1880/ui` opened on the projector
  before the section starts.
- Have a "fake telemetry" Python script ready as a fallback in case the USB
  CDC port misbehaves on stage.

## Workshop (optional, ~60 min)

For attendees who want to try it on their own machine:

- Install Node.js + Node-RED + `node-red-dashboard`
  (see [`docs/setup-windows.md`](../../docs/setup-windows.md)).
- Import the `flows.json` from
  [`demos/01-node-red-embedded-logger/`](../../demos/01-node-red-embedded-logger/).
- Either plug in one of the pre-flashed boards (3–5 will be available at the
  workshop) or run the included fake-telemetry script.
- Open the dashboard, watch the chart move, press the LED button.

## Slides

Slides will be added here once finalised:

- `slides.pdf` — *not yet committed*

## Related links

- Demo project: [`demos/01-node-red-embedded-logger/`](../../demos/01-node-red-embedded-logger/)
- Setup guide: [`docs/setup-windows.md`](../../docs/setup-windows.md)
- Roadmap: [`ROADMAP.md`](../../ROADMAP.md)
