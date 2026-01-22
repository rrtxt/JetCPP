#pragma once

#include "raylib.h"
#include "raymath.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Sprite
const float SPRITE_SCALE = 3.0f;

// Player
const int VELOCITY = 300;
const int PLAYER_WIDTH = 25;
const int PLAYER_HEIGHT = 25;

// Enemy
const int ENEMY_SPEED = 200;
const int ENEMY_WIDTH = 25;
const int ENEMY_HEIGHT = 25;
