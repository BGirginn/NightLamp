# NightLamp

A smart, touch-controlled RGB night lamp project implemented using Arduino C++. This project features multiple color modes, automatic color cycling, and optional Bluetooth connectivity with music synchronization capabilities.

## Project Overview

NightLamp is an Arduino-based smart lighting system that transforms any space into a customizable ambient environment. The project offers three different implementations, each building upon the previous version with enhanced features:

### Features

- **Touch Control**: Simple touch sensor interface for easy color switching
- **Multiple Color Modes**: 12 predefined static colors plus dynamic color cycling
- **RGB LED Control**: Full spectrum color control using PWM
- **Bluetooth Connectivity**: A2DP audio sink for music synchronization (advanced version)
- **Music Sync Mode**: LED effects that respond to audio playback
- **Customizable**: Easy to modify colors, timing, and behavior

### Project Variants

1. **noColorCycle**: Basic version with 12 static color modes
2. **withColorCycle**: Enhanced version adding automatic color cycling mode
3. **MusicBluetoothButton**: Advanced version with Bluetooth and music synchronization

## Hardware Prerequisites

### Required Components

- **Microcontroller**: ESP32 or Arduino-compatible board with WiFi/Bluetooth capability
- **RGB LED**: Common anode RGB LED or LED strip
- **Touch Sensor**: Digital touch sensor module
- **Resistors**: Current limiting resistors for LED protection
- **Breadboard/PCB**: For circuit assembly
- **Power Supply**: 5V DC power supply (depending on LED requirements)

### Pin Connections

| Component | Pin | Description |
|-----------|-----|-------------|
| Touch Sensor | 13 | Digital input for touch detection |
| Red LED | 25 | PWM output for red channel |
| Green LED | 26 | PWM output for green channel |
| Blue LED | 27 | PWM output for blue channel |

## Software Prerequisites

### Development Environment

- **Arduino IDE** (version 1.8.0 or higher) or **PlatformIO**
- **ESP32 Board Package** (if using ESP32)
- **BluetoothA2DPSink Library** (for MusicBluetoothButton variant)

### Installation Steps

1. **Install Arduino IDE**
   ```
   Download from: https://www.arduino.cc/en/software
   ```

2. **Add ESP32 Board Support** (if using ESP32)
   - Open Arduino IDE
   - Go to File → Preferences
   - Add this URL to Additional Board Manager URLs:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Go to Tools → Board → Board Manager
   - Search for "ESP32" and install "ESP32 by Espressif Systems"

3. **Install Required Libraries**
   - For MusicBluetoothButton variant:
     - Go to Sketch → Include Library → Manage Libraries
     - Search for "ESP32-A2DP" and install the library by Phil Schatzmann

## Setup Instructions

### 1. Hardware Assembly

1. **Connect the RGB LED**:
   - Connect the common anode to 3.3V or 5V (depending on your LED)
   - Connect red cathode to pin 25 through a 220Ω resistor
   - Connect green cathode to pin 26 through a 220Ω resistor
   - Connect blue cathode to pin 27 through a 220Ω resistor

2. **Connect the Touch Sensor**:
   - VCC to 3.3V or 5V
   - GND to ground
   - Signal/Data to pin 13

3. **Power the System**:
   - Connect your microcontroller to USB or external power supply

### 2. Software Setup

1. **Clone or Download** this repository
2. **Choose Your Variant**:
   - `noColorCycle/noColorCycle.ino` - Basic functionality
   - `withColorCycle/withColorCycle.ino` - With color cycling
   - `MusicBluetoothButton/MusicBluetoothButton.ino` - Full featured

3. **Open in Arduino IDE**:
   - Open the `.ino` file for your chosen variant
   - Select your board type (Tools → Board)
   - Select the correct port (Tools → Port)

4. **Compile and Upload**:
   - Click the verify button (✓) to compile
   - Click the upload button (→) to flash to your device

### 3. Usage

#### Basic Operation
- **Single Touch**: Cycle through 12 color modes (13 in withColorCycle variant)
- **Color Modes**: White, Red, Green, Blue, Yellow, Cyan, Magenta, Pink, Orange, Purple, Light Blue, Gold Yellow
- **Color Cycle Mode**: Automatic rainbow color cycling (withColorCycle and MusicBluetoothButton variants)

#### Advanced Features (MusicBluetoothButton)
- **Long Press** (3+ seconds): Toggle music synchronization mode
- **Bluetooth Pairing**: Device appears as "SmartLEDSpeaker"
- **Music Sync**: LED effects respond to audio playback when connected

## Customization

### Adding New Colors

To add new color modes, modify the `setColor()` function:

```cpp
case 14: // Your custom color
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
    Serial.println("Custom Color");
    break;
```

### Adjusting Color Cycle Speed

Modify these parameters in `withColorCycle` or `MusicBluetoothButton`:

```cpp
const int hueStep = 2;        // Color change speed (1-10)
const long hueInterval = 15;  // Update interval in milliseconds
```

### Changing Touch Sensitivity

Adjust the debounce delay in the main loop:

```cpp
delay(300); // Increase for less sensitivity, decrease for more
```

## Troubleshooting

### Common Issues

1. **LED Not Lighting Up**:
   - Check wiring connections
   - Verify power supply voltage
   - Ensure current limiting resistors are present

2. **Touch Sensor Not Responding**:
   - Check sensor power connections
   - Verify pin 13 connection
   - Try adjusting debounce delay

3. **Bluetooth Not Connecting** (MusicBluetoothButton):
   - Ensure ESP32-A2DP library is installed
   - Check that ESP32 board is selected
   - Verify Bluetooth is enabled on source device

4. **Compilation Errors**:
   - Ensure correct board is selected
   - Install missing libraries
   - Check Arduino IDE version compatibility

## Contributing

We welcome contributions to improve NightLamp! Here's how you can help:

### Getting Started

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Make** your changes
4. **Test** your changes thoroughly
5. **Commit** your changes (`git commit -m 'Add amazing feature'`)
6. **Push** to the branch (`git push origin feature/amazing-feature`)
7. **Open** a Pull Request

### Contribution Guidelines

#### Code Style
- Follow existing code formatting and naming conventions
- Use descriptive variable and function names
- Add comments for complex logic
- Keep functions focused and modular

#### Testing
- Test your changes on actual hardware when possible
- Verify existing functionality is not broken
- Document any new hardware requirements

#### Documentation
- Update README.md for new features
- Add inline comments for complex algorithms
- Include wiring diagrams for new hardware configurations

### Types of Contributions

- **Bug Fixes**: Report and fix issues
- **New Features**: Add new lighting effects, control methods, or hardware support
- **Documentation**: Improve setup instructions, add tutorials, or create wiring diagrams
- **Optimization**: Improve performance or reduce memory usage
- **Hardware Support**: Add support for new sensors or LED types

### Reporting Issues

When reporting bugs or requesting features:

1. **Search existing issues** first
2. **Use the issue templates** when available
3. **Provide detailed information**:
   - Hardware configuration
   - Arduino IDE/PlatformIO version
   - Complete error messages
   - Steps to reproduce the issue

## License

This project is open source. Please check the repository for license details.

## Acknowledgments

- Arduino and ESP32 communities for excellent documentation
- Contributors who have helped improve this project
- Open source libraries that make this project possible

---

**Happy Building!** 🌟

For questions, suggestions, or support, please open an issue in this repository.