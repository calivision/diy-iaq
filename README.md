# What's Your Air Quality? | Build Designs for Indoor Air Quality Monitors 
## Make Your Own IAQ Monitor & Save!

### What is this project?
DIY IAQ brings together code, hardware, and enclosure files to get started with environmental sensors for indoor air quality. <br> 
This project has reviewed documentation from Bosch for 68x sensors and includes code as permitted by license. <br>
I am in the process of asking Bosch to permit me to include the BSEC Integration Guide in this repo. The Release Notes and BSEC2 Binary Size Information files are included in the repository for now.

## Build 1 
### Assemble Components 

<br>
<br>

## Recommended Components

## MCUs
### XIAO SAMD21 (Formerly Seeduino) 
[The XIAO SAMD21 CPU is the ARM® Cortex®-M0+ 32bit 48MHz microcontroller(SAMD21G18) with 256KB Flash,32KB SRAM](https://wiki.seeedstudio.com/Seeeduino-XIAO/)

## Sensors
### BME680 - Sensor of Mystery
The BME68x sensor series developed by Bosch is widely manufactured and senses Temperature, Humidity, TVOC levels to calculate an indoor air quality metric (IAQ) and CO2 level. 

### DFRobot SEN0233
This sensor measures Particulate Matter. I have not gotten any data from the sensor as of 03/28/2025 and am troubleshooting the issue.

## Displays
This project uses a widely available 0.96" 128x64 Pixel OLED screen (Blue/Yellow variant) and the Adafruit SSD1306 library 

## Enclosures
There is a basic enclosure for a half breadboard that can serve as a basis for further development

## PCBs
### Build 1 (March 2025)
The project uses a half breadboard to connect XIAO SAMD21, OLED Dispaly 12864, BME680 sensor.
### Build 2 (est May 2025)
Custom PCB including SAMD21, OLED Dispaly 12864, BME68x sensor
### Build 3 (est July 2025)
Build 2 plus audio features
