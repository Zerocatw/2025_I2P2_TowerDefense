#include <string>

#include "SplitEnemy.hpp"
#include "SoldierEnemy.hpp"
#include "Scene/PlayScene.hpp"
#include <iostream>

                                    //   Enemy(std::string img, float x, float y, float radius, float speed, float hp, int money)
SplitEnemy::SplitEnemy(int x, int y) : Enemy("play/enemy-6.png", x, y, 20, 20, 60, 50) {
}

void SplitEnemy::Hit(float damage){
    if (dead) return; // already die!
    hp -= damage;
    if (hp <= 0) {
        if (!hasSplit) {
            Split();         // split 2 Soldier
            hasSplit = true;
        }
        dead = true;     // to die
    }
}
void SplitEnemy::Split() {
    PlayScene* scene = getPlayScene();

    // be sure path
    if (path.size() <= 1) {
        std::cout << "[SplitEnemy] Path too short, cannot split\n";
        return;
    }

    // cur, next
    Engine::Point gridCurr = path[0];
    Engine::Point gridNext = path[1];
    Engine::Point forwardVec = (gridNext - gridCurr).Normalize();

    // offset
    float offset = PlayScene::BlockSize * 0.25f;

    // next, prev
    Engine::Point frontPos = Position + forwardVec * offset;
    Engine::Point backPos  = Position - forwardVec * offset;
    std::array<Engine::Point, 2> candidates = { frontPos, backPos };

    for (auto& pos : candidates) {
        // space index
        int gx = static_cast<int>(std::floor(pos.x / PlayScene::BlockSize));
        int gy = static_cast<int>(std::floor(pos.y / PlayScene::BlockSize));

        // check
        if (gx < 0 || gx >= PlayScene::MapWidth ||
            gy < 0 || gy >= PlayScene::MapHeight) {
            std::cout << "[SplitEnemy] Candidate (" << pos.x << "," << pos.y 
                      << ") grid (" << gx << "," << gy << ") out of bounds, skip\n";
            continue;
        }

        if (scene->mapState[gy][gx] != PlayScene::TILE_DIRT) {
            std::cout << "[SplitEnemy] Candidate grid (" << gx << "," << gy 
                      << ") not TILE_DIRT, skip\n";
            continue;
        }

        float centerX = gx * PlayScene::BlockSize + PlayScene::BlockSize * 0.5f;
        float centerY = gy * PlayScene::BlockSize + PlayScene::BlockSize * 0.5f;

        // born
        auto soldier = new SoldierEnemy(centerX, centerY);
        soldier->UpdatePath(scene->mapDistance);
        scene->EnemyGroup->AddNewObject(soldier);

        std::cout << "[SplitEnemy] Spawned SoldierEnemy at grid (" 
                  << gx << ", " << gy << ") -> pixel (" 
                  << centerX << ", " << centerY << ")\n";
    }

    std::cout << "[SplitEnemy] Split complete\n";
}




void SplitEnemy::Update(float deltaTime) {
    if (dead) {
        dead = false; //delay 1
        Enemy::Hit(9999); // delete SplitEnemy
        return;
    }
    Enemy::Update(deltaTime);
}