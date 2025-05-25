#ifndef SHOVEL_HPP
#define SHOVEL_HPP

#include <string>
#include "Engine/Sprite.hpp"

class PlayScene;

class Shovel : public Engine::Sprite {
public:
    Shovel(float x, float y);
    bool Preview = false;
protected:
    PlayScene* getPlayScene();
};

#endif // SHOVEL_HPP
