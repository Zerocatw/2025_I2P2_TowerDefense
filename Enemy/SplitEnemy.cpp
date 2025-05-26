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

    for(auto it:path){
        std::cout << it.x << " " << it.y << "\n";
    }

    if (path.size() >= 2) {
        Engine::Point Spawn_next = path.back();
        Engine::Point Spawn_next_next = path[(int)path.size()-2];
        // first born!
        int gx = Spawn_next.x;
        int gy = Spawn_next.y;
        float centerX = gx * PlayScene::BlockSize + PlayScene::BlockSize/2;
        float centerY = gy * PlayScene::BlockSize + PlayScene::BlockSize/2;
        auto soldier = new SoldierEnemy(centerX, centerY);
        soldier->UpdatePath(scene->mapDistance);
        scene->EnemyGroup->AddNewObject(soldier);
        std::cout << "First born : " << gx << " " << gy; 
        // second born!
        gx = Spawn_next_next.x;
        gy = Spawn_next_next.y;
        centerX = gx * PlayScene::BlockSize + PlayScene::BlockSize/2;
        centerY = gy * PlayScene::BlockSize + PlayScene::BlockSize/2;
        soldier = new SoldierEnemy(centerX, centerY);
        soldier->UpdatePath(scene->mapDistance);
        scene->EnemyGroup->AddNewObject(soldier);
        std::cout << "Second born : " << gx << " " << gy; 
    }
    std::cout << "born all done!\n";
}




void SplitEnemy::Update(float deltaTime) {
    if (dead) {
        dead = false; //delay 1
        Enemy::Hit(9999); // delete SplitEnemy
        return;
    }
    Enemy::Update(deltaTime);
}