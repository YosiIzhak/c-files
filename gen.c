#include<stdio.h>
#include <string.h>
#include <stdlib.h> 

typedef int(*sortCrit)(void*, void*);
struct Person
{
	int m_id;
	char m_name[120];
	int m_age;
};

int Cmp_int(void* vp1, void* vp2)
{
	return *(int*)vp1 - *(int*)vp2;
}
int Cmp_ch(void* vp1, void* vp2)
{
	return *(char*)vp1 - *(char*)vp2;
}
/*int Cmp_personId(void* vp1, void* vp2)
{
	return *(struct Person*)vp1 - *(struct Person*)vp2;
}
*/
void BubbleSort(void* arr, int len, int elemsize, sortCrit cmp)
{
	 int flag,i, j;
	void* base;
	void* base_next;
	for (i = 0; i < len - 1; i++)
	{
		flag = 0;
		for (j = 0; j < len - i - 1; j++)
		{
			base = (char*)arr + j * elemsize;
			base_next = (char*)arr + (j + 1) * elemsize;
			if (cmp(base, base_next) > 0)
			{
				void* tmp = malloc(elemsize);
				memcpy(tmp, base, elemsize);
				memcpy(base, base_next, elemsize);
				memcpy(base_next, tmp, elemsize);
				free(tmp);
				flag = 1;
			}
		}
		 if (flag == 0) break; 
	}
}
    
int main()
{

struct Person pArr[5] = {
{1, "yosi", 2}, {3, "avi", 4}, {4,"gali",6}, {5,"gal",6}, {4,"sofi",7}
};
	char crr[] = { 'c','e','d','a','b' };
	int i, arr[] = { 1,5,7,0,9,12,34,6,8,10 };
	BubbleSort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), Cmp_int);
	for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d  ", arr[i]);
	}
	printf("\n"); 

	BubbleSort(crr, sizeof(crr) / sizeof(crr[0]), sizeof(char), Cmp_ch);
	for (i = 0; i < sizeof(crr) / sizeof(crr[0]); i++)
	{
		printf("%c  ", crr[i]);
	}
	printf("\n");	
	  
}  
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 0
#define NO 0
#define SUCCESS 1
#define YES 1
#define SIZE_OF_ARR 10

static void GenSwap(void * _e1, void * _e2, size_t _sizeOfElement, void * _temp);

int GenSort(void * _data, size_t _numOfElements, size_t _sizeOfElement, int(*_SortCri)(const void * _e1, const void * _e2))
{
	size_t index, j;
	int flag = 0;
	void *temp = (void*)malloc(_sizeOfElement);
	if(temp == NULL)
	{
		return ERROR;
	}
	for(j = 0; j < _numOfElements - 1; j++)
	{
		flag = 0;
		for(index = 0; index < _numOfElements - 1 - j; index++)
		{
			if(_SortCri((void*)((char*)_data + index*_sizeOfElement),(void*)((char*)_data + (index+1)*_sizeOfElement)))
			{
				GenSwap((void*)((char*)_data + index*_sizeOfElement),(void*)((char*)_data + (index+1)*_sizeOfElement), _sizeOfElement, temp);
				flag = 1;
			}
		}
		if(flag == 0)
		{
			break;
		}
	}
	free(temp);
	return SUCCESS;
}


static void GenSwap(void * _e1, void * _e2, size_t _sizeOfElement, void * _temp)
{
	memcpy(_temp, _e1, _sizeOfElement);
	memcpy(_e1, _e2, _sizeOfElement);
	memcpy(_e2, _temp, _sizeOfElement);
}

/**********************************************************************************************/

int IsBigger(const void * _e1, const void * _e2)
{
	if(*(int*)_e1 <= *(int*)_e2)
	{
		return NO;
	}
	return YES;
}
/**********************************************************************************************/

int StudentSortById(const void * _p1, const void * _p2)
{
	if(((student*)_p1)-> id <= ((student*)_p2)-> id)
	{
		return NO;
	}
	return YES;
}


/**********************************************************************************************/

/*stracture type student*/
typedef struct student
{
	char name[30];
	long id;
	int age;
	int grade;
} student;



int main(void)
{
	int i = 0; 
	int intArr[SIZE_OF_ARR] = {9,8,7,6,5,4,3,2,1,0};
	int size;
	/*initial students data in the student struct*/
	student stData[SIZE_OF_ARR];
	/*st1*/
	strcpy(stData[0].name , "Amir");
	stData[0].id = 9;
	stData[0].age = 21;
	stData[0].grade = 90;
	/*st2*/
	strcpy(stData[1].name , "Yoav");
	stData[1].id = 8;
	stData[1].age = 23;
	stData[1].grade = 95;
	/*st3*/
	strcpy(stData[2].name , "Amit");
	stData[2].id = 7;
	stData[2].age = 54;
	stData[2].grade = 88;
	/*st4*/
	strcpy(stData[3].name , "Ran");
	stData[3].id = 6;
	stData[3].age = 24;
	stData[3].grade = 94;
	/*st5*/
	strcpy(stData[4].name , "Almog");
	stData[4].id = 5;
	stData[4].age = 27;
	stData[4].grade = 92;
		/*st1*/
	strcpy(stData[5].name , "Amir");
	stData[5].id = 4;
	stData[5].age = 21;
	stData[5].grade = 90;
	/*st2*/
	strcpy(stData[6].name , "Yoav");
	stData[6].id = 3;
	stData[6].age = 23;
	stData[6].grade = 95;
	/*st3*/
	strcpy(stData[7].name , "Amit");
	stData[7].id = 2;
	stData[7].age = 54;
	stData[7].grade = 88;
	/*st4*/
	strcpy(stData[8].name , "Ran");
	stData[8].id = 1;
	stData[8].age = 24;
	stData[8].grade = 94;
	/*st5*/
	strcpy(stData[9].name , "Almog");
	stData[9].id = 0;
	stData[9].age = 27;
	stData[9].grade = 92;
	
	/*size of stData*/
	size = sizeof(stData)/sizeof(stData[SIZE_OF_ARR]);
	GenSort(stData, SIZE_OF_ARR, sizeof(student), StudentSortById);
	/*printing data before sort*/
	printStructStudent(stData, size);
	printf("\n");
	

	GenSort(intArr, SIZE_OF_ARR, sizeof(int), IsBigger);
	printf("\n");
	for(i; i < SIZE_OF_ARR; i++)
	{
		printf("%d, ", intArr[i]);
	}
	printf("\n");
	return SUCCESS;
}
/**********************************************************************************************/



/*print func to print all the student data from student structure*/ 
int printStructStudent(struct student *students_data, int size)
{
	int st_num;
	if(students_data == NULL)
	{	
		return ERROR;
	}
	for(st_num = 0; st_num < size; st_num++)
	{
		printf("student name: %s\nstudent id: %ld\nstudent age: %d\nstudent grade: %d\n\n", students_data[st_num].name, students_data[st_num].id, students_data[st_num].age, students_data[st_num].grade);
	}
	return SUCCESS;
}
    
