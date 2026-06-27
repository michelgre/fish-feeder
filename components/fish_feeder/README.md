# Fish Feeder for ESPHome

An ESPHome external component implementing a Wi-Fi connected fish feeder based on an ESP32-C3 and an SG90 servo.

The goal of this project is to keep the YAML configuration as small as possible while implementing all the application logic in C++.

## Features

- ESPHome external component
- ESP32-C3 SuperMini target
- SG90 servo control
- Feed on demand
- Persistent feed counter
- Reset feed counter
- Native Home Assistant integration
- OTA updates
- Local control through ESPHome API

## Project status

🚧 Work in progress

Current version: **0.1.0**

## Repository layout

```
fish-feeder/
│
├── components/
│   └── fish_feeder/
│
├── firmware/
│
└── .vscode/
```

## Requirements

- VSCode
- ESPHome extension
- ESPHome CLI
- Python 3

## Hardware

- ESP32-C3 SuperMini
- SG90 servo
- Fish feeder mechanism
- 5V power supply

## Building

```
esphome compile firmware/fish-feeder.yaml
```

## Upload

```
esphome upload firmware/fish-feeder.yaml
```

## Logs

```
esphome logs firmware/fish-feeder.yaml
```

## License

MIT