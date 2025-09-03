# ESP32 Rainmaker Dual Relay Controller Modifications

## Overview
This document describes the modifications made to convert the ESP32 Rainmaker project from a **pulse-based garage door opener** to a **generic dual relay controller** with unlimited relay control.

## What Changed

### Before (Pulse-Based Garage Door Opener)
- Relays were activated for exactly 500ms when triggered
- Rainmaker app showed momentary button behavior
- Relays automatically returned to OFF state after pulse
- State was always reported back to Rainmaker as OFF
- **Purpose**: Garage door control only

### After (Generic Dual Relay Controller)
- Relays remain in their commanded state indefinitely
- Rainmaker app shows persistent toggle switch behavior
- Relays stay ON or OFF until user changes the state
- State is accurately reported back to Rainmaker
- **Purpose**: Generic relay control for any application

## Code Changes Made

### 1. `main/app_priv.h`
- **Removed**: `RELAY_PULSE_DURATION_MS` constant (no longer needed)
- **Changed**: Default states from `true` (HIGH) to `false` (LOW)
  - `DEFAULT_DOOR_1_STATE` now `false` (relay closed by default)
  - `DEFAULT_DOOR_2_STATE` now `false` (relay closed by default)
- **Note**: GPIO pin names kept for compatibility but now represent generic relay outputs

### 2. `main/app_driver.c`
- **Removed**: Pulse task functions (`door1_pulse_task`, `door2_pulse_task`)
- **Removed**: Pulse state tracking variables (`g_door1_pulse_active`, `g_door2_pulse_active`)
- **Added**: Direct state tracking variables (`g_door1_state`, `g_door2_state`)
- **Modified**: `app_driver_set_door1_state()` and `app_driver_set_door2_state()` functions
  - Now directly set GPIO levels based on state
  - No more task creation or timing delays
  - Immediate state changes

### 3. `main/app_main.c`
- **Modified**: `write_cb()` function
  - Now handles both ON and OFF commands for each relay
  - Updates Rainmaker state to reflect actual relay state
  - No more automatic state reset to OFF
- **Updated**: GPIO initialization to use default states
- **Updated**: Ready banner text to reflect new functionality

## How It Works Now

### Relay Control Logic
1. **GPIO HIGH** = Relay OPEN (no connection)
2. **GPIO LOW** = Relay CLOSED (connection made)

### State Management
- Each relay maintains its current state in memory
- State changes are immediately applied to GPIO
- Rainmaker app shows accurate current state
- States persist across reboots (using default values)

### User Experience
- **Rainmaker App**: Shows toggle switches for each relay
- **Relay 1**: Independent ON/OFF control
- **Relay 2**: Independent ON/OFF control
- **No Time Limits**: Relays stay in commanded state indefinitely

## Applications

### **Generic Relay Control**
This system can now control any device connected to the relays:

- **Lighting Systems**: Indoor/outdoor lights, LED strips, lamps
- **Appliances**: Fans, pumps, heaters, air conditioners
- **Security Systems**: Cameras, motion sensors, alarms
- **Industrial Equipment**: Motors, valves, sensors
- **Home Automation**: Smart plugs, switches, timers
- **DIY Projects**: Any electrical device requiring relay control

### **Hardware Requirements**
- **ESP32 Development Board** (ESP32, ESP32-C6, ESP32-S3, etc.)
- **2-Channel Relay Module** (5V or 3.3V compatible)
- **Power Supply** appropriate for your relay module
- **Devices to Control** (lights, motors, etc.)

## Safety Features

### Startup Protection
- GPIO pins are set to safe states immediately on boot
- Default states prevent accidental relay activation
- Double initialization for safety

### State Validation
- All state changes are logged for debugging
- Invalid states are prevented
- LED indicator shows when any relay is active

## Testing the Modifications

### Build Verification
```bash
./build.sh build
```
✅ Build successful - no compilation errors

### Expected Behavior
1. **Power On**: Relays start in default OFF state (GPIO HIGH)
2. **Rainmaker App**: Shows both relays as OFF
3. **Toggle ON**: Relay closes (GPIO LOW), stays closed
4. **Toggle OFF**: Relay opens (GPIO HIGH), stays open
5. **State Persistence**: Relays maintain state until changed

### LED Indicator
- **LED OFF**: Both relays are open (default state)
- **LED ON**: At least one relay is closed

## Benefits of New System

1. **Flexibility**: Users can control relay states independently
2. **Versatility**: Can control any device, not just garage doors
3. **Reliability**: No timing dependencies or task scheduling
4. **User Experience**: Clear visual feedback in Rainmaker app
5. **Safety**: Immediate state changes, no unexpected behavior
6. **Maintenance**: Simpler code, easier to debug

## Compatibility

- **Hardware**: No changes required - same GPIO pins
- **Rainmaker App**: Same device type (switch), enhanced functionality
- **WiFi/Network**: No changes to networking code
- **OTA Updates**: Still supported for future firmware updates

## Future Enhancements

- **State Persistence**: Save relay states to NVS for reboot recovery
- **Scheduling**: Add time-based relay control
- **Scenes**: Create preset relay configurations
- **Local Control**: Add physical button support for manual control
- **Device Templates**: Pre-configured setups for common applications

## Conclusion

The modifications successfully convert the project from a simple pulse-based garage door opener to a flexible, **generic dual relay controller**. Users can now control any device connected to the relays independently through the Rainmaker app, with relays maintaining their commanded states indefinitely until changed. This makes the system suitable for a wide variety of home automation, industrial control, and DIY projects.
