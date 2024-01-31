#pragma once

#include <SDL.h>
#include "GameObject.h"
#include "Player.h"

class Snowflake : public GameObject
{
public:
    Snowflake();
    Snowflake(double x, double y);

    virtual void update(double dt) override;
    virtual void collide(Player& o) override;
};
