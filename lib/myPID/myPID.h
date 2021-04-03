#pragma once

class Pid
{
    public:
    Pid(float k_prop, int lim_min, int lim_max);
    void calculate(float temperature);
    void setPoint(float point);
    int pid_output;
    private:
    float k_prop;
    int lim_min, lim_max;
    float temp_point;
};