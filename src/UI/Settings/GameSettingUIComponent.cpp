#include "GameSettingUIComponent.h"

GameSettingUIComponent::GameSettingUIComponent(GameState* gameState, EventSystem* eventSystem) 
    : gameState(gameState), eventSystem(eventSystem), selectedSettingIndex(0) {
    
    // Initialize visual properties
    titleFontSize = 48;
    settingFontSize = 24;
    settingSpacing = 80;
    titleColor = BLACK;
    selectedColor = GREEN;
    normalColor = BLACK;
    valueColor = GREEN;
    backgroundColor = WHITE;
    
    // UI dimensions
    sliderWidth = 300;
    sliderHeight = 20;
    buttonWidth = 200;
    buttonHeight = 40;
}

// Removed InitializeSettings - no longer needed!
// We work directly with gameState->settings now

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
    
    const char* settingLabels[] = {"Master Volume", "Difficulty", "Control Scheme", "Graphics Quality"};
    
    // Draw only the actual settings (exclude BACK_BUTTON from this loop)
    for (int i = 0; i < BACK_BUTTON; i++) {
        Vector2 settingPos = {
            settingsStartPosition.x,
            settingsStartPosition.y + i * settingSpacing
        };
        
        // Draw setting label
        Color labelColor = (i == selectedSettingIndex) ? selectedColor : normalColor;
        DrawText(settingLabels[i], settingPos.x, settingPos.y, settingFontSize, labelColor);
        
        // Draw setting control based on type
        Vector2 controlPos = {settingPos.x, settingPos.y + 30};
        
        switch (i) {
            case VOLUME:
                DrawVolumeSlider(controlPos);
                break;
            case DIFFICULTY:
                DrawDifficultyDropdown(controlPos);
                break;
            case CONTROLS:
                DrawControlsDropdown(controlPos);
                break;
            case GRAPHICS:
                DrawGraphicsDropdown(controlPos);
                break;
        }
    }
}

void GameSettingUIComponent::DrawVolumeSlider(Vector2 position) {
    Rectangle sliderRect = GetSliderRect(position);
    Rectangle handleRect = GetSliderHandleRect(position, gameState->settings.masterVolume, 0.0f, 1.0f);
    
    // Draw slider track
    DrawRectangleRec(sliderRect, DARKGRAY);
    DrawRectangleLinesEx(sliderRect, 2, WHITE);
    
    // Draw slider handle
    DrawRectangleRec(handleRect, valueColor);
    DrawRectangleLinesEx(handleRect, 2, WHITE);
    
    // Draw value text
    const char* valueText = TextFormat("%.0f%%", gameState->settings.masterVolume * 100);
    DrawText(valueText, position.x + sliderWidth + 20, position.y, settingFontSize, valueColor);
}

void GameSettingUIComponent::DrawDifficultyDropdown(Vector2 position) {
    Rectangle dropdownRect = {position.x, position.y, sliderWidth, sliderHeight};
    
    // Draw dropdown background
    DrawRectangleRec(dropdownRect, DARKGRAY);
    DrawRectangleLinesEx(dropdownRect, 2, WHITE);
    
    // Draw current selection
    const char* difficultyNames[] = {"Easy", "Normal", "Hard"};
    const char* selectedText = difficultyNames[gameState->settings.difficulty];
    DrawText(selectedText, position.x + 10, position.y + 2, settingFontSize - 4, valueColor);
    
    // Draw dropdown arrow
    DrawText("v", position.x + sliderWidth - 25, position.y + 2, settingFontSize - 4, WHITE);
}

void GameSettingUIComponent::DrawControlsDropdown(Vector2 position) {
    Rectangle dropdownRect = {position.x, position.y, sliderWidth, sliderHeight};
    
    // Draw dropdown background
    DrawRectangleRec(dropdownRect, DARKGRAY);
    DrawRectangleLinesEx(dropdownRect, 2, WHITE);
    
    // Draw current selection
    const char* controlNames[] = {"WASD", "Arrow Keys"};
    const char* selectedText = controlNames[gameState->settings.controlScheme];
    DrawText(selectedText, position.x + 10, position.y + 2, settingFontSize - 4, valueColor);
    
    // Draw dropdown arrow
    DrawText("v", position.x + sliderWidth - 25, position.y + 2, settingFontSize - 4, WHITE);
}

void GameSettingUIComponent::DrawGraphicsDropdown(Vector2 position) {
    Rectangle dropdownRect = {position.x, position.y, sliderWidth, sliderHeight};
    
    // Draw dropdown background
    DrawRectangleRec(dropdownRect, DARKGRAY);
    DrawRectangleLinesEx(dropdownRect, 2, WHITE);
    
    // Draw current selection
    const char* qualityNames[] = {"Low", "Medium", "High"};
    const char* selectedText = qualityNames[gameState->settings.graphicsQuality];
    DrawText(selectedText, position.x + 10, position.y + 2, settingFontSize - 4, valueColor);
    
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
    
    // Determine button color based on selection state and mouse hover
    Color buttonColor = DARKGRAY;
    Color textColor = WHITE;
    Color borderColor = WHITE;
    
    bool isSelected = (selectedSettingIndex == BACK_BUTTON);
    bool isMouseOver = CheckCollisionPointRec(GetMousePosition(), backButtonRect);
    
    if (isSelected) {
        buttonColor = selectedColor;
        textColor = BLACK;
        borderColor = BLACK;
    } else if (isMouseOver) {
        buttonColor = GRAY;
    }
    
    DrawRectangleRec(backButtonRect, buttonColor);
    DrawRectangleLinesEx(backButtonRect, 2, borderColor);
    
    const char* backText = "BACK TO MENU";
    int textWidth = MeasureText(backText, 20);
    DrawText(backText, 
        backButtonRect.x + backButtonRect.width / 2 - textWidth / 2,
        backButtonRect.y + backButtonRect.height / 2 - 10,
        20, textColor);
}

void GameSettingUIComponent::HandleInput() {
    // Navigate settings with UP/DOWN
    if (IsKeyPressed(KEY_UP)) {
        selectedSettingIndex--;
        if (selectedSettingIndex < 0) {
            selectedSettingIndex = SETTING_COUNT - 1;
        }
    }
    
    if (IsKeyPressed(KEY_DOWN)) {
        selectedSettingIndex++;
        if (selectedSettingIndex >= SETTING_COUNT) {
            selectedSettingIndex = 0;
        }
    }
    
    // Handle ENTER key for back button
    if (IsKeyPressed(KEY_ENTER)) {
        if (selectedSettingIndex == BACK_BUTTON) {
            ApplySettings();
            eventSystem->Emit("ChangeToMainMenu");
            return;
        }
    }
    
    // Modify selected setting with LEFT/RIGHT (only for actual settings, not back button)
    if (selectedSettingIndex < BACK_BUTTON) {
        if (IsKeyPressed(KEY_LEFT)) {
            UpdateSelectedSetting(-0.1f);
        }
        
        if (IsKeyPressed(KEY_RIGHT)) {
            UpdateSelectedSetting(0.1f);
        }
    }
    
    // Mouse interaction for volume slider
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 controlPos = {
            settingsStartPosition.x,
            settingsStartPosition.y + VOLUME * settingSpacing + 30
        };
        
        if (IsMouseOverSlider(controlPos)) {
            float newValue = GetSliderValueFromMouse(controlPos, 0.0f, 1.0f);
            gameState->settings.masterVolume = Clamp(newValue, 0.0f, 1.0f);
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

void GameSettingUIComponent::UpdateSelectedSetting(float delta) {
    // Only update actual settings, not the back button
    if (selectedSettingIndex >= BACK_BUTTON) return;
    
    switch (selectedSettingIndex) {
        case VOLUME:
            gameState->settings.masterVolume = Clamp(gameState->settings.masterVolume + delta, 0.0f, 1.0f);
            break;
            
        case DIFFICULTY:
            if (delta > 0) {
                gameState->settings.difficulty = (GameSettings::Difficulty)((gameState->settings.difficulty + 1) % 3);
            } else {
                gameState->settings.difficulty = (GameSettings::Difficulty)((gameState->settings.difficulty + 2) % 3);
            }
            break;
            
        case CONTROLS:
            if (delta > 0) {
                gameState->settings.controlScheme = (GameSettings::ControlScheme)((gameState->settings.controlScheme + 1) % 2);
            } else {
                gameState->settings.controlScheme = (GameSettings::ControlScheme)((gameState->settings.controlScheme + 1) % 2);
            }
            break;
            
        case GRAPHICS:
            if (delta > 0) {
                gameState->settings.graphicsQuality = (GameSettings::GraphicsQuality)((gameState->settings.graphicsQuality + 1) % 3);
            } else {
                gameState->settings.graphicsQuality = (GameSettings::GraphicsQuality)((gameState->settings.graphicsQuality + 2) % 3);
            }
            break;
    }
}

void GameSettingUIComponent::ApplySettings() {
    // Settings are already applied directly to gameState->settings during interaction
    // Just need to trigger any additional logic and notify other systems
    
    // Update player health if difficulty changed
    gameState->playerHealth = gameState->settings.GetPlayerStartingHealth();
    if (gameState->playerCurrentHealth > gameState->playerHealth) {
        gameState->playerCurrentHealth = gameState->playerHealth;
    }
    
    // Log applied settings
    const GameSettings& settings = gameState->settings;
    std::cout << "Settings applied:" << std::endl;
    std::cout << "  Master Volume: " << (settings.masterVolume * 100) << "%" << std::endl;
    std::cout << "  Difficulty: " << (settings.difficulty == GameSettings::EASY ? "Easy" : 
                                     settings.difficulty == GameSettings::NORMAL ? "Normal" : "Hard") << std::endl;
    std::cout << "  Controls: " << (settings.controlScheme == GameSettings::WASD ? "WASD" : "Arrow Keys") << std::endl;
    std::cout << "  Graphics: " << (settings.graphicsQuality == GameSettings::LOW ? "Low" : 
                                   settings.graphicsQuality == GameSettings::MEDIUM ? "Medium" : "High") << std::endl;
    
    // Emit event to notify other systems that settings changed
    eventSystem->Emit("OnSettingsChanged");
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
