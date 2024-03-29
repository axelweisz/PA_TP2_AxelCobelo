#include <iostream>
#include <vector>

#include <SDL.h>

#include "Game.h"

using namespace std;

Game::Game() : keepPlaying(true)
{
}
       
/**
     * Main game Loop
     *
     * See
     * http://gameprogrammingpatterns.com/game-loop.html
     * https://gafferongames.com/post/fix_your_timestep/
 */

void Game::loop(SDL_Renderer* renderer)
{
    SDL_Event event;

    unsigned int lastFrameTime = SDL_GetTicks() - MS_PER_STEP;
    unsigned int timeAccumulator = 0;

    while (keepPlaying) 
    {
        unsigned int frameTime = SDL_GetTicks();
        unsigned int dt = frameTime - lastFrameTime;

        if (dt > 100) dt = 100; //Avoid spiral of death 

        timeAccumulator += dt;

        //handle inpout
        while (SDL_PollEvent(&event)) 
        {
            handleInput(event);
        }

        // -- Update --
        while (timeAccumulator >= MS_PER_STEP) 
        {
            update(MS_PER_STEP);
            timeAccumulator -= MS_PER_STEP;
        }
        update(timeAccumulator);

        timeAccumulator = 0;

        render(renderer);

        int wait = frameTime + MS_PER_STEP - SDL_GetTicks();

        if (wait < 0) 
        {
            cout << "WARNING: lag of " << -wait << "ms" << endl;
        } 
        else 
        {
            SDL_Delay(wait);
        }

        lastFrameTime = frameTime;
    }
}
