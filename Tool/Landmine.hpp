#ifndef LANDMINE_HPP
#define LANDMINE_HPP

#include <string>
#include "Engine/Sprite.hpp"

class PlayScene;

class Landmine : public Engine::Sprite {
public:
    static const int Price;
    Landmine(float x, float y);
    bool Preview = false;
    bool Enabled = false;
    void Update(float deltaTime) override;
    void Draw() const override;
    int GetPrice() const;
protected:
    PlayScene* getPlayScene();
    float CollisionRadius = 16.0f;
    float boomRadius = 128.0f;   
    float damage = 50.0f;
};

#endif // LANDMINE_HPP
