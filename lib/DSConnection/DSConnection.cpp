#include "DSConnection.h"
#include "OneWire.h"

ds_sensor::ds_sensor(int pin)
{
    sensor_pin = pin;
}

void ds_sensor::setResolution(int res)
{
    int command = 0x3F;
    OneWire ds(sensor_pin);
    switch(res)
    {
        case 9:
        command = 0x1F;
        break;
        case 10:
        command = 0x3F;
        break;
        case 11:
        command = 0x5F;
        break;
        case 12:
        command = 0x7F;
        break;
    }
    ds.reset();
    ds.write(0xCC);
    ds.write(0x4E); ds.write(0); ds.write(0); ds.write(command);
    ds.write(0x48);
    ds.reset();
}

void ds_sensor::updateTemperature()
{
    OneWire ds(sensor_pin);
    ds.reset();
    ds.write(0xCC);
    ds.write(0x44);
}

float ds_sensor::readTemperature(float ts_mult)
{
    OneWire ds(sensor_pin);
    byte data[2];
    ds.reset();
    ds.write(0xCC); 
    ds.write(0xBE);
    data[0] = ds.read();
    data[1] = ds.read();
    return ((data[1] << 8) | data[0]) * ts_mult;
}