#include "mems.h"
#include "led.h"

const float factor_up = 1.0f;
const float factor_down = 0.5f;
const float factor_lp  = 0.2f; 

void setup() {

  Serial.begin(9600);

  setup_MPU_Power();
  setup_MPU_Acceleration(AFS_SEL_2G);

  setup_LED();
}

long lastHit = 0;

float process(float height, float magnitude) {
  long now = millis();
  if(magnitude > 1.5f) { 
    lastHit = now;
    
    height += factor_up;
    if(height >= (float)NUM_LEDS) {
      height = (float)NUM_LEDS-1;
    }
  } else {
    if(now - lastHit > 2000) {
      height -= factor_down;
      if ( height < 0) {
        height = 0.0f;
      }
    }
  }

  return height;
}

float process2(float height, float magnitude) {
  
  if(magnitude > 1.0f) { 

    if(magnitude > 2) {
      height += magnitude * factor_up;
      if(height >= (float)NUM_LEDS) {
        height = (float)NUM_LEDS-1;
      }
    } 

  } else {
    height -= factor_down;
    if ( height < 0) {
      height = 0.0f;
    }
  }

  return height;
}

float height = 0;
float lp_height = 0;

float accelX = 0.0;
float accelY = 0.0;
float accelZ = 0.0;

void loop() {

  read_MPU_Acceleration(accelX, accelY, accelZ);
  high_pass_filter_xyz(accelX, accelY, accelZ);
  float mag = magnitude(accelX, accelY, accelZ);  

  height = process(height, mag);

  lp_height = low_pass_filter(lp_height, factor_lp, height);

  Serial.print("M= "); Serial.print(mag);
  Serial.print(", H= "); Serial.print(height);
  Serial.print(", LP= "); Serial.println(lp_height);

  display_LED(lp_height);
  delay(10);
}
