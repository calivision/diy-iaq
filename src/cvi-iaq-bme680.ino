// SPDX-FileCopyrightText: 2020 Limor Fried for Adafruit Industries
// SPDX-FileCopyrightText: 2020 Kevin Townsend for Adafruit Industries
//
// SPDX-License-Identifier: MIT

/***************************************************************************
  This is a library for the BME68X gas, humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME68X Breakout
  ----> http://www.adafruit.com/products/3660

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution

---------- California Vision Development - Begin Sep 2024 --------- 
  David Anderson modified this code to the current state starting 09/26/24
  
  Hardcoded values using #define should be changed to const or constexpr - 03/25
  Code is being uploaded as-is, users should be aware that despite this file saying
  MIT License, the bsec.h file and other Bosch code has BSD-3-Clause License
 ***************************************************************************/

#include <bsec.h>
#include <Adafruit_SSD1306.h>
#include "bsec.h"

Adafruit_SSD1306 display = Adafruit_SSD1306();

#define SEALEVELPRESSURE_HPA (1005.7)

#define FARFACTOR (1.8)
#define FAROFFSET (32)

#define LED_BUILTIN 2

// Helper functions declarations
void checkIaqSensorStatus(void);
void errLeds(void);

// Create an object of the class Bsec
Bsec iaqSensor;

String output;

// Entry point for the example
void setup(void)
{
  /* Initializes the Serial communication */
  Serial.begin(115200);
  Wire.begin(0,2);
  delay(1000);

// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  pinMode(LED_BUILTIN, OUTPUT);

  iaqSensor.begin(BME68X_I2C_ADDR_LOW, Wire);
  output = "\nBSEC library version " + String(iaqSensor.version.major) + "." + String(iaqSensor.version.minor) + "." + String(iaqSensor.version.major_bugfix) + "." + String(iaqSensor.version.minor_bugfix);
  Serial.println(output);
  checkIaqSensorStatus();
  bsec_virtual_sensor_t sensorList[10] = {
    BSEC_OUTPUT_RAW_TEMPERATURE,
    BSEC_OUTPUT_RAW_PRESSURE,
    BSEC_OUTPUT_RAW_HUMIDITY,
    BSEC_OUTPUT_RAW_GAS,
    BSEC_OUTPUT_IAQ,
    BSEC_OUTPUT_STATIC_IAQ,
    BSEC_OUTPUT_CO2_EQUIVALENT,
    BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
  };

  iaqSensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
  checkIaqSensorStatus();
  // Print the header
  output = "Timestamp [ms], raw temperature [°C], pressure [hPa], raw relative humidity [%], gas [Ohm], IAQ, IAQ accuracy, temperature [°C], relative humidity [%], Static IAQ, CO2 equivalent, breath VOC equivalent";
  Serial.println(output);
}

void loop() {
  display.setCursor(0,0);
  display.clearDisplay();

  unsigned long time_trigger = millis();
  if (! iaqSensor.run()) { // If no data is available
    checkIaqSensorStatus();
    return;
  }
  
  output = String(time_trigger);
  output += ", " + String(iaqSensor.rawTemperature);
  output += ", " + String(iaqSensor.pressure);
  output += ", " + String(iaqSensor.rawHumidity);
  output += ", " + String(iaqSensor.gasResistance);
  output += ", " + String(iaqSensor.iaq);
  output += ", " + String(iaqSensor.iaqAccuracy);
  output += ", " + String(iaqSensor.temperature);
  output += ", " + String(iaqSensor.humidity);
  output += ", " + String(iaqSensor.staticIaq);
  output += ", " + String(iaqSensor.co2Equivalent);
  output += ", " + String(iaqSensor.breathVocEquivalent);
  Serial.println(output);

  Serial.print("XIAO BME680 OLED Demo");
  Serial.print("by California Vision");
  display.println("XIAO BME680 OLED Demo"); 
  display.println("by California Vision");

  Serial.print("Temperature = "); Serial.print(iaqSensor.temperature  * FARFACTOR + FAROFFSET); Serial.println(" *F");
  display.print("Temperature: "); display.print(iaqSensor.temperature  * FARFACTOR + FAROFFSET); display.println("*F");

  Serial.print("Pressure = "); Serial.print(iaqSensor.pressure / 100.0); Serial.println(" hPa");
  display.print("Pressure: "); display.print(iaqSensor.pressure / 100); display.println("hPa");

  Serial.print("Humidity = "); Serial.print(iaqSensor.humidity); Serial.println(" %");
  display.print("Humidity: "); display.print(iaqSensor.humidity); display.println("%");

  Serial.print("IAQ = "); Serial.print(iaqSensor.staticIaq); Serial.print("");Serial.print(" IAQ Accuracy: "); Serial.print(iaqSensor.iaqAccuracy); Serial.println("");
  display.print("IAQ: "); display.print(iaqSensor.staticIaq); display.print("");display.print(" IAQ Acc: "); display.print(iaqSensor.iaqAccuracy); display.println("");
  
  Serial.print("CO2 equiv = "); Serial.print(iaqSensor.co2Equivalent); Serial.println(" ppm");
  display.print("CO2eq: "); display.print(iaqSensor.co2Equivalent); display.println("ppm");
  
  Serial.print("Breath VOC = "); Serial.print(iaqSensor.breathVocEquivalent); Serial.println(" ppm");
  display.print("VOC: "); display.print( iaqSensor.breathVocEquivalent); display.println("ppm");
  
  Serial.println();
  display.display();
  delay(2000);
}


// Helper function definitions
void checkIaqSensorStatus(void)
{
  if (iaqSensor.bsecStatus != BSEC_OK) {
    if (iaqSensor.bsecStatus < BSEC_OK) {
      output = "BSEC error code : " + String(iaqSensor.bsecStatus);
      Serial.println(output);
      display.setCursor(0,0);
      display.println(output);
      display.display();
      for (;;)  delay(10);
    } else {
      output = "BSEC warning code : " + String(iaqSensor.bsecStatus);
      Serial.println(output);
    }
  }

  if (iaqSensor.bme68xStatus != BME68X_OK) {
    if (iaqSensor.bme68xStatus < BME68X_OK) {
      output = "BME68X error code : " + String(iaqSensor.bme68xStatus);
      Serial.println(output);
      display.setCursor(0,0);
      display.println(output);
      display.display();
      for (;;)  delay(10);
    } else {
      output = "BME68X warning code : " + String(iaqSensor.bme68xStatus);
      Serial.println(output);
    }
  }
}

void errLeds(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}