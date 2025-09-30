#include "TimeScale.h"

int TimeScale::timescale = 1;

TimeScale::TimeScale(int initial) { 
    timescale = initial; 
}

int TimeScale::Get() { 
    return timescale; 
}

void TimeScale::Set(int value) { 
    if(value < 0) value = 0;
    timescale = value;
}
