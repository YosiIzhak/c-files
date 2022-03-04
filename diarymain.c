#include <stdio.h>
#include <stdlib.h>
#include "diary.h"
errors OverlapCheck(diary *_diary, meet *_meet);
meet* GetMeetPointer(diary *_diary, int i);
errors InsertMeeting (diary *_diary, meet *_meet);
void SortArray (diary *_diary);
void CreateDiaryIsTwoZerosGiveNull(void)
{
	diary *ptr;
	ptr = CreateDiary(0, 0);
	if(ptr == NULL)
	{
		printf("CreateAd test - Is two zero give NULL          - PASS! \n");	
	}
	if(ptr != NULL)
	{
		printf("QueueCreate test - Is two zero give NULL        - FAILS! \n");	
	}
	Destroy (ptr);	
}
void CreateDiaryCheckParameters(void)
{
	diary *ptr;
	ptr = CreateDiary(10, 2);
	if(GetSize(ptr) == 10 && Increase(ptr) == 2 && NumberOfMeetings(ptr) == 0)
	{
		printf("CreateAd test - Check parameters               - PASS! \n");	
	}
	else
	{
		printf("CreateAd test - Check parameters               - FAILS! \n");	
	}

Destroy (ptr);	
}
void CreateMeetingCheckParameters(void)
{

	meet *ptr;
	ptr = CreateMeet(3.16, 4.18, 5);
	if((GetStart(ptr) - 3.16 < 0.1 || 3.16- GetStart(ptr) < 0.1) && (GetEnd(ptr) - 4.18 < 0.1 || 4.18 - GetEnd(ptr) < 0.1) && GetRoom(ptr) == 5)
	{
		printf("CreateMeeting test - Check parameters                  - PASS! \n");	
	}
	else
	{
		printf("CreateMeeting test - Check parameters                  - FAILS! \n");	
	}
	free(ptr);
}
void IsRoomEnterTheArray(void)
{	
	diary *ptr;
	meet *meet;
	ptr = CreateDiary(10, 2);
	meet = CreateMeet(3.16, 4.18, 5);
	Insert (ptr, meet);
	
	if(GetMeetRoom(ptr,0) == 5)
	{
		printf("InsertMeeting test - Is room enter the array         - PASS! \n");	
	}
	else
	{
		printf("InsertMeeting test - Is room enter the array        - FAILS! \n");	
	}
	
	Destroy (ptr);	
}
void IsMeetEnterTheArray(void)
{
	diary *ptr;
	meet *meet;
	ptr = CreateDiary(10, 2);
	meet = CreateMeet(3, 4, 5);
	Insert (ptr, meet);
	
	if(meet == GetMeetPointer(ptr, 0) )
	{
		printf("InsertMeeting test - Is meet pointer enter the array - PASS! \n");	
	}
	else
	{
		printf("InsertMeeting test - Is meet pointer enter the array - FAILS! \n");	
	}
	
	Destroy (ptr);	
}
void IsOverlapErrWork(void)
{	
	diary *ptr;
	meet *meet;
	ptr = CreateDiary(10, 2);
	meet = CreateMeet(3.16, 4.18, 5);
	Insert (ptr, meet);
	meet = CreateMeet(4.02, 6, 10);
	Insert (ptr, meet);
	
	
	if(Insert (ptr, meet) == OVERLAP)
	{
		printf("InsertMeeting test - Is overlap err work             - PASS! \n");	
	}
	else
	{
		printf("InsertMeeting test - Is overlap err work            - FAILS! \n");	
	}
	
Destroy (ptr);	
}
void IsSortWork(void)
{	
	diary *ptr;
	meet *meet;
	ptr = CreateDiary(10, 2);
	meet = CreateMeet(3.16, 4.18, 3);
	Insert (ptr, meet);
	meet = CreateMeet(2.2, 3, 2);
	Insert (ptr, meet);
	meet = CreateMeet(1.2, 2.1, 1);
	Insert (ptr, meet);
	
	
	if(GetMeetRoom(ptr,0) == 1 &&  GetMeetRoom (ptr,1) == 2 && GetMeetRoom (ptr,2) == 3)
	{
		printf("InsertMeeting test - Is sort work                    - PASS! \n");	
	}
	else
	{
		printf("InsertMeeting test - Is sort work                   - FAILS! \n");	
	}
	
Destroy (ptr);	
}

int main()
{

	CreateDiaryIsTwoZerosGiveNull();
	CreateDiaryCheckParameters();
	CreateMeetingCheckParameters();
	IsRoomEnterTheArray();
	IsMeetEnterTheArray();
	IsOverlapErrWork();
	IsSortWork();
}
