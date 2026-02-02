#include "Events/GameStateEvents.h"
#include "EventSystem.h"
#include "GameState.h"
#include "SoundSystem.h"

void GameStateEvents::Register(EventSystem* eventSystem, GameState* gameState, SoundSystem* soundSystem){
    eventSystem->Subscribe("OnPlayerDied", [gameState]() {
        TimeScale::Set(0);
        gameState->isGameOver = true;
    });
    eventSystem->Subscribe("OnPlayerHit", [gameState, eventSystem, soundSystem]() {
        gameState->playerCurrentHealth -= 1;
        cout << "Player Health: " << gameState->playerCurrentHealth << endl;

        soundSystem->PlaySFX("player_hit");
        eventSystem->Emit("CameraShake");
        eventSystem->Emit("OnHealthchanged");
    });
    eventSystem->Subscribe("OnHealthchanged", [gameState, eventSystem](){
        if(gameState->playerCurrentHealth <= 0){
            eventSystem->Emit("OnPlayerDied");
        }
    });
    eventSystem->Subscribe("OnEnemyDestroyed", [gameState, soundSystem]() {
        gameState->score += 100;
        soundSystem->PlaySFX("explosion");
    });
    eventSystem->Subscribe("OnBulletSpawn", [gameState, soundSystem]() {
        std::cout << "Bullet Spawned, playing sound" << std::endl;
        soundSystem->PlaySFX("shoot");
    });
}
