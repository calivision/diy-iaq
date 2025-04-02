# What's Your Air Quality? 
## DIY-IAQ | Indoor Air Quality Monitoring System | Make Your Own IAQ Monitor!

### What is this project?
DIY IAQ brings together code, hardware, and enclosure files to get started with environmental sensors for indoor air quality. 
This project has reviewed documentation from Bosch for 68x sensors and includes code as permitted by license.
Release Notes and BSEC2 Binary Size Information files are included in the repository for now.

[View this project on Hackster.io with pictures and video](https://www.hackster.io/david-anderson3/diy-iaq-indoor-air-quality-monitor-xiao-samd21-bme680-e9f8e3) <br>
<br>
[DIY-IAQ YouTube Short Video | Shows IAQ Accuracy Metric Change](https://youtube.com/shorts/EIIJA0CVomI?si=GgLcWr9QqU5e79Y_)

## Build 1 
### Assemble Components 

The first build of the DIY-IAQ monitor uses a half breadboard to hold the XIAO SAMD21 MCU, a BME680 sensor, and a 0.96" 128x64 OLED display.  Connect A4/A5 pins on the XIAO to SDA/SCL pins on the BME680 as described above. Connect the SDA/SCL pins from the display on the breadboard directly behind the BME680's SDA/SCL pins. 

Connect the GND and 3v3 pins on the XIAO to the breadboard rail. Connect the VCC and GND pins from the display and sensor to the rail so they are powered by the XIAO. Plug a USB-C cable into the XIAO and then into a USB port or powerbank. Upon initial use the BME680 calibrates itself by heating the sensor for 48-72 hours. Post-calibration the 'iaqAccuracy' metric moves from '0' to '1' approximately 5 minutes after the XIAO is plugged in to a source of power.

## Recommended Components

## MCU
### XIAO SAMD21 (Formerly Seeduino) 
[The XIAO SAMD21 CPU is the ARM® Cortex®-M0+ 32bit 48MHz microcontroller(SAMD21G18) with 256KB Flash,32KB SRAM](https://wiki.seeedstudio.com/Seeeduino-XIAO/)

## Sensor
### BME680 - BME680 - TVOCs & Barometric Pressure
The BME68x sensor series developed by Bosch is widely manufactured and senses Temperature, Humidity, TVOC levels to calculate an indoor air quality metric (IAQ) and CO2 level. 

## Display
This project uses a widely available 0.96" 128x64 Pixel OLED screen (Blue/Yellow variant) with the Adafruit_SSD1306 library. 

## Enclosures
There is a basic enclosure for a half breadboard that can serve as a basis for further development.

## Development Roadmap  - in progress
### Build 1 (March 2025)
XIAO SAMD21, BME680 sensor, 0.96" 128x64 OLED Display, on half-breadboard.
### Build 2 (est May 2025)
Custom PCB including Build 1 components.
### Build 3 (est July 2025)
Build 2 plus audio features.
