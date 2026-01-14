#include "EventSystem.h"
#include <CameraSystem.h>
#include <cstdio>
#include <raylib.h>

CameraSystem::CameraSystem(Camera2D* camera, EventSystem* eventSystem) : camera(camera), eventSystem(eventSystem){
    eventSystem->Subscribe("CameraShake", [this](){
        printf("camera shaked...\n");
        Shake(8.0f, 0.2f, 0.01f);
    });
};

void CameraSystem::SetTarget(Vector2 target) {
    baseTarget = target;
};

void CameraSystem::Shake(float intensity, float duration, float frequency) {
    shake.intensity = intensity;
    shake.duration = duration;
    shake.timer = duration;
    shake.frequency = frequency;
};

void CameraSystem::Update(){
    if (!camera){
        printf("Camera is not set...\n");
        return;
    }

    camera->target = baseTarget;

    if (shake.timer > 0.0f) {
        shake.timer -= shake.frequency;

        float progress = shake.timer / shake.duration;
        float currentIntensity = shake.intensity * progress;

        float offsetX = GetRandomValue(-100, 100) / 100.0f * currentIntensity;
        float offsetY = GetRandomValue(-100, 100) / 100.0f * currentIntensity;

        camera->target.x += offsetX;
        camera->target.y += offsetY;
    }
}
