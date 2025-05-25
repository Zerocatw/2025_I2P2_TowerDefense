#include "Shovel.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"

PlayScene* Shovel::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Shovel::Shovel(float x, float y)
    : Engine::Sprite("play/shovel.png", x, y){
    Anchor.y += 8.0f / GetBitmapHeight();
}

