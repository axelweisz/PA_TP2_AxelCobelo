#pragma once

#include <SDL.h>
#include "Snowflake.h"

class SnowflakeRebound : public Snowflake
{
public:
    SnowflakeRebound();
    SnowflakeRebound(double x, double y);

    virtual void update(double dt) override;
    virtual void collide(Player& o) override;
private:
    bool alreadyHit;
    void rebound();
};
