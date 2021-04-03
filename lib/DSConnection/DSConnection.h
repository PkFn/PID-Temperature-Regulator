#pragma once

class ds_sensor
{
    public:
    ds_sensor(int ds_pin);
    void setResolution(int resolution);
    void updateTemperature();
    float readTemperature(float ts_multiplier);
    private:
    int sensor_pin;
};