#include "EventSystem.h"

void EventSystem::Subscribe(const std::string& eventName, Callback callback) {
    listeners[eventName].push_back(callback);
}

void EventSystem::Emit(const std::string& eventName) {
    if (listeners.find(eventName) != listeners.end()) {
        for (const auto& callback : listeners[eventName]) {
            callback();
        }
    }
}
