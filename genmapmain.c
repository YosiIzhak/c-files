#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genmap.h"
#include "genlist.h"
#include "dliststruct.h"
#include "dlistitr.h"
#include "listfunction.h"

struct Person
{
int m_id;
char m_name[128];
int m_age;
}; 

size_t HashFunc(void*_key)
{
	if( _key == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}
	return (*(int*)_key) * 2;
}
/**************************************************/

int Equality(void* _firstKey, void* _secondKey)
{
	int a = *((int*)(_firstKey));
	int b = *((int*)(_secondKey));
	if (a == b)
	{
		return 1;
	}
	return 0;
}
/**************************************************/
int checkNullCreate()
{
	HashMap* map;
	map = HashMap_Create ( 0 , HashFunc , Equality) ;
	printf("checkNullCreate test: ");
	if ( map == NULL)
	{
		printf ( "PASS\n" ) ;
	}
	else
	{
		printf ( "FAIL\n" ) ;
	}
}
/**************************************************/
int checkNotNullCreate()
{
	HashMap* map;
	map = HashMap_Create ( 100 , HashFunc , Equality) ;
	printf("checkNotNullCreate test: ");
	if ( map != NULL)
	{
		printf ( "PASS\n" ) ;
	}
	else
	{
		printf ( "FAIL\n" ) ;
	}
}
/**************************************************/
int checkDestroy()
{
	HashMap* map;
	map = HashMap_Create ( 100 , HashFunc , Equality);
	HashMap_Destroy(&map, NULL, NULL);
	printf("checkDestroy test: ");
	if ( map == NULL)
	{
		printf ( "PASS\n" ) ;
	}
	else
	{
		printf ( "FAIL\n" ) ;
	}
}
/**************************************************/
int checkInsert()
{
	
	HashMap* map;
	Map_Result res;
	int key = 10;
	int value = 1000,  value1 = 2000, value2 = 3000;
	map = HashMap_Create ( 100 , HashFunc , Equality);
	res = HashMap_Insert(map, &key, &value);
	printf("checkInsert test: ");
	if ( res == MAP_SUCCESS)
	{
		printf ( "PASS\n" ) ;
	}
	else
	{
		printf ( "FAIL\n" ) ;
	}
	HashMap_Destroy(&map, NULL, NULL);
}
/**************************************************/
int checkInsertAndFind()
{
	
	HashMap* map;
	Map_Result res, res1;
	int *pValue;
	int key = 10;
	int value = 1000;
	map = HashMap_Create (100 , HashFunc , Equality);
	res = HashMap_Insert(map, &key, &value);
	
	res1 = HashMap_Find(map, &key, (void**)&pValue);
	printf("checkInsertAndFind test: ");
	if ( res1 == MAP_SUCCESS)
	{
		printf ( "PASS\n" ) ;
	}
	else
	{
		printf ( "FAIL\n" ) ;
	}
	HashMap_Destroy(&map, NULL, NULL);
}
/**************************************************/
int main()
{
	/*checkNullCreate();
	checkNotNullCreate();
	checkDestroy();
	checkInsert();*/
	checkInsertAndFind();
	
	
	
}
