#pragma once

#include "Common.h"
#include "GameState.h"

class UIComponent {
public:
    virtual ~UIComponent() = default;
    
    // Pure virtual methods that each component must implement
    virtual void Draw() = 0;
    
    // Optional update method (default implementation does nothing)
    virtual void Update() {}
    
    // Component state management
    virtual void SetVisible(bool visible) { isVisible = visible; }
    virtual bool IsVisible() const { return isVisible; }
    
    // Enable/disable component
    virtual void SetEnabled(bool enabled) { isEnabled = enabled; }
    virtual bool IsEnabled() const { return isEnabled; }

protected:
    bool isVisible = true;
    bool isEnabled = true;
};