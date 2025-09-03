# ESP32 Rainmaker Dual Relay Controller

## Overview
This is a **generic dual relay controller** built on the ESP32 platform using ESP Rainmaker technology. It allows users to independently control two relays through the Rainmaker mobile application, with relays maintaining their commanded states (i.e., CLOSED or OPEN) until changed.

## What It Is
- **Dual Relay Controller**: Controls two independent relays
- **Generic Purpose**: Can control any device connected to the relays
- **Unlimited Control**: Relays stay in commanded state until manually changed
- **Cloud Connected**: Remote control via ESP Rainmaker app
- **WiFi Enabled**: Connects to your home/office WiFi network

## Applications

### **Home Automation**
- **Lighting**: Indoor/outdoor lights, LED strips, lamps
- **Appliances**: Fans, pumps, heaters, air conditioners
- **Security**: Cameras, motion sensors, alarms
- **Entertainment**: TVs, speakers, gaming systems

### **Industrial/Commercial**
- **Motors**: Conveyors, pumps, fans
- **Valves**: Water, air, gas control
- **Sensors**: Data collection, monitoring
- **Equipment**: Power tools, machinery

### **DIY Projects**
- **Arduino Projects**: Power control for microcontrollers
- **Robotics**: Motor control, sensor power
- **Aquaponics**: Pump control, lighting systems
- **Smart Home**: Custom automation solutions

## Hardware Requirements

### **Required Components**
- **ESP32 Development Board** (ESP32, ESP32-C6, ESP32-S3, etc.)
- **2-Channel Relay Module** (5V or 3.3V compatible)
- **Power Supply** appropriate for your relay module
- **WiFi Network** for cloud connectivity

### **GPIO Pin Assignment**
- **Relay 1**: GPIO 15
- **Relay 2**: GPIO 19
- **LED Indicator**: WS2812 RGB LED (shows relay status)

### **Relay Module Types**
- **5V Relay Module**: Most common, requires 5V power supply
- **3.3V Relay Module**: Lower power, can be powered from ESP32
- **Solid State Relays**: For AC applications, more expensive
- **Mechanical Relays**: For DC applications, cost-effective

## How It Works

### **Relay Control Logic**
1. **GPIO HIGH** = Relay OPEN (no connection)
2. **GPIO LOW** = Relay CLOSED (connection made)

### **State Management**
- Each relay maintains its current state in memory
- State changes are immediately applied to GPIO
- Rainmaker app shows accurate current state
- States persist across reboots (using default values)

### **Default Behavior**
- **Power On**: Both relays start in OFF state (GPIO HIGH)
- **Safety**: Relays are open by default to prevent accidental activation
- **Indicator**: LED shows when any relay is active

## Setup Instructions

### **1. Hardware Connection**
```
ESP32 GPIO 15 → Relay 1 Control Input
ESP32 GPIO 19 → Relay 2 Control Input
ESP32 3.3V/5V → Relay Module Power
ESP32 GND → Relay Module GND
```

### **2. Software Setup**
```bash
# Clone the repository
git clone <repository-url>
cd ESP32_Dual_Garage_Door_Opener

# Build the firmware
./build.sh build

# Flash to ESP32 (replace PORT with your device port)
./build.sh flash
```

### **3. WiFi Configuration**
1. Power on the ESP32
2. Connect to the ESP32's WiFi network
3. Use the Rainmaker app to configure WiFi credentials
4. Device will connect to your network and Rainmaker cloud

## Using the Rainmaker App

### **Device Discovery**
1. Open ESP Rainmaker app
2. Scan for new devices
3. Select "Dual Relay Controller"
4. Follow setup instructions

### **Control Interface**
- **Relay 1**: Toggle switch for first relay
- **Relay 2**: Toggle switch for second relay
- **Status**: Real-time relay state display
- **History**: Track relay usage over time

### **Features**
- **Remote Control**: Control relays from anywhere
- **Real-time Status**: See current relay states
- **Scheduling**: Set timers for automatic control
- **Scenes**: Create preset relay configurations
- **Sharing**: Allow family members to control relays

## Safety Considerations

### **Electrical Safety**
- **Voltage Limits**: Ensure relays are rated for your application
- **Current Limits**: Don't exceed relay current ratings
- **Isolation**: Use appropriate relays for AC/DC applications
- **Grounding**: Proper grounding for safety

### **Operational Safety**
- **Startup Protection**: Relays default to OFF state
- **State Validation**: All changes are logged and validated
- **Emergency Stop**: Power cycling returns relays to safe state
- **Monitoring**: LED indicator shows active relays

## Troubleshooting

### **Common Issues**
1. **WiFi Connection**: Check network credentials and signal strength
2. **Relay Not Responding**: Verify wiring and power supply
3. **App Not Connecting**: Ensure device is online and claimed
4. **Unexpected Behavior**: Check GPIO pin assignments

### **Debug Information**
- Serial monitor output shows detailed operation logs
- LED indicator provides visual status feedback
- Rainmaker app shows connection status
- Build logs available for troubleshooting

## Customization

### **GPIO Pin Changes**
Edit `main/app_priv.h`:
```c
#define GARAGE_DOOR_1_GPIO    15  // Change to desired pin
#define GARAGE_DOOR_2_GPIO    19  // Change to desired pin
```

### **Default States**
Edit `main/app_priv.h`:
```c
#define DEFAULT_DOOR_1_STATE  false   // true = ON, false = OFF
#define DEFAULT_DOOR_2_STATE  false   // true = ON, false = OFF
```

### **Device Names**
Edit `main/app_main.c`:
```c
door1_device = esp_rmaker_device_create("Custom Name 1", ESP_RMAKER_DEVICE_SWITCH, NULL);
door2_device = esp_rmaker_device_create("Custom Name 2", ESP_RMAKER_DEVICE_SWITCH, NULL);
```

## Future Enhancements

### **Planned Features**
- **State Persistence**: Save relay states to flash memory
- **Local Control**: Physical buttons for manual operation
- **Advanced Scheduling**: Complex timing patterns
- **Device Templates**: Pre-configured setups for common applications

### **Community Contributions**
- **New Relay Types**: Support for different relay modules
- **Sensor Integration**: Temperature, humidity, motion sensors
- **Automation Rules**: If-then logic for smart control
- **API Integration**: Webhook support for external services

## Support and Community

### **Documentation**
- **Code Comments**: Inline documentation in source files
- **Build Scripts**: Automated build and flash processes
- **Wiring Diagrams**: Visual connection guides
- **Troubleshooting**: Common issues and solutions

### **Getting Help**
- **GitHub Issues**: Report bugs and request features
- **Community Forum**: Share projects and get help
- **Documentation**: Comprehensive setup and usage guides
- **Examples**: Sample applications and use cases

## License
This project is released under the Public Domain (CC0) license, allowing free use for any purpose.

---

**Note**: This system is designed for educational and personal use. Always follow proper electrical safety practices when working with relays and electrical systems.
