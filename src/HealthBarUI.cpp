#include "HealthBarUI.h"

HealthBarUI::HealthBarUI(int maxHealth) : maxHealth(maxHealth) {};
void HealthBarUI::Draw(int currentHealth){
    for (int i = 0; i < maxHealth; i++){
        if (i < currentHealth){
            DrawRectangle(20 + i * 35, 20, 30, 30, BLACK);
        } else {
            DrawRectangle(20 + i * 35, 20, 30, 30, GRAY);
        }
    }
};