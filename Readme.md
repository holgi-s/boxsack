# BoxSack

## Hardware

* Arduino Nano
* WS2812B LED Strip  
* MPU6050 3-Axis Gyro & Accelerometer  

<img src="Hardware/BoxSack.png" width="800" height="532" />

## Software

* Wire Library  
Used to read the acceleration from the MPU 6050 accelerometer

* FastLED Library  
Used to display the number of hits, or total power of all hits.  

* HighPass Filter  
Used to filter out gravity and slow swining of the boxsack

* LowPass Filter  
Used to smoothen the display

## Build Status  

Autmatic build using **arduino-cli**.

**CircleCi:**
<img src="https://circleci.com/bb/holgis/boxsack.svg?style=svg&circle-token=d9e0a768c426e7b83bd08fffcc4e09e1c06ba707" />

