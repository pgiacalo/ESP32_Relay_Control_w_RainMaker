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
