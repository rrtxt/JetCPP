#include "GameState.h"

void GameState::RegisterEvents(EventSystem* es) {
    es->Subscribe("OnPlayerDied", [&]() {
        this->isGameOver = true;
    });
    es->Subscribe("OnPlayerHit", [&, es]() {
        this->playerCurrentHealth -= 1;
        cout << "Player Health: " << this->playerCurrentHealth << endl;

        es->Emit("OnHealthchanged");
    });
    es->Subscribe("OnHealthchanged", [&, es](){
        if(this->playerCurrentHealth <= 0){
            es->Emit("OnPlayerDied");
        }
    });
    es->Subscribe("OnEnemyDestroyed", [&]() {
        this->score += 100;
    });
}
