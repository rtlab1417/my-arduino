/*
 * source: https://forum.arduino.cc/index.php?topic=610345.0
 * refer to my code: adxl345_I2C_1.ino
 * this code is for addressging 2 units of ADXL345 over i2c.
 * unit 1 -> SD0 is shorted to GND - address is 0x53
 * unit 2 -> SD0 is shorted to VCC - address is 0x1D
 * 
 */

#include<Wire.h>

#define accel_module (0x1D)         // SDO-> Vcc
#define accel_module2 (0x53)       // SDO-> GND

byte values[6];
byte values2[6];
char output[512];
char output2[512];

void getAccelration(int accelSensor, int cal)
{
  int xyzregister = 0x32;
  //int x, y, z;
  float x, y, z;

  Wire.beginTransmission(accelSensor);
  Wire.write(0x2D);
  Wire.write(0); 
  Wire.endTransmission();
  
  Wire.beginTransmission(accelSensor);
  Wire.write(0x2D);
  Wire.write(16);
  Wire.endTransmission();
  
  Wire.beginTransmission(accelSensor);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();

  Wire.beginTransmission(accelSensor);
  Wire.write(xyzregister);
  Wire.endTransmission();

  Wire.beginTransmission(accelSensor);
  Wire.requestFrom(accelSensor, 6);

  int i = 0;
  while(Wire.available())
  {
    values[i] = Wire.read();
    i++;
    }
  Wire.endTransmission();

  x = (((int)values[1]) << 8) | values[0];
  x = x/256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  y = (((int)values[3])<< 8) | values[2];
  y = y/256;
  z = (((int)values[5]) << 8) | values[4];
  z = z/256;
  //sprintf(output, "%d",z); //-cal);
  //Serial.print(output);
  Serial.print(x);
  Serial.print("  "); 
  Serial.print(y);
  Serial.print("  ");
  Serial.print(z);
  Serial.print("  ");
  }

 
void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  getAccelration(accel_module, 205); // ********accel 0x1D*********//
  Serial.print("    From2: ");
  getAccelration(accel_module2, 28);  //*******accel 0x53********//

  Serial.println(); 
 
  delay(200);
}
