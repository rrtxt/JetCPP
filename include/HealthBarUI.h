#pragma once

#include "Common.h"

class HealthBarUI {
public:
    int maxHealth;
    HealthBarUI(int maxHealth);
    void Draw(int currentHealth);
};