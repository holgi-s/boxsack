#include <Wire.h>
#include "mems.h"
#include <math.h>


int8_t AFS_SEL = 0;
float AFS_SEL_LSB = 16384.0f;

const int MPU=0x68; 

float alpha = 0.1;

float EMA_X_a = alpha;    //initialization of EMA alpha
float EMA_X_S = 0.0;        //initialization of EMA S 

float EMA_Y_a = alpha;    //initialization of EMA alpha
float EMA_Y_S = 0.0;        //initialization of EMA S

float EMA_Z_a = alpha;    //initialization of EMA alpha
float EMA_Z_S = 0.0;        //initialization of EMA S



void setup_MPU_Power(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
}


void setup_AFS_divider(int8_t afs_sel){
  switch (afs_sel){
    default:
    case 0:
      AFS_SEL_LSB = 16384.0f;
      break;
    case 1:
      AFS_SEL_LSB = 8192.0f;
      break;
    case 2:
      AFS_SEL_LSB = 4096.0f;
      break;
    case 3:
      AFS_SEL_LSB = 2048.0f;
      break;
  }
}

void setup_MPU_Acceleration(int8_t afs_sel){
  AFS_SEL = afs_sel;
  setup_AFS_divider(afs_sel);

  Wire.beginTransmission(MPU);
  Wire.write(0x1C); 
  Wire.write(afs_sel<<3);
  Wire.endTransmission(true);
}

void read_MPU_Acceleration(float& fax, float& fay, float& faz){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);  
  int16_t xa=Wire.read()<<8|Wire.read();    
  int16_t ya=Wire.read()<<8|Wire.read();  
  int16_t za=Wire.read()<<8|Wire.read();  

  fax = (float)xa/AFS_SEL_LSB;
  fay = (float)ya/AFS_SEL_LSB;
  faz = (float)za/AFS_SEL_LSB;
}

void high_pass_filter_xyz(float& fax, float& fay, float& faz){
  EMA_X_S = (EMA_X_a*fax) + ((1-EMA_X_a)*EMA_X_S);  //run the EMA
  fax = fax - EMA_X_S;    
 
  EMA_Y_S = (EMA_Y_a*fay) + ((1-EMA_Y_a)*EMA_Y_S);  //run the EMA
  fay = fay - EMA_Y_S;   

  EMA_Z_S = (EMA_Z_a*faz) + ((1-EMA_Z_a)*EMA_Z_S);  //run the EMA
  faz = faz - EMA_Z_S;   
}

float high_pass_filter(float filtered, float weight, float actual) {
  filtered = (weight*actual) + ((1-weight)*filtered);
  return actual - filtered;
}

float low_pass_filter(float filtered, float weight, float actual) {
  return (weight*actual) + ((1-weight)*filtered);
}

float magnitude(float x, float y, float z){
  return sqrt(x*x + y*y + z*z);
}