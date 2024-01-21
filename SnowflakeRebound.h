#pragma once

#include <SDL.h>
#include "Snowflake.h"

class SnowflakeRebound : public Snowflake
{
public:
    SnowflakeRebound(double x, double y);

    void update(double dt) override;
    void collide(Player& o) override;
private:
    bool alreadyHit;
    void rebound();
};
