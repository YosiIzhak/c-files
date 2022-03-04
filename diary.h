typedef struct diaryArray diary;
typedef struct meet meet;


typedef enum {NULL_ERROR, OVERFLOW, SIZE_ERROR, SUCCESS, FAULT, OVERLAP, NO_OVERLAP, NOT_EXIST, UNDERFLOW, EXIST} errors;
#define MAGIC_NUMBER 942199

/* this function create a diary. she get the initial size and the increase size and return pointer to diary the size must be positive and the increase size can't be negative. she allocate the memory of diary.
include the memory of the arrY OF meeting.*/
diary *CreateDiary( int size, int blockSize);
/* this function create a meet. she get the start hour, end hour and room. the end must be bigger than start. they both must be in range 0-23.99.she return pointer to meet. she allocate the memory of meet.*/
meet *CreateMeet(float start, float end, int room);
/* this function destry a diary. she get the pointer to the diary,
and free the memory allocation of the diary and the inner array */
int Destroy(diary *ptr);
/*this function check the hours of meet. if there is overlap with another meet, the meet isn't valid. she get pointers to the diary and to the meet. she return SUCCESS or FAULT.*/
int CheckValidMeet (diary* ptr, meet* meetPtr);
/* this function insert a meet to the diary and allocate more memory if needed. she get pointers to the diary and to the meet. she return SUCCESS or another messege. */
errors Insert (diary *_diary, meet *_meet);
/* this function search a meet in the diary and return the index if it's exist and -1 if not. the search made by the start hour. */
int SearchMeet(diary* ptr, float start);
/* this function delete a meet in the diary and return SUCCESS if it's deleted.if it isn't exist the function return a. the search made by the start hour. */
int RemoveMeet(diary* ptr, float start);
/* this function print all the meets in the diary*/
int PrintDiary(diary* ptr);
/*this is help function to check if there is overlap beetwen two meets*/
errors OverlapCheck(diary *_diary, meet *_meet);
/* this function sort the array of meets. the sort made by start hour*/
void SortArray (diary *_diary);

struct meet {
int room;
float start;
float end;

} ;

struct diaryArray {
meet **meetArray;
int dArraySize;
int dArrayBlockSize;
int numOfElements;
int m_magicNumber;
} ;
