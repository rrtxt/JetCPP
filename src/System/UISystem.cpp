#include "UISystem.h"
#include "HealthBarUIComponent.h"
#include "PauseMenuUIComponent.h"
#include "ScoreUIComponent.h"
#include "GameOverUIComponent.h"
#include "MainMenuUIComponent.h"
#include "GameSettingUIComponent.h"
#include <memory>

UISystem::UISystem(GameState* gameState, EventSystem* eventSystem)
    : gameState(gameState), eventSystem(eventSystem) {
}

UISystem::~UISystem() {
    ClearComponents();
}

void UISystem::AddComponent(std::unique_ptr<UIComponent> component) {
    if (component) {
        components.push_back(std::move(component));
    }
}

void UISystem::RemoveComponent(UIComponent* component) {
    components.erase(
        std::remove_if(components.begin(), components.end(),
            [component](const std::unique_ptr<UIComponent>& ptr) {
                return ptr.get() == component;
            }),
        components.end());
}

void UISystem::ClearComponents() {
    components.clear();
}

void UISystem::Draw() {
    for (auto& component : components) {
        if (component && component->IsVisible()) {
            component->Draw();
        }
    }
}

void UISystem::Update() {
    for (auto& component : components) {
        if (component && component->IsEnabled()) {
            component->Update();
        }
    }
}

void UISystem::SetupInGameUI() {
    ClearComponents();

    // Add in-game UI components
    AddComponent(std::make_unique<HealthBarUIComponent>(gameState));
    AddComponent(std::make_unique<ScoreUIComponent>(gameState));

    if (eventSystem) {
        AddComponent(std::make_unique<GameOverUIComponent>(gameState, eventSystem));
        AddComponent(std::make_unique<PauseMenuUIComponent>(gameState, eventSystem));
    }

    std::cout << "In-game UI setup complete with " << GetComponentCount() << " components" << std::endl;
}

void UISystem::SetupMainMenuUI() {
    ClearComponents();

    // Add main menu UI components
    if (eventSystem) {
        AddComponent(std::make_unique<MainMenuUIComponent>(gameState, eventSystem));
    }

    std::cout << "Main menu UI setup complete with " << GetComponentCount() << " components" << std::endl;
}

void UISystem::SetupSettingsUI() {
    ClearComponents();

    // Add settings UI components
    if (eventSystem) {
        AddComponent(std::make_unique<GameSettingUIComponent>(gameState, eventSystem));
    }

    std::cout << "Settings UI setup complete with " << GetComponentCount() << " components" << std::endl;
}
