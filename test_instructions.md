# Testing Instructions for ESP32 Dual Relay Controller

## Hardware Testing

### Power Supply Testing:
1. **USB Power**: Works directly for development and testing
2. **External 5V DC**: Requires 1.5F supercapacitor for ESP32-C6 stability
   - **Voltage**: Should be 5V ±5% (4.75V - 5.25V)
   - **Current**: Should be stable ~300-500mA (not fluctuating)
   - **Supercapacitor**: 1.5F, 5.5V or higher rating

### GPIO Testing:
1. Connect relays to GPIO 15 and GPIO 19
2. Power up the ESP32-C6
3. Monitor serial output for startup messages

## GPIO Testing

### Door 1 (GPIO 15):
- Trigger Door 1 from RainMaker app
- Verify GPIO 15 goes LOW for 0.5 seconds
- Verify relay 1 activates

### Door 2 (GPIO 19):
- Trigger Door 2 from RainMaker app
- Verify GPIO 19 goes LOW for 0.5 seconds
- Verify relay 2 activates

## Serial Monitor Output

Expected messages when doors are triggered:
```
I (xxxx) app_driver: Door 1: Starting pulse (GPIO 15 LOW for 500 ms)
I (xxxx) app_driver: Door 1: Pulse completed, reported OFF to RainMaker

I (xxxx) app_driver: Door 2: Starting pulse (GPIO 19 LOW for 500 ms)
I (xxxx) app_driver: Door 2: Pulse completed, reported OFF to RainMaker
```

## Power Stability Testing

### For External 5V Power:
- **Green LED**: Should be solid on (not blinking)
- **Current draw**: Should be stable ~300-500mA
- **No boot loops**: Device should boot once and stay running
- **RainMaker online**: App should show device as connected
