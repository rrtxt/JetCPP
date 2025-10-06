#pragma once

#include "Common.h"

class EventSystem {
public:
    using Callback = std::function<void()>;
    
    void Subscribe(const std::string& eventName, Callback callback);
    void Emit(const std::string& eventName);

private:
    std::unordered_map<std::string, std::vector<Callback>> listeners;
};
