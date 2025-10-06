#pragma once

#include "UIComponent.h"
#include "EventSystem.h"

enum class SettingType {
    VOLUME,
    DIFFICULTY,
    CONTROLS,
    GRAPHICS
};

struct SettingItem {
    std::string label;
    SettingType type;
    float value;
    float minValue;
    float maxValue;
    std::vector<std::string> options; // For dropdown-style settings
    int selectedOption;
};

class GameSettingUIComponent : public UIComponent {
public:
    GameSettingUIComponent(GameState* gameState, EventSystem* eventSystem);
    
    void Draw() override;
    void Update() override;

private:
    GameState* gameState;
    EventSystem* eventSystem;
    
    // UI state
    int selectedSettingIndex;
    
    // Setting categories for navigation
    enum SettingCategory {
        VOLUME = 0,
        DIFFICULTY = 1,
        CONTROLS = 2,
        GRAPHICS = 3,
        SETTING_COUNT = 4
    };
    
    // Visual properties
    Vector2 titlePosition;
    Vector2 settingsStartPosition;
    int titleFontSize;
    int settingFontSize;
    int settingSpacing;
    Color titleColor;
    Color selectedColor;
    Color normalColor;
    Color valueColor;
    Color backgroundColor;
    
    // UI dimensions
    float sliderWidth;
    float sliderHeight;
    float buttonWidth;
    float buttonHeight;
    
    // Methods
    void HandleInput();
    void DrawTitle();
    void DrawSettings();
    void DrawVolumeSlider(Vector2 position);
    void DrawDifficultyDropdown(Vector2 position);
    void DrawControlsDropdown(Vector2 position);
    void DrawGraphicsDropdown(Vector2 position);
    void DrawBackButton();
    void UpdateSelectedSetting(float delta);
    void ApplySettings();
    void ResetToDefaults();
    
    // Helper methods
    Rectangle GetSliderRect(Vector2 position);
    Rectangle GetSliderHandleRect(Vector2 position, float value, float minVal, float maxVal);
    bool IsMouseOverSlider(Vector2 position);
    float GetSliderValueFromMouse(Vector2 position, float minVal, float maxVal);
};
