//#include "SnowflakePool.h"
//#include "Constants.h"
//#include "SnowflakeNoContact.h"
//#include "SnowflakeSine.h"
//#include "SnowflakeRebound.h"
//
//using namespace std;
//
//template<class T>
//SnowflakePool<T>::SnowflakePool() : 
//	nbSnowflakesActifs{ SNOWFLAKES_START_NUM },
//	pool(make_unique<T[]>(MAX_NUM_SNOWFLAKES))
//{
//	//fillArraySnowFlakeBase();
//	//fillArraySnowFlakeAllTypes();
//}
//
//template<class T>
//void SnowflakePool<T>::spawn()
//{
//	nbSnowflakesActifs++;
//}
//
//template<class T>
//void SnowflakePool<T>::destroy(size_t deleteIdx)
//{
//	T toReplace = pool[deleteIdx];
//	pool[deleteIdx] = pool[nbSnowflakesActifs + 1];
//	pool[nbSnowflakesActifs + 1] = toReplace;
//
//	//pool[deleteIdx].x = rand() / (double)RAND_MAX * SCREEN_WIDTH;
//	//pool[deleteIdx].y = rand() / (double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;
//	pool[deleteIdx].deleteMe = false;
//}
//
//template<class T>
//void SnowflakePool<T>::fillArraySnowFlakeBase()
//{
//	for (size_t i = 0; i < MAX_NUM_SNOWFLAKES; i++)
//	{
//		double x = rand() / (double)RAND_MAX * SCREEN_WIDTH;
//		double y = rand() / (double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;
//		pool[i] = T(x, y);
//	}
//}
//
//template<class T>
//void SnowflakePool<T>::fillArraySnowFlakeAllTypes()
//{
//	for (size_t i = 0; i < MAX_NUM_SNOWFLAKES; i++)
//	{
//		T snowflake;
//		double x = rand() / (double)RAND_MAX * SCREEN_WIDTH;
//		double y = rand() / (double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10;
//
//		int rnd = rand();
//		if (rnd < RAND_MAX / 10)
//			snowflake = SnowflakeRebound(x, y);
//		else if (rnd < RAND_MAX / 5 * 2)
//			snowflake = SnowflakeNoContact(x, y);
//		else if (rnd < RAND_MAX / 2)
//			snowflake = SnowflakeSine(x, y);
//		else
//			snowflake = Snowflake(x, y);
//
//		pool[i] = snowflake;
//	}
//}
//
//
