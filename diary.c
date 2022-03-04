#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "diary.h"


diary *CreateDiary( int _size, int _blockSize)
{
	diary *ptr;
	if (_size == 0 || _blockSize < 0)
	{
		return NULL_ERROR;
	}
	
	ptr = (diary*) malloc (sizeof(diary));
	if (ptr == NULL) 
	{
        	printf("Memory not allocated.\n");
       	return NULL_ERROR;
   	}
	ptr->meetArray = (meet**) malloc(_size * sizeof(meet*));
	if (ptr->meetArray == NULL) 
	{
        	printf("Memory not allocated.\n");
       	return NULL_ERROR;
   	}
  	ptr->dArraySize = _size;
  	ptr->numOfElements = 0;
  	ptr->dArrayBlockSize = _blockSize;
  	return ptr;
}

meet *CreateMeet(float _start, float _end, int _room)
{
	meet *meetPtr;
	if (_start < 0 || _end > 24 || _end < _start)
	{
		return NULL;
	}
	meetPtr = (meet*) malloc(sizeof(meet));
	if (meetPtr == NULL) 
	{
        	return NULL_ERROR;
   	}
	meetPtr->start = _start;
  	meetPtr->end = _end;
  	meetPtr->room = _room;
  	return meetPtr;
}

int Destroy(diary *_ptr)
{	
	int i;
	if (_ptr == NULL || _ptr-> m_magicNumber != MAGIC_NUMBER)
	{ 
		return NULL_ERROR;
	} 
	_ptr-> m_magicNumber = 0;
	for(i = 0; i < _ptr -> numOfElements; i++)
	{
		free(_ptr -> meetArray[i]);
	}
	free(_ptr->meetArray);
	free(_ptr);
	return SUCCESS;
}
int CheckValidMeet (diary* _ptr, meet* _meetPtr)
{
	int i;
	for (i = 0; i < _ptr->numOfElements; i++)
	{
		if ((_meetPtr->start > _ptr->meetArray[i]->start && 
			_meetPtr->start < _ptr->meetArray[i]->end) ||
		(_meetPtr->end > _ptr->meetArray[i]->start && 
			_meetPtr->end < _ptr->meetArray[i]->end))
		{
			return FAULT;
		}
		else
		{
			return SUCCESS;
		}
	}
}

errors Insert (diary *_diary, meet *_meet)
{
meet **temp;

	if(_diary == NULL || _meet == NULL)
	{
		return NULL_ERROR;
	}
	
	if(OverlapCheck(_diary, _meet) == OVERLAP)
	{
		return OVERLAP;
	}

	if((_diary -> numOfElements) >= (_diary -> dArraySize))
	{
		if(_diary -> dArrayBlockSize == 0)
		{
			return OVERFLOW;
		}
		
		temp = (meet**)realloc(_diary -> meetArray, (_diary -> dArraySize + _diary -> dArrayBlockSize) * sizeof(meet*));
		if(temp == NULL)
		{
			return NULL_ERROR;
		}
				
		_diary -> meetArray = temp;
		_diary -> dArraySize = _diary -> dArraySize + _diary -> dArrayBlockSize;	
	}
			
	_diary -> meetArray [_diary -> numOfElements] = _meet;
	_diary -> numOfElements++;
	
	SortArray (_diary);
	return SUCCESS;		
}


void SortArray (diary *_diary)
{
int index;
meet *hold;

	for (index = _diary -> numOfElements -1; index >  0 ; index--)
        {
               if((_diary -> meetArray [index] -> start) < (_diary -> meetArray [index - 1] -> start))
                {
                    hold = (_diary -> meetArray [index]);
                   (_diary -> meetArray [index]) = (_diary -> meetArray [index - 1] );
                   (_diary -> meetArray [index - 1] ) = hold;
                }
        }
}

errors OverlapCheck(diary *_diary, meet *_meet)
{
int i;

	for (i = 0; i < _diary -> numOfElements; i++)
	{
		if(
		((_meet -> start) > (_diary -> meetArray [i] -> start) && (_meet -> start) < (_diary -> meetArray [i] -> end)) ||
		((_meet -> end) > (_diary -> meetArray [i] -> start) && (_meet -> end) < (_diary -> meetArray [i] -> end))
		)
		{
			return OVERLAP;
		}
	}
	
return NO_OVERLAP;
}
int SearchMeet(diary* _ptr, float _start)
{
	int mid, low = 0, high = _ptr->numOfElements;
	while (low <= high) 
	{
    		mid = low + (high - low) / 2;

    		if (_ptr->meetArray[mid]->start == _start)
    		{
      			return mid;
		}
    		if (_ptr->meetArray[mid]->start < _start)
    		{
	        	low = mid + 1;
	        }
	        else
	        {
	        	high = mid - 1;
	        }
	        
  	}

  return -1;
}
int RemoveMeet(diary* _ptr, float _start) 
{
	int i, meetIndex;
	meet* meetPtr;
	meetIndex = SearchMeet(_ptr, _start);
	 if (meetIndex == FAULT)
	 {
   	 return FAULT;
   	 }
  	else
	for(i = meetIndex; i < _ptr->numOfElements; i++)
	{
		_ptr->meetArray[i] = _ptr->meetArray[i + 1];
	}
	_ptr->numOfElements--;
	return SUCCESS;
}

int PrintDiary(diary* _ptr)
{
	int i;
	for(i = 0; i < _ptr->numOfElements; i++)
	{
		printf("%2.2f\n", _ptr->meetArray[i]->start);
		printf("%2.2f\n", _ptr->meetArray[i]->end);
		printf("%d\n", _ptr->meetArray[i]->room);
		putchar('\n');
	} 
	return SUCCESS;
}

errors SaveDiary(diary* _diary, char _fileName[])
{
	int i;
	FILE* cfPtr;
	if(_diary == NULL || _fileName == NULL)
	{
		return NULL_ERROR;
	}
	if (( cfPtr = fopen( _fileName, "w" ) ) == NULL )
	{
		printf( "File could not be opened\n" );
		return NULL_ERROR;
	}
	fprintf( cfPtr,"%d\n", _diary->numOfElements);
	for(i = 0; i < _diary->numOfElements; i++)
	{
		fprintf( cfPtr, "%.2f\n%.2f\n%d\n",_diary->meetArray[i]->start, _diary->meetArray[i]->end, _diary->meetArray[i]->room);
	}
	fclose(cfPtr );
}	

errors LoadDiary(diary* _diary, char _fileName[])
{
	
	meet* meet;
	int i, num,room;
	float start, end;
	FILE* cfPtr;
	if(_diary == NULL)
	{
		return NULL_ERROR;
	}
	cfPtr = fopen(_fileName, "r");
	if(cfPtr == NULL)
	{
		return NULL_ERROR;
	}
   	fscanf(cfPtr,"%d", &num);
   	for (i = 0; i < _diary->numOfElements; i++)
   	{
   		free(_diary->meetArray[i]);
   	}
   	_diary->numOfElements = 0;
   	for(i = 0; i < num; i++)
	{
		fscanf(cfPtr,"%f%f%d", &start, &end, &room);
		meet = CreateMeet(start, end, room);
		Insert(_diary, meet);
	}	
   	fclose(cfPtr);

}
float GetStart(meet *_meet)
{
	return  _meet -> start;
}
float GetEnd(meet *_meet)
{
	return  _meet -> end;
}
int GetRoom(meet *_meet)
{
	return _meet -> room;
}
meet* GetMeetPointer(diary *_diary, int i)
{
	return _diary -> meetArray [i];
}
int GetSize(diary *_diary)
{
	return _diary -> dArraySize;
}
int Increase(diary *_diary)
{
	return _diary -> dArrayBlockSize;
}
int NumberOfMeetings(diary *_diary)
{
	return _diary -> numOfElements;
}
int GetMeetRoom(diary *_diary, int i)
{
	return _diary -> meetArray [i] -> room;
}











