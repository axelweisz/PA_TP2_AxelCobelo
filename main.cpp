/*
  Basic SDL game engine -- Nicolas Hurtubise

  SDL download : https://libsdl.org/download-2.0.php

  Visual Studio 2019 setup :
  https://stackoverflow.com/questions/57732058/how-do-i-link-sdl-with-visual-studio-2019

  -- SDL References --
  https://lazyfoo.net/tutorials/SDL/index.php
  http://headerphile.com/sdl2/sdl2-part-1-setting-up-sdl2/

  -- Game Loop --
  http://gameprogrammingpatterns.com/game-loop.html
  https://gafferongames.com/post/fix_your_timestep/
*/

#include <iostream>
#include <SDL.h>

#include "Constants.h"
#include "GameSnow.h"

#include "Snowflake.h"
#include "Game.h"
#include "SnowflakePool.h"
#include "Snowflake.h"
#include "SnowflakeRebound.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeSine.h"
using namespace std;

int main(int argc, char* args[])
{
    Player pl(0, 0);
    Snowflake sn(0, 0);
    SnowflakeRebound reb(0, 0);
    SnowflakeNoContact noc(0, 0);
    SnowflakeSine sine(0, 0);

    cout << "Player sizeof: " << sizeof(pl) << endl;
    cout << "Snowflake sizeof: " << sizeof(sn) << endl;
    cout << "SnowflakeRebound sizeof: " << sizeof(reb) << endl;
    cout << "SnowflakeNoContact sizeof: " << sizeof(noc) << endl;
    cout << "SnowflakeSine sizeof: " << sizeof(sine) << endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        cout << "SDL error (init): " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    SDL_Window* window = SDL_CreateWindow(
                                         WINDOW_TITLE,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SCREEN_WIDTH, SCREEN_HEIGHT,
                                         SDL_WINDOW_SHOWN
                                         );

    if (window == nullptr) 
    {
        cout << "SDL error (window): " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    SDL_Renderer* renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) 
    {
        cout << "SDL error (renderer):" << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
    }

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    GameSnow g;
    g.loop(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
