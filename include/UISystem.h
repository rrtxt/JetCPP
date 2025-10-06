#pragma once

#include "Common.h"
#include "GameState.h"
#include "EventSystem.h"
#include "UIComponent.h"
#include <memory>

class UISystem {
public:
    UISystem(GameState* gameState, EventSystem* eventSystem = nullptr);
    ~UISystem();

    // Component management
    void AddComponent(std::unique_ptr<UIComponent> component);
    void RemoveComponent(UIComponent* component);
    void ClearComponents();
    
    // Rendering and updating
    void Draw();
    void Update();
    
    // Utility methods
    size_t GetComponentCount() const { return components.size(); }
    
    // Scene-specific setup helpers
    void SetupInGameUI();
    void SetupMainMenuUI();

private:
    GameState* gameState;
    EventSystem* eventSystem;
    std::vector<std::unique_ptr<UIComponent>> components;
};
