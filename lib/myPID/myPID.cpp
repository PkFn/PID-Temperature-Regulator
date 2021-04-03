#include "myPID.h"

Pid::Pid(float _k_prop, int _lim_min, int _lim_max)
{
    k_prop = _k_prop;
    lim_min = _lim_min;
    lim_max = _lim_max;
}

void Pid::setPoint(float point)
{
    temp_point = point;
}

void Pid::calculate(float temperature)
{
    float res = k_prop * (temp_point - temperature);
    if(res > lim_max) res = lim_max;
    else if(res < lim_min) res = lim_min;
    pid_output = res;
}