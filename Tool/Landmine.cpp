#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <utility>
#include <iostream>
#include "Landmine.hpp"
#include "Scene/PlayScene.hpp"
#include "Enemy/Enemy.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "Engine/Collider.hpp"

const int Landmine::Price = 150;
PlayScene* Landmine::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Landmine::Landmine(float x, float y)
    : Engine::Sprite("play/landmine.png", x, y){
    Anchor.y += 2.0f / GetBitmapHeight();
}

void Landmine::Update(float deltaTime){
    Sprite::Update(deltaTime);
    if (Preview || !Enabled) return;

    auto *scene = getPlayScene();
    if (!scene) return;
    bool boom = false;

    for (auto &obj : scene->EnemyGroup->GetObjects()) {
        Enemy *enemy = dynamic_cast<Enemy *>(obj);
        if (!enemy) continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius,enemy->Position, enemy->CollisionRadius)) {
            boom = true;
            break;
        }
    }
    if(!boom) return;
    if(boom){ // enemy on landmine
        for (auto &obj : scene->EnemyGroup->GetObjects()) {
            Enemy *enemy = dynamic_cast<Enemy *>(obj);
            if (!enemy) continue;
            if (Engine::Collider::IsCircleOverlap(Position, boomRadius,enemy->Position, enemy->CollisionRadius)) {
                enemy->Hit(damage);
            }
        }
        auto it = GetObjectIterator();
        it->first = false;
        scene->LandGroup->RemoveObject(it);
        return;
    }
}
void Landmine::Draw() const {
    if (Preview) {
        al_draw_filled_circle(Position.x, Position.y,boomRadius,al_map_rgba(0, 255, 0, 50));
    }
    Engine::Sprite::Draw();
}

int Landmine::GetPrice() const {
    return Price;
}
