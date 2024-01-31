#pragma once

#include <cstddef> // for size_t
#include <memory>  // for unique_ptr
#include <cstdlib> // for rand()
#include "Snowflake.h"
#include "SnowflakeRebound.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeSine.h"
#include "Constants.h" 

template<class T>
class SnowflakePool 
{
public:
    SnowflakePool() : nbSnowflakesActifs(0), pool(nullptr) 
    {
        initPool();
    }

    void spawn() 
    {
       nbSnowflakesActifs++;
       //std::cout << " nbSnowflakesActifs: " << nbSnowflakesActifs << std::endl;
    }

    void destroy(size_t deleteIdx) 
    {
        T toReplace = pool[deleteIdx]; 
        pool[deleteIdx] = pool[nbSnowflakesActifs + 1];

        double x = rand() / (double)RAND_MAX * SCREEN_WIDTH;
        double y = rand() / (double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;
        toReplace.x = x;
        toReplace.y = y;
        toReplace.deleteMe = false;
        pool[nbSnowflakesActifs + 1] = toReplace;
       
        if(nbSnowflakesActifs > 0)
            nbSnowflakesActifs--;

    }

    void fillArraySnowFlakeBase() 
    {
      // Implementation of fillArraySnowFlakeBase function
      for (size_t i = 0; i < MAX_NUM_SNOWFLAKES; i++) 
      {
        double x = rand() / (double)RAND_MAX * SCREEN_WIDTH;
        double y = rand() / (double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;
        pool[i] = T(x, y);
      }
    }

    void fillArraySnowFlakeAllTypes() 
    {
      // Implementation of fillArraySnowFlakeAllTypes function
      for (size_t i = 0; i < MAX_NUM_SNOWFLAKES; i++) 
      {
        T snowflake;
        double x = rand() / (double)RAND_MAX * SCREEN_WIDTH;
        double y = rand() / (double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;

        int rnd = rand();
        if (rnd < RAND_MAX / 10)
            snowflake = SnowflakeRebound(x, y);
        else if (rnd < RAND_MAX / 5 * 2)
            snowflake = SnowflakeNoContact(x, y);
        else if (rnd < RAND_MAX / 2)
            snowflake = SnowflakeSine(x, y);
        else
            snowflake = Snowflake(x, y);
            pool[i] = snowflake;
      }
    }

    size_t nbSnowflakesActifs;
    std::unique_ptr<T[]> pool;

private:
    void initPool() 
    {
     // Initialize the pool
     nbSnowflakesActifs = SNOWFLAKES_START_NUM;
     pool = std::make_unique<T[]>(MAX_NUM_SNOWFLAKES);
     fillArraySnowFlakeBase();
    }
};


//std::cout << "delIdx: " << (int)deleteIdx << " delMe before : " << pool[deleteIdx].deleteMe << std::endl;
//std::cout << "delIdx " << (int)deleteIdx << " xy before : " << pool[deleteIdx].x << " " << pool[deleteIdx].y << std::endl;

//std::cout << "1stInactive delMe before : " << pool[nbSnowflakesActifs + 1].deleteMe << std::endl;
//std::cout << "1stInactive xy before : " << pool[nbSnowflakesActifs + 1].x << " " << pool[nbSnowflakesActifs + 1].y << std::endl;