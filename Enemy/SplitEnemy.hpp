#ifndef SPLITENEMY_HPP
#define SPLITENEMY_HPP
#include "Enemy.hpp"

class SplitEnemy : public Enemy {
public:
    SplitEnemy(int x, int y);
    void Hit(float damage) override;
    void Update(float deltaTime) override;
    bool hasSplit = false;
    bool dead = false;
private:
    void Split();
};
#endif   // SPLITENEMY_HPP
