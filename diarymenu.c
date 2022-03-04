#include <stdio.h>
#include <stdlib.h>
#include "diary.h"

void menu();
void mainMenu();
void optionsMenu();
void options(diary* diary);
void allOptionsMenu(void);
meet* allMenu(diary* diary);
int choice2 = 0;
int choice3 = 0;
int choice1 = 0;
void mainMenu(void)
{
    printf("Main Menu\n");
    printf( "1 - create diary\n");
    printf("2 - Quit\n");
    printf( "Please choose: ");
    scanf("%d", &choice1);
}
 
void optionsMenu(void) 
{
    printf("Options Menu\n");
    printf("1 - insert meet\n");
    printf("2 - Quit\n");
    printf("Please choose: ");
    scanf("%d",&choice2);
}
void allOptionsMenu(void) 
{
    printf("All Options Menu\n");
    printf("1 - create meet\n");
    printf("2 - remove meet\n");
    printf("3 -  Check if meet exists\n");
    printf("4 - Print all the meets\n");
    printf("5 - Save to file\n");
    printf("6 - read from file\n");
    printf("7 - Quit\n");
    printf("Please choose: ");
    scanf("%d",&choice3);
}
void options(diary* diary)
{
	
    	float start, end;
	int room;
	meet *meet;
	errors insert;
    do {
        optionsMenu();

        switch(choice2)
        {

            case 1:
             printf("Enter start time:\n");
	     scanf("%f", &start);
	     printf("Enter end time:\n");
		scanf("%f", &end);
		printf("Enter room number:\n");
		scanf("%d", &room);
		meet = CreateMeet(start, end, room);
		if(meet == NULL)
		{
			printf("\n");
			printf("Invalid times, try again.\n");
			options(diary);
		}
		insert = Insert(diary, meet);
		if(insert == OVERLAP)
		{
			printf("\n");
			printf("overlap error.\n");
			allMenu(diary);
		}
                allMenu(diary);
                break;

            case 2: 
               Destroy(diary);
		printf("Your diary has been destroyed. see you soon.\n");
                break;

            default: 
            printf("Invalid choice! try again.\n ");
                break;

        }

    } while(choice2 != 2);


}
meet* allMenu(diary* diary)
{
	char fileName[25];
	float start, end;
	int room;
	meet *meet;
	errors insert, Remove, IsExists ;
	
    	do {
        allOptionsMenu();

        switch(choice3)
        {

            case 1:
            	printf("\n");
		printf("Enter start time:\n");
		scanf("%f", &start);
		printf("Enter end time:\n");
		scanf("%f", &end);
		printf("Enter room number:\n");
		scanf("%d", &room);
		meet = CreateMeet(start, end, room);
		if(meet == NULL)
		{
			printf("\n");
			printf("Invalid times, try again.\n");
		       allMenu(diary);
			break;
		}
		insert = Insert(diary, meet);
		if(insert == OVERLAP)
		{
			printf("try other hours.\n");
			allMenu(diary);
			break;		
		}
		if(insert == OVERFLOW)
		{
			printf("The place in diary is run out.\n");
			allMenu(diary);
			break;		
		}
		printf("Your meeting created and entered in the diary.\n");		allMenu(diary);
		break;
	   case 2:
		printf("Enter the begin time of the meeting you want to delete.\n");
		printf("\n");
		scanf("%f", &start);
		Remove = RemoveMeet(diary, start);
		if(Remove == UNDERFLOW)
		{
		   	printf("\n");
			printf("The diary is empty there is nothing to delete.");
			allMenu(diary);
			break;
		}
		if(Remove == NOT_EXIST)
		{
			printf("try again with other hour");
			allMenu(diary);
			break;
		}
		if(Remove == SUCCESS)
		{
			printf("The meeting has been deleted!\n");
			allMenu(diary);
			break;
		}
		break;
		case 3:
		printf("\n");
		printf("Enter the begin time of the meeting you want to find.\n");
		scanf("%f", &start);
		IsExists = SearchMeet(diary, start);
		if(IsExists == EXIST)
		{
			printf("find it\n");
			allMenu(diary);
			break;
		}
		if(IsExists == NOT_EXIST)
		{
			printf("don't find a meet.\n");
			allMenu(diary);
			break;
		}
		break;
		case 4:
			PrintDiary(diary);
			allMenu(diary);
			break;
		case 5:
			printf("please enter file name.\n ");
			scanf("%s", fileName);
			SaveDiary(diary, fileName);
			break;
		case 6:
			printf("please enter file name.\n ");
			scanf("%s", fileName);
			LoadDiary(diary, fileName);
			Insert(diary, meet);
			break;
		case 7:
			Destroy(diary);
			printf("the diary has been destroyed.\n");
			break;
				
		default:
			printf("\n");
			printf("Invalid choice! try again.\n ");
			options(diary);
			break;
		}
	} while(choice3 != 7);
}
void menu()
{
	
	diary *ptr;
        int size, increase;
        do 
        {
        	choice1 = 0;
        	mainMenu();

        	switch(choice1)
        	{

            	case 1:
                printf("Enter the number of meetings you want to insert:\n");
			scanf("%d", &size);
			printf("\n");
			printf("how many meets do you want to increase it ?\n");
			scanf("%d", &increase);
			ptr = CreateDiary(size, increase);
			if(ptr == NULL)
			{
				printf("\n");
				printf("Something went wrong. Try again.\n");
				break;
			}
			printf("\n");
			printf("Your diary created.\n");
			options(ptr);
	   	break;
            	case 2:
               printf("see you soon.\n");
                break;

            	default:
            	printf("try again.\n ");
                break;

       	}

   	 } while(choice1 != 2);
}

int main(int argc, char** argv)
{

    menu();

   return 0;
}

