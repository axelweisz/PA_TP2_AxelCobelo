#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include <SDL.h>

#include "Constants.h"
#include "GameSnow.h"
#include "Player.h"

using namespace std;

GameSnow::GameSnow() : m_pause(false), 
          p(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), snf()
{
    init(presets[0]);
}

void GameSnow::init(int n)
{
    snf.nbSnowflakesActifs = n;
    snfs.nbSnowflakesActifs = n;
    snfnc.nbSnowflakesActifs = n;
    snfr.nbSnowflakesActifs = n;
//code ancien
 /*   
    snowflakes.clear();

    for(int i=0; i<n; i++) 
    {
        double x = rand()/(double)RAND_MAX * SCREEN_WIDTH;
        double y = rand()/(double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;

        addSnowflake(x, y);
    }
*/
}

void GameSnow::addSnowflake()
{
    // Default : top of the screen
    addSnowflake(rand()/(double)RAND_MAX * SCREEN_WIDTH, -10);
}

void GameSnow::addSnowflake(double x, double y)
{

    /*
    unique_ptr<Snowflake> snowflake;
    int rnd = rand();
    if(rnd < RAND_MAX / 10)
        snowflake = make_unique<SnowflakeRebound>(x, y);
    else if(rnd < RAND_MAX / 5 * 2)
        snowflake = make_unique<SnowflakeNoContact>(x, y);
    else if(rnd < RAND_MAX / 2)
        snowflake = make_unique<SnowflakeSine>(x, y);
    else
        snowflake = make_unique<Snowflake>(x, y);
    snowflakes.push_back(move(snowflake));
    */
}

void GameSnow::spawnRandomTypeSnowflake()
{
    int randomNumber = rand() % 4;
    switch (randomNumber)
    {
    case 0:
        if (snf.nbSnowflakesActifs < MAX_NUM_SNOWFLAKES)
            snf.spawn();
        break;
    case 1:
        if (snfs.nbSnowflakesActifs < MAX_NUM_SNOWFLAKES)
            snfs.spawn();
        break;
    case 2:
        if (snfs.nbSnowflakesActifs < MAX_NUM_SNOWFLAKES)
            snfnc.spawn();
        break;
    case 3:
        if (snfs.nbSnowflakesActifs < MAX_NUM_SNOWFLAKES)
            snfr.spawn();
        break;
    default:
        break;
    }
}

void GameSnow::handleInput(const SDL_Event& event)
{
    switch (event.type) 
    {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT) 
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                p.x = x;
                p.y = y;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym) 
            {
                case SDLK_LEFT:
                    p.inputs.left = false;
                    break;
                case SDLK_RIGHT:
                    p.inputs.right = false;
                    break;
                case SDLK_DOWN:
                    p.inputs.down = false;
                    break;
                case SDLK_UP:
                case SDLK_SPACE:
                    p.inputs.jump = false;
                    break;
            }
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) 
            {
                case SDLK_LEFT:
                    p.inputs.left = true;
                    break;
                case SDLK_RIGHT:
                    p.inputs.right = true;
                    break;
                case SDLK_DOWN:
                    p.inputs.down = true;
                    break;
                case SDLK_UP:
                case SDLK_SPACE:
                    p.inputs.jump = true;
                    break;
                //Pause
                case SDLK_p:
                    m_pause = !m_pause;
                    break;
                case SDLK_k:
                    m_pause = !m_pause;
                    break;
                case SDLK_l:
                    snf.spawn();
                    break;
                case SDLK_1:
                case SDLK_2:
                case SDLK_3:
                case SDLK_4:
                case SDLK_5:
                case SDLK_6:
                case SDLK_7:
                case SDLK_8:
                case SDLK_9:
                    init(presets[event.key.keysym.sym - SDLK_1]);
                    break;
                case SDLK_ESCAPE:
                    keepPlaying = false;
                    break;
             }
    }
}

void GameSnow::update(unsigned long dt)
{
    if(m_pause) return;

    double delta_t = dt / 1000.0;

    //Physics
    p.update(delta_t); //player
    //flocons
    for (size_t i = 0; i < snf.nbSnowflakesActifs; i++)
    {
        snf.pool[i].update(delta_t);
    }
    for (size_t i = 0; i < snfs.nbSnowflakesActifs; i++)
    {
        snfs.pool[i].update(delta_t);
    }
    for (size_t i = 0; i < snfnc.nbSnowflakesActifs; i++)
    {
        snfnc.pool[i].update(delta_t);
    }
    for (size_t i = 0; i < snfr.nbSnowflakesActifs; i++)
    {
        snfr.pool[i].update(delta_t);
    }

    //code ancien
    //for(auto& obj : snowflakes) {  obj->update(delta_t); }

    // Collisions
    for (size_t i = 0; i < snf.nbSnowflakesActifs; i++)
    {
        snf.pool[i].testCollision(p);
    }
    for (size_t i = 0; i < snfs.nbSnowflakesActifs; i++)
    {
        snfs.pool[i].testCollision(p);
    }
    for (size_t i = 0; i < snfnc.nbSnowflakesActifs; i++)
    {
        snfnc.pool[i].testCollision(p);
    }
    for (size_t i = 0; i < snfr.nbSnowflakesActifs; i++)
    {
        snfr.pool[i].testCollision(p);
    }

    //call destrouy if shouldDelete == true
    for (size_t i = 0; i < snf.nbSnowflakesActifs; i++)
    {
        if (snf.pool[i].shouldDelete())
        {
            snf.destroy(i);
            spawnRandomTypeSnowflake();
        } 
    }
    for (size_t i = 0; i < snfs.nbSnowflakesActifs; i++)
    {
        if (snfs.pool[i].shouldDelete())
        {
            snfs.destroy(i);
            spawnRandomTypeSnowflake();
        }
    }
    for (size_t i = 0; i < snfnc.nbSnowflakesActifs; i++)
    {
        if (snfnc.pool[i].shouldDelete())
        {
            snfnc.destroy(i);
            spawnRandomTypeSnowflake();
        }
    }
    for (size_t i = 0; i < snfr.nbSnowflakesActifs; i++)
    {
        if (snfr.pool[i].shouldDelete())
        {
            snfr.destroy(i);
            spawnRandomTypeSnowflake();
        }
    }
     
    //code ancien
    /*
        for(auto& obj : snowflakes) {  obj->testCollision(p);  }
         Remove unused objects
        tem que fazer o codego que qdo o snowflake goes out of bounds
        ele volta pra cima
        long size_before = snowflakes.size();
        snowflakes.erase(remove_if(snowflakes.begin(),
                                   snowflakes.end(),
                                   [](auto& ptr) {
                                       return ptr->shouldDelete();
                                   }),
                         snowflakes.end());
        long nb_new_snowflakes = size_before - snowflakes.size();
        for(int i=0; i<nb_new_snowflakes; i++){ addSnowflake(); }
    */

}

void GameSnow::render(SDL_Renderer* renderer) const
{
    // -- Clear screen --
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

   //Draw player
    p.render(renderer);
    //Draw particles
    for (size_t i = 0; i < snf.nbSnowflakesActifs; i++)
    {
        snf.pool[i].render(renderer);
    }
    for (size_t i = 0; i < snfs.nbSnowflakesActifs; i++)
    {
        snfs.pool[i].render(renderer);
    }
    for (size_t i = 0; i < snfnc.nbSnowflakesActifs; i++)
    {
        snfnc.pool[i].render(renderer);
    }
    for (size_t i = 0; i < snfr.nbSnowflakesActifs; i++)
    {
        snfr.pool[i].render(renderer);
    }

    //code ancien
    //for(const auto& obj : snowflakes) { obj->render(renderer);}

    SDL_RenderPresent(renderer);
}
