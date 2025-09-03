# Wiring Diagram for ESP32 Dual Garage Door Opener

## Component Overview

This project uses an ESP32 to control two garage doors via a dual-channel relay module that simulates button presses on the garage door controllers. **Tested and verified on ESP32-C6 development boards.**

## Wiring Setup Reference

![ESP32 Wiring Setup](photos/wiring_photo.jpg)

*ESP32 development board connected to dual-channel relay module. The pins at the upper right connect in parallel to the garage door button wires.*

## Relay Module Reference

![2-Channel Relay Module](photos/relay_module.jpg)

*Typical 2-channel relay module with screw terminals for garage door connections*

## Detailed Connection Guide

### ESP32 to Relay Module Connections

| ESP32 Pin | Relay Module Pin | Description |
|-----------|------------------|-------------|
| GPIO 15   | IN1              | Control signal for Door 1 |
| GPIO 19   | IN2              | Control signal for Door 2 |
| 5V/3.3V   | VCC              | Power supply (check relay module specs) |
| GND       | GND              | Common ground |

### Power Supply Requirements

**For External 5V DC Power (ESP32-C6):**
- **Voltage**: 5V ±5% (4.75V - 5.25V)
- **Current**: Minimum 1A, recommended 2A
- **Supercapacitor**: 1.5F, 5.5V or higher rating
  - **Purpose**: Provides power stability during boot and operation
  - **Connection**: Across the 5V power bus (VIN to GND)
  - **Required for**: ESP32-C6 external power operation

**For USB Power:**
- **Standard USB power** works directly for development and testing
- **No additional components required**

### Relay Module to Garage Door Controller

| Relay Module | Garage Door Button | Connection |
|--------------|-------------------|------------|
| Relay 1 COM  | Door 1 Terminal 1 | Common connection |
| Relay 1 NO   | Door 1 Terminal 2 | Normally Open contact |
| Relay 2 COM  | Door 2 Terminal 1 | Common connection |
| Relay 2 NO   | Door 2 Terminal 2 | Normally Open contact |

## Relay Module Specifications

- **Type**: Dual-channel Normally Open (NO) relay module
- **Control Voltage**: 5V or 3.3V (check your module)
- **Switching Current**: Minimum 10mA
- **Contact Rating**: 10A @ 120V AC (for garage door controller)
- **Isolation**: Optoisolated (recommended for safety)

## Operation Sequence

1. **Idle State**: 
   - GPIO 15 and GPIO 19 are HIGH
   - Relays are open (NO contacts disconnected)
   - Garage doors remain in current state

2. **Door Activation**:
   - GPIO pin goes LOW for 500ms
   - Relay closes (NO contacts connect)
   - Garage door controller receives button press signal
   - GPIO returns to HIGH
   - Relay opens (NO contacts disconnect)

3. **Door Movement**:
   - If door is closed → opens
   - If door is open → closes
   - If door is moving → stops

## Safety Considerations

- **Isolation**: Use relay modules with optoisolation to protect ESP32
- **Testing**: Always test with multimeter before connecting to garage door system
- **Fuses**: Consider adding appropriate fuses for additional protection
- **Voltage**: Ensure relay module voltage matches ESP32 output (3.3V or 5V)
- **Current**: Verify relay can handle garage door controller current requirements

## Troubleshooting

- **Door doesn't respond**: Check relay connections and garage door button terminals
- **ESP32 resets**: Verify power supply can handle relay module current draw
- **Intermittent operation**: Check for loose connections or poor grounding
- **Wrong door activates**: Verify GPIO pin assignments match relay connections
