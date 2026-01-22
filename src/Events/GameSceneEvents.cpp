#include "GameSceneEvents.h"
#include "GameState.h"
void GameSceneEvents::Register(EventSystem *eventSystem, SceneManager *sceneManager, GameState* gameState){
    eventSystem->Subscribe("ChangeToMainMenu", [sceneManager]() {
        sceneManager->ChangeScene(GameState::MAIN_MENU);
    });

    eventSystem->Subscribe("ChangeToInGame", [sceneManager]() {
        sceneManager->ChangeScene(GameState::IN_GAME);
    });

    eventSystem->Subscribe("ChangeToSettings", [sceneManager]() {
        sceneManager->ChangeScene(GameState::SETTINGS);
    });

    eventSystem->Subscribe("QuitGame", [&]() {
        gameState->isShouldQuit = true;
    });

    eventSystem->Subscribe("RestartGame", [sceneManager, gameState]() {
        // Reset game state and restart
        gameState->isPaused = false;
        gameState->isGameOver = false;
        gameState->score = 0;
        gameState->playerCurrentHealth = gameState->playerHealth;
        TimeScale::Set(1);
        sceneManager->ChangeScene(GameState::IN_GAME);
    });

}
