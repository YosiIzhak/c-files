#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "genmap.h"
#include "genlist.h"
#include "dliststruct.h"
#include "dlistitr.h"
#include "listfunction.h"
#define HASHSIZE 2000


void ItemDestroy(void* _item)
{
	free(_item);
}
/**************************************************/
size_t HashFunc(void* _word)
{
int len;
int count = 0;
int i;

	if(_word == NULL)
	{
		return 0;
	}
	len = strlen(_word);
	for(i = 0; i < len; i++)
	{
		count = count + ((*(char*)_word + i) - '0');
	}
		
return count;
}

/**************************************************/
int Equality(void* _firstKey, void* _secondKey)
{
	if(_firstKey == NULL || _secondKey == NULL)
	{
		return 0;
	}
	if(strcmp(_firstKey, _secondKey) == 0)
	{
		return 1;
	}
	return 0;
}
/**************************************************/
static void PrintKey(void* _key)
{
	if (NULL == _key)
	{
		return;
	}
	printf(" %s  ",((char*)_key));
}
/**************************************************/
static void PrintValue(void* _value)
{
	if (NULL == _value)
	{
		return;
	}
	printf(" %d times\n  ",(*(int*)_value));
}
/**************************************************/
char* FixWord(char* word)
{
int j;

	if(word[0] <= 'Z' && word[0] >= 'A')
	{
		word[0] = word[0] + 32;
	}

	 for(j = 0; j < strlen(word); j++)
	 {
	        if( word[j] == '.' || word[j] == ',' || word[j] == ':' || word[j] == '\n' || word[j] == ';' || word[j] == ' ')
	        {
	        	word[j] = '\0';
	        }
	 }
	 
return word;
}	
/**************************************************/
void WordMap(char _fileName[])
{
	char str[15], word[15];
	void* count;
	char* wordKey;
	int* valueKey;
	HashMap* map;
	Map_Result res;
	FILE* ptr1; 
	int len;
	if (_fileName == NULL)
	{
		return;
	}
	ptr1 = fopen(_fileName , "r" );
	if (ptr1 == NULL)
	{
		return;
	}
	map = HashMap_Create (HASHSIZE , HashFunc , Equality);
	fscanf(ptr1, "%s", str);
	while (!feof(ptr1))
	{
		
		strcpy(word, str);
		res = HashMap_Find(map, word, &count);
		strcpy(word, str);
		if ( res == MAP_SUCCESS)
		{
			(*(int*)count)++;
		}
		else
		{
			strcpy(word, str);
			len = strlen(word);
			if((wordKey = (char*) malloc(len + 1)) == NULL)
			{
				return;
			}
			if((valueKey = (int*) malloc(sizeof(int))) == NULL)		  	          {
				return;
			}
			strcpy(wordKey, word);
			*valueKey = 1;
			HashMap_Insert(map, wordKey, valueKey);
		}
		fscanf(ptr1, "%s", str);
	}
	
	PrintMap(map, PrintKey, PrintValue);
	fclose(ptr1);
	HashMap_Destroy(&map, ItemDestroy, ItemDestroy);
}




int main()
{
	WordMap("sometext.txt");
}
    
    













