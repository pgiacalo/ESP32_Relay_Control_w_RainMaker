#!/bin/bash

# Dual Relay Controller Build Script
# This script builds and flashes the ESP32 dual relay controller firmware

# Source ESP-IDF environment
if [ -f ~/esp/esp-idf/export.sh ]; then
    source ~/esp/esp-idf/export.sh
    echo "Sourced ESP-IDF environment from ~/esp/esp-idf/export.sh"
elif [ -f ~/.espressif/esp-idf/export.sh ]; then
    source ~/.espressif/esp-idf/export.sh
    echo "Sourced ESP-IDF environment from ~/.espressif/esp-idf/export.sh"
else
    echo "Warning: ESP-IDF export.sh not found. Please ensure ESP-IDF environment is set up."
    echo "Common locations: ~/esp/esp-idf/export.sh or ~/.espressif/esp-idf/export.sh"
fi

# Function to show usage
show_usage() {
    echo "Usage: $0 [build|flash|monitor|flash-monitor|clean|menuconfig]"
    echo ""
    echo "Commands:"
    echo "  build         - Build the project only"
    echo "  flash         - Build and flash the firmware"
    echo "  monitor       - Monitor serial output"
    echo "  flash-monitor - Build, flash, and monitor (recommended)"
    echo "  clean         - Clean build artifacts"
    echo "  menuconfig    - Open configuration menu"
    echo ""
    echo "Examples:"
    echo "  $0 build         # Build only"
    echo "  $0 flash-monitor # Build, flash, and monitor (most common)"
    echo "  $0 clean         # Clean build"
}

# Set the RainMaker path if not already set
if [ -z "$RMAKER_PATH" ]; then
    export RMAKER_PATH=/Users/phil/esp/esp-rainmaker
    echo "Set RMAKER_PATH to $RMAKER_PATH"
fi

# Set default serial port for ESP32 (can be overridden with ESP32_PORT env var)
if [ -z "$ESP32_PORT" ]; then
    # Auto-detect ESP32 port (prefer usbserial over other devices)
    if [ -e "/dev/cu.usbserial-0001" ]; then
        export ESP32_PORT="/dev/cu.usbserial-0001"
    elif [ -e "/dev/cu.usbserial-0000" ]; then
        export ESP32_PORT="/dev/cu.usbserial-0000"
    else
        export ESP32_PORT="/dev/cu.usbserial-0001"  # Default fallback
    fi
    echo "Set ESP32_PORT to $ESP32_PORT"
fi

# Check if command is provided
if [ $# -eq 0 ]; then
    echo "No command specified. Building project..."
    COMMAND="build"
else
    COMMAND=$1
fi

# Execute command based on argument
case $COMMAND in
    "build")
        echo "Building Dual Relay Controller firmware..."
        idf.py build
        if [ $? -eq 0 ]; then
            echo "Build successful!"
        else
            echo "Build failed!"
            exit 1
        fi
        ;;
    "flash")
        echo "Building and flashing Dual Relay Controller firmware..."
        idf.py build flash
        if [ $? -eq 0 ]; then
            echo "Build and flash successful!"
        else
            echo "Build and flash failed!"
            exit 1
        fi
        ;;
    "monitor")
        echo "Starting serial monitor on $ESP32_PORT..."
        idf.py monitor -p $ESP32_PORT
        ;;
    "flash-monitor")
        echo "Building, flashing, and monitoring Dual Relay Controller firmware on $ESP32_PORT..."
        idf.py build flash monitor -p $ESP32_PORT
        ;;
    "clean")
        echo "Cleaning build artifacts..."
        idf.py fullclean
        echo "Clean completed!"
        ;;
    "menuconfig")
        echo "Opening configuration menu..."
        idf.py menuconfig
        ;;
    "help"|"-h"|"--help")
        show_usage
        ;;
    *)
        echo "Unknown command: $COMMAND"
        show_usage
        exit 1
        ;;
esac
