#include "SnowflakePool.h"

using namespace std;

SnowflakePool::SnowflakePool(const int size) : 
	nbSnowflakesActifs{ 0 }, pool(make_unique<Snowflake[]>(size))
{
	fillSnowflakeArray(size);
}

void SnowflakePool::spawn()
{
}

void SnowflakePool::destroy(size_t deleteIdx)
{
}

void SnowflakePool::fillSnowflakeArray(size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		pool[i] = Snowflake(0.0, 0.0);
	}
}

