#pragma once

#include "Common.h"

class TimeScale {
private:
    static int timescale;

public:
    TimeScale(int initial = 1);
    static int Get();
    static void Set(int value);
};
