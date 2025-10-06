#include "GameSettingUIComponent.h"

GameSettingUIComponent::GameSettingUIComponent(GameState* gameState, EventSystem* eventSystem) 
    : gameState(gameState), eventSystem(eventSystem), selectedSettingIndex(0) {
    
    // Initialize visual properties
    titleFontSize = 48;
    settingFontSize = 24;
    settingSpacing = 80;
    titleColor = BLACK;
    selectedColor = YELLOW;
    normalColor = BLACK;
    valueColor = GREEN;
    backgroundColor = WHITE;
    
    // UI dimensions
    sliderWidth = 300;
    sliderHeight = 20;
    buttonWidth = 200;
    buttonHeight = 40;
    
    InitializeSettings();
}

void GameSettingUIComponent::InitializeSettings() {
    settings.clear();
    
    // Master Volume
    settings.push_back({
        "Master Volume",
        SettingType::VOLUME,
        0.7f,  // current value
        0.0f,  // min
        1.0f,  // max
        {},    // no options for slider
        0      // selectedOption (unused for sliders)
    });
    
    // Difficulty
    settings.push_back({
        "Difficulty",
        SettingType::DIFFICULTY,
        1.0f,  // current value (index)
        0.0f,  // min
        2.0f,  // max
        {"Easy", "Normal", "Hard"},  // options
        1      // selectedOption (Normal)
    });
    
    // Controls
    settings.push_back({
        "Control Scheme",
        SettingType::CONTROLS,
        0.0f,  // current value (index)
        0.0f,  // min
        1.0f,  // max
        {"WASD", "Arrow Keys"},  // options
        0      // selectedOption (WASD)
    });
    
    // Graphics Quality
    settings.push_back({
        "Graphics Quality",
        SettingType::GRAPHICS,
        1.0f,  // current value (index)
        0.0f,  // min
        2.0f,  // max
        {"Low", "Medium", "High"},  // options
        1      // selectedOption (Medium)
    });
}

void GameSettingUIComponent::Draw() {
    if (!isVisible || !isEnabled) return;
    
    // Draw semi-transparent background
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
    
    DrawTitle();
    DrawSettings();
    DrawBackButton();
}

void GameSettingUIComponent::Update() {
    if (!isEnabled) return;
    
    HandleInput();
}

void GameSettingUIComponent::DrawTitle() {
    const char* title = "GAME SETTINGS";
    int titleWidth = MeasureText(title, titleFontSize);
    titlePosition.x = GetScreenWidth() / 2 - titleWidth / 2;
    titlePosition.y = 80;
    
    DrawText(title, titlePosition.x, titlePosition.y, titleFontSize, titleColor);
}

void GameSettingUIComponent::DrawSettings() {
    settingsStartPosition.x = GetScreenWidth() / 2 - 200;
    settingsStartPosition.y = titlePosition.y + titleFontSize + 60;
    
    for (int i = 0; i < settings.size(); i++) {
        Vector2 settingPos = {
            settingsStartPosition.x,
            settingsStartPosition.y + i * settingSpacing
        };
        
        // Draw setting label
        Color labelColor = (i == selectedSettingIndex) ? selectedColor : normalColor;
        DrawText(settings[i].label.c_str(), settingPos.x, settingPos.y, settingFontSize, labelColor);
        
        // Draw setting control based on type
        Vector2 controlPos = {settingPos.x, settingPos.y + 30};
        
        if (settings[i].type == SettingType::VOLUME) {
            DrawSlider(settings[i], controlPos);
        } else {
            DrawDropdown(settings[i], controlPos);
        }
    }
}

void GameSettingUIComponent::DrawSlider(const SettingItem& setting, Vector2 position) {
    Rectangle sliderRect = GetSliderRect(position);
    Rectangle handleRect = GetSliderHandleRect(position, setting.value, setting.minValue, setting.maxValue);
    
    // Draw slider track
    DrawRectangleRec(sliderRect, DARKGRAY);
    DrawRectangleLinesEx(sliderRect, 2, WHITE);
    
    // Draw slider handle
    DrawRectangleRec(handleRect, valueColor);
    DrawRectangleLinesEx(handleRect, 2, WHITE);
    
    // Draw value text
    const char* valueText = TextFormat("%.0f%%", setting.value * 100);
    DrawText(valueText, position.x + sliderWidth + 20, position.y, settingFontSize, valueColor);
}

void GameSettingUIComponent::DrawDropdown(const SettingItem& setting, Vector2 position) {
    Rectangle dropdownRect = {position.x, position.y, sliderWidth, sliderHeight};
    
    // Draw dropdown background
    DrawRectangleRec(dropdownRect, DARKGRAY);
    DrawRectangleLinesEx(dropdownRect, 2, WHITE);
    
    // Draw current selection
    if (setting.selectedOption < setting.options.size()) {
        const char* selectedText = setting.options[setting.selectedOption].c_str();
        DrawText(selectedText, position.x + 10, position.y + 2, settingFontSize - 4, valueColor);
    }
    
    // Draw dropdown arrow
    DrawText("v", position.x + sliderWidth - 25, position.y + 2, settingFontSize - 4, WHITE);
}

void GameSettingUIComponent::DrawBackButton() {
    Rectangle backButtonRect = {
        (float)(GetScreenWidth() / 2 - buttonWidth / 2),
        (float)(GetScreenHeight() - 100),
        buttonWidth,
        buttonHeight
    };
    
    Color buttonColor = DARKGRAY;
    if (CheckCollisionPointRec(GetMousePosition(), backButtonRect)) {
        buttonColor = GRAY;
    }
    
    DrawRectangleRec(backButtonRect, buttonColor);
    DrawRectangleLinesEx(backButtonRect, 2, WHITE);
    
    const char* backText = "BACK TO MENU";
    int textWidth = MeasureText(backText, 20);
    DrawText(backText, 
        backButtonRect.x + backButtonRect.width / 2 - textWidth / 2,
        backButtonRect.y + backButtonRect.height / 2 - 10,
        20, WHITE);
}

void GameSettingUIComponent::HandleInput() {
    // Navigate settings with UP/DOWN
    if (IsKeyPressed(KEY_UP)) {
        selectedSettingIndex--;
        if (selectedSettingIndex < 0) {
            selectedSettingIndex = settings.size() - 1;
        }
    }
    
    if (IsKeyPressed(KEY_DOWN)) {
        selectedSettingIndex++;
        if (selectedSettingIndex >= settings.size()) {
            selectedSettingIndex = 0;
        }
    }
    
    // Modify selected setting with LEFT/RIGHT
    if (IsKeyPressed(KEY_LEFT)) {
        UpdateSettingValue(selectedSettingIndex, -0.1f);
    }
    
    if (IsKeyPressed(KEY_RIGHT)) {
        UpdateSettingValue(selectedSettingIndex, 0.1f);
    }
    
    // Mouse interaction for sliders
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        
        for (int i = 0; i < settings.size(); i++) {
            Vector2 controlPos = {
                settingsStartPosition.x,
                settingsStartPosition.y + i * settingSpacing + 30
            };
            
            if (settings[i].type == SettingType::VOLUME && IsMouseOverSlider(controlPos)) {
                float newValue = GetSliderValueFromMouse(controlPos, settings[i].minValue, settings[i].maxValue);
                settings[i].value = Clamp(newValue, settings[i].minValue, settings[i].maxValue);
            }
        }
    }
    
    // Handle back button
    Rectangle backButtonRect = {
        (float)(GetScreenWidth() / 2 - buttonWidth / 2),
        (float)(GetScreenHeight() - 100),
        buttonWidth,
        buttonHeight
    };
    
    if (IsKeyPressed(KEY_ESCAPE) || 
        (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), backButtonRect))) {
        ApplySettings();
        eventSystem->Emit("ChangeToMainMenu");
    }
}

void GameSettingUIComponent::UpdateSettingValue(int settingIndex, float delta) {
    if (settingIndex < 0 || settingIndex >= settings.size()) return;
    
    SettingItem& setting = settings[settingIndex];
    
    if (setting.type == SettingType::VOLUME) {
        setting.value = Clamp(setting.value + delta, setting.minValue, setting.maxValue);
    } else {
        // For dropdown settings, change selection
        if (delta > 0) {
            setting.selectedOption++;
            if (setting.selectedOption >= setting.options.size()) {
                setting.selectedOption = 0;
            }
        } else {
            setting.selectedOption--;
            if (setting.selectedOption < 0) {
                setting.selectedOption = setting.options.size() - 1;
            }
        }
    }
}

void GameSettingUIComponent::ApplySettings() {
    // Apply settings to game state or save to file
    std::cout << "Applying settings:" << std::endl;
    for (const auto& setting : settings) {
        if (setting.type == SettingType::VOLUME) {
            std::cout << "  " << setting.label << ": " << (setting.value * 100) << "%" << std::endl;
        } else {
            std::cout << "  " << setting.label << ": " << setting.options[setting.selectedOption] << std::endl;
        }
    }
}

// Helper methods
Rectangle GameSettingUIComponent::GetSliderRect(Vector2 position) {
    return {position.x, position.y, sliderWidth, sliderHeight};
}

Rectangle GameSettingUIComponent::GetSliderHandleRect(Vector2 position, float value, float minVal, float maxVal) {
    float normalizedValue = (value - minVal) / (maxVal - minVal);
    float handleX = position.x + normalizedValue * (sliderWidth - 20);
    return {handleX, position.y - 2, 20, sliderHeight + 4};
}

bool GameSettingUIComponent::IsMouseOverSlider(Vector2 position) {
    Rectangle sliderRect = GetSliderRect(position);
    return CheckCollisionPointRec(GetMousePosition(), sliderRect);
}

float GameSettingUIComponent::GetSliderValueFromMouse(Vector2 position, float minVal, float maxVal) {
    Vector2 mousePos = GetMousePosition();
    float relativeX = mousePos.x - position.x;
    float normalizedValue = Clamp(relativeX / sliderWidth, 0.0f, 1.0f);
    return minVal + normalizedValue * (maxVal - minVal);
}
