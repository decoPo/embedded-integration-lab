# Embedded Integration Lab

Public engineering lab focused on embedded integration, telemetry, validation
and rapid prototyping workflows.

The goal is to share small, self-contained demos that connect a real embedded
target (STM32, nRF, ESP32, …) to practical PC-side tooling — dashboards,
loggers, instrument automation, validation reports — and to document what
worked and what did not.

## Demos

| # | Title | Status |
| - | ----- | ------ |
| 01 | [Node-RED embedded logger](demos/01-node-red-embedded-logger/) | in progress |

More are listed in [`ROADMAP.md`](ROADMAP.md). A running progress log lives in
[`PROGRESS.md`](PROGRESS.md).

## Talks

| Date | Title |
| ---- | ----- |
| 2026-05 | [Node-RED as a rapid integration layer for embedded](talks/2026-05-node-red-embedded-logger/) |

## Layout

```
demos/      self-contained demo projects, numbered
talks/      slides, notes and material from talks/workshops
docs/       cross-cutting setup guides and references
```

## Licensing

- Demo code and documentation in this repository are released under the
  [MIT license](LICENSE) unless stated otherwise.
- Some firmware examples include vendor-generated code (for example
  STMicroelectronics CubeMX, Nordic Semiconductor SDK, Zephyr modules).
  That code remains under its respective vendor license; only the surrounding
  glue and configuration in this repository is MIT.
