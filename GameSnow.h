#pragma once
#include <vector>
#include <memory>

#include "Player.h"
#include "Snowflake.h"
#include "Game.h"
#include "SnowflakePool.h"
#include "Snowflake.h"
#include "SnowflakeRebound.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeSine.h"

class GameSnow : public Game
{
public:
    GameSnow();
    
    SnowflakePool<Snowflake> snf;
    SnowflakePool<SnowflakeSine> snfs;
    SnowflakePool<SnowflakeNoContact> snfnc;
    SnowflakePool<SnowflakeRebound> snfr;

    void handleInput(const SDL_Event& event) override;
    void update(unsigned long dt) override;
    void render(SDL_Renderer* renderer) const override;
    void init(int snowflakes);
    void addSnowflake();
    void addSnowflake(double x, double y);  
    void spawnRandomTypeSnowflake();

private:
    bool m_pause;
    //comme maintenans ce sont 4 pools j'ai divise le nombre de chaque case par 4 pour qu'on ait la cantite mnaximale originale en tout temps

 
    unsigned long presets[9] = {
                                250, 
                                625, 
                                1250, 
                                1500, 
                                1750, 
                                2000, 
                                2250, 
                                2500, 
                                3000
                                };



    Player p;
    std::vector<std::unique_ptr<Snowflake>> snowflakes;

};
 

