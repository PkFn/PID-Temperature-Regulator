#include <OneWire.h>
#include "myPID.h"
#include "DSConnection.h"

#define heat_pin 4
#define heat_temperature 35
#define ts_pin 5
#define ts_res 10
#define ts_mult 0.0625
#define ts_barrel_capacity 60
#define upd_interval 1000

OneWire ds(ts_pin);
Pid heat_reg(50, 0, 1023);
ds_sensor ds_connect(ts_pin);

unsigned int upd_last = 0;
bool output_block = false;
float ts_barrel = 0, ts_temp_average = 0;

float getTemperature();
void printTime();

void setup(){
  heat_reg.setPoint(heat_temperature);
  Serial.begin(9600);
  Serial.print("\n\n\nDevice...");
  if(ds.reset()==1) Serial.println("OK"); else Serial.println("ERROR");
  ds_connect.setResolution(ts_res);
  ds_connect.updateTemperature();
}

void loop(){
  if(millis() - upd_last > upd_interval)
  {
    upd_last = millis();
    printTime();
    if(!output_block){
      float current_temp = getTemperature();

      ts_barrel += current_temp;
      ts_temp_average = ts_barrel / ts_barrel_capacity;
      ts_barrel -= ts_temp_average;

      ds_connect.updateTemperature();
      heat_reg.calculate(current_temp);
      analogWrite(heat_pin, heat_reg.pid_output);
      Serial.print("curT: ");
      Serial.print(current_temp);
      Serial.print("°C\tavT: ");
      Serial.print(ts_temp_average);
      Serial.print("°C\theat_reg_output: ");
      Serial.println(heat_reg.pid_output);
    }
    else{
      Serial.println("Sensor error");
      analogWrite(heat_pin, 0);
    }
  }
}

float getTemperature(){
  static float last_good_temp = 0;
  static int errors = 0;
  float temp = ds_connect.readTemperature(ts_mult);
  if(temp == -127)
  {
    errors++;
    Serial.print("Sensor error! (");
    Serial.print(errors);
    Serial.print("/2)\t");
    if(errors >= 2) output_block = true;
    return last_good_temp;
  }
  errors = 0;
  return temp;
}

void printTime()
{
  int time = upd_last / 1000;
  Serial.print("[");
  Serial.print(time/3600);
  Serial.print(":");
  Serial.print(time%3600/60);
  Serial.print(":");
  Serial.print(time%60);
  Serial.print("] ");
}