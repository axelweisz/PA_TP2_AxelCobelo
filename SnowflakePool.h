#pragma once
#include <cstddef> // pour size_t
#include <memory> // pour unique_ptr
#include "Snowflake.h"

class SnowflakePool
{
public:
    SnowflakePool(const int);

    void spawn();

    void destroy(size_t deleteIdx);

 // ... Autres méthodes à votre choix ...
    void fillSnowflakeArray(size_t);


private:
    std::unique_ptr<Snowflake[]> pool; 
    size_t nbSnowflakesActifs;
};
