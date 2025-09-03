# ESP32 Dual Relay Controller

This project creates an ESP32-based **generic dual relay controller** using Espressif RainMaker that can control two independent relays remotely. The implementation is based on the ESP RainMaker switch example with modifications to provide unlimited relay control rather than pulse-based operation.

**Tested and verified on ESP32-C6 development boards.**

## 📚 **Important: Complete Development Guide**

**For a comprehensive understanding of this project, including the complete development process, technical decisions, lessons learned, and future enhancements, please read:**

**[ESP32_RainMaker_Development_Case_Study.md](ESP32_RainMaker_Development_Case_Study.md)**

This case study documents the complete transformation from the Espressif switch example to this production-ready dual relay controller, including:
- **Complete code changes** and technical implementation
- **Safety features** and security considerations
- **Platform compatibility** testing (iOS vs Android)
- **Lessons learned** from real development challenges
- **Alternative approaches** considered and trade-offs made
- **Future enhancement** possibilities
- **Development environment** setup and debugging techniques

*This README provides the essential information to get started, while the case study offers deep technical insights and development guidance.*

## Key Features

### Hardware Control
- **Dual Relay Support**: Controls two relays independently
- **Unlimited Control**: Relays maintain their commanded state indefinitely
- **Normally Open Relays**: GPIO pins are HIGH by default, go LOW when relay is activated
- **Safe Operation**: Relays start in OFF state and maintain state until changed

### Software Features
- **RainMaker Integration**: Remote control via ESP RainMaker mobile app
- **Real-time Status**: App shows current relay states accurately
- **LED Indicator**: RGB LED shows when any relay is active
- **Independent Control**: Each relay operates independently

## Hardware Setup

### GPIO Connections
- **Relay 1**: GPIO 15 (default HIGH, goes LOW when relay is activated)
- **Relay 2**: GPIO 19 (default HIGH, goes LOW when relay is activated)
- **Boot Button**: GPIO 0 (for WiFi reset and configuration)

### Relay Wiring
Connect normally open relays to the GPIO pins:
- Relay 1: Connect to GPIO 15
- Relay 2: Connect to GPIO 19
- Each relay can control any device (lights, motors, pumps, etc.)

**For detailed wiring instructions, see [WIRING.md](WIRING.md)**

## Implementation Details

### GPIO Configuration
- **Relay 1**: GPIO 15 (configurable in `app_priv.h`)
- **Relay 2**: GPIO 19 (configurable in `app_priv.h`)
- **Boot Button**: GPIO 0 (for WiFi configuration)

### Relay Control
- **State Management**: Relays maintain their commanded state indefinitely
- **Immediate Response**: GPIO changes occur immediately without delays
- **Direct Control**: No task scheduling or timing dependencies

### RainMaker Devices
- **Device Type**: Two separate switch devices
- **Names**: "Relay 1" and "Relay 2"
- **Node Name**: "Dual Relay Controller"
- **Control**: Each device has independent power parameter

## Operation

1. **Remote Control**: Use the ESP RainMaker mobile app to control each relay independently
2. **Real-time Status**: App shows current relay states accurately
3. **State Persistence**: Relays maintain their commanded state indefinitely
4. **Relay Operation**: Relays provide continuous control for connected devices

### Operation Sequence

1. **Idle State**: 
   - GPIO 15 and GPIO 19 are HIGH
   - Relays are open (NO contacts disconnected)
   - Connected devices remain in current state

2. **Relay Activation**:
   - GPIO pin goes LOW (relay closes)
   - Relay closes (NO contacts connect)
   - Connected device receives power/control signal
   - Relay maintains state until commanded to change

3. **Device Control**:
   - Device receives continuous power/control signal
   - Device operates according to relay state
   - State persists until manually changed

## Configuration

The GPIO pins can be modified in `main/app_priv.h`:
```c
#define RELAY_1_GPIO    15
#define RELAY_2_GPIO    19
```

### Customization Options

#### GPIO Pins
Modify in `main/app_priv.h`:
```c
#define RELAY_1_GPIO    15
#define RELAY_2_GPIO    19
```

#### Device Names
Modify in `main/app_main.c`:
```c
relay1_device = esp_rmaker_device_create("Relay 1", ESP_RMAKER_DEVICE_SWITCH, NULL);
relay2_device = esp_rmaker_device_create("Relay 2", ESP_RMAKER_DEVICE_SWITCH, NULL);
```

## Building and Flashing

1. Set up ESP-IDF environment
2. Configure the project: `idf.py menuconfig`
3. Build the project: `idf.py build`
4. Flash to ESP32: `idf.py flash monitor`

### Build Commands
```bash
# Clean build
idf.py fullclean

# Build project
idf.py build

# Flash to device
idf.py flash

# Monitor output
idf.py monitor

# Combined build and flash
idf.py build flash monitor
```

## RainMaker Setup

1. Flash the firmware to your ESP32
2. Follow the ESP RainMaker app setup process
3. The device will appear as "Dual Relay Controller" with two separate switches
4. Each switch controls one relay independently

## File Structure

```
dual_relay_controller/
├── main/
│   ├── app_main.c          # Main application with RainMaker setup
│   ├── app_driver.c        # GPIO control and relay logic
│   ├── app_priv.h          # GPIO definitions and constants
│   └── Kconfig.projbuild   # Build configuration
├── README.md               # Project documentation
├── WIRING.md              # Hardware wiring instructions
├── test_instructions.md   # Testing procedures
├── build.sh               # Build script
└── ESP32_RainMaker_Development_Case_Study.md # Development guide
```

## Key Modifications from Switch Example

1. **Dual Device Support**: Created two separate RainMaker devices instead of one
2. **State Management**: Added persistent state tracking for each relay
3. **GPIO Management**: Configured two GPIO pins with independent control
4. **Relay Control**: Direct GPIO control without timing delays
5. **Callback Handling**: Modified write callback to handle both devices

## Safety Considerations

- **Isolation**: Relays provide electrical isolation between ESP32 and controlled devices
- **Fail-Safe**: GPIO pins default to HIGH (relay open) state
- **State Control**: Relays maintain commanded state for safe operation
- **Independent Operation**: Each relay operates independently
- **Startup Protection**: Multiple safety layers prevent accidental activation during boot
- **Testing**: Always test with multimeter before connecting to controlled devices
- **Fuses**: Consider adding appropriate fuses for additional protection
- **Voltage**: Ensure relay module voltage matches ESP32 output (3.3V or 5V)
- **Current**: Verify relay can handle controlled device current requirements

## Testing

- **Hardware Test**: Use multimeter to verify relay operation
- **Software Test**: Monitor serial output for relay state changes
- **App Test**: Verify RainMaker app control functionality
- **Integration Test**: Test with actual controlled devices

### Testing Procedures
For detailed testing instructions, see [test_instructions.md](test_instructions.md)

## Troubleshooting

- **Device doesn't respond**: Check relay connections and controlled device terminals
- **ESP32 resets**: Verify power supply can handle relay module current draw
- **Intermittent operation**: Check for loose connections or poor grounding
- **Wrong relay activates**: Verify GPIO pin assignments match relay connections

## Hardware Requirements

### ESP32 Development Board:
- **ESP32-C6**: Tested and verified (primary development platform)
- **ESP32-WROOM-32D**: Compatible (GPIO 15/19 available)
- **ESP32-S3-WROOM-1**: Compatible (GPIO 15/19 available)

### Power Supply:
- **USB Power**: Works directly for development and testing
- **External 5V DC**: Requires 1.5F supercapacitor for power stability
  - **Voltage**: 5V ±5% (4.75V - 5.25V)
  - **Current**: Minimum 1A, recommended 2A
  - **Supercapacitor**: 1.5F, 5.5V or higher rating

### Relay Module:
- **Type**: Dual-channel normally open (NO) relay module
- **Control Voltage**: 5V or 3.3V (check your module)
- **Contact Rating**: 10A @ 120V AC (for general purpose use)

## Platform Compatibility

### iOS (Working Correctly):
- ✅ Relays maintain commanded state
- ✅ Persistent switch behavior as intended
- ✅ Reliable relay activation
- ✅ Proper parameter synchronization

### Android (Functional with UI Quirk):
- ✅ Relays work perfectly
- ✅ Button presses control relays
- ✅ Top-level switches work correctly
- ⚠️ Detail view sliders stay ON (platform-specific UI sync issue)

## Usage Instructions

1. **Hardware Setup**: Connect relays to GPIO 15 and 19
2. **Power Supply**: Use USB for development or external 5V with 1.5F supercapacitor
3. **Build**: Run `./build.sh` or `idf.py build`
4. **Flash**: Run `./build.sh flash-monitor`
5. **Configure**: Use ESP RainMaker app to provision device
6. **Control**: Use app to control relays remotely

This implementation provides a robust, safe, and user-friendly solution for remote relay control using ESP32 and RainMaker technology.
