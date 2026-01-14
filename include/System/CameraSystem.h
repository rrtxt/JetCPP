#pragma once
#include "EventSystem.h"
#include <raylib.h>
struct CameraShake {
    float intensity = 0.0f;
    float duration = 0.0f;
    float timer = 0.0f;
    float frequency = 0.0f; // Shake period
};

class CameraSystem {
    public:
        Camera2D* camera;
        Vector2 baseTarget;
        CameraShake shake;

        CameraSystem(Camera2D* camera, EventSystem* eventSystem);
        void Update();
        void SetTarget(Vector2 target);
        void Shake(float intensity, float duration, float dt);

    private:
        EventSystem* eventSystem;
};
