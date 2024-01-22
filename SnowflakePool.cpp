#include "SnowflakePool.h"
#include "Constants.h"
using namespace std;

SnowflakePool::SnowflakePool(const int size) : 
	nbSnowflakesActifs{ MAX_NUM_SNOWFLAKES }, pool(make_unique<Snowflake[]>(size))
{
	fillSnowflakeArray();
}

void SnowflakePool::spawn()
{
}

void SnowflakePool::destroy(size_t deleteIdx)
{
}

void SnowflakePool::fillSnowflakeArray()
{
	for (size_t i = 0; i < MAX_NUM_SNOWFLAKES; i++)
	{
		double x = rand() / (double)RAND_MAX * SCREEN_WIDTH;
		double y = rand() / (double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;
		pool[i] = Snowflake(x, y);
	}
}

