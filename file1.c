#include<stdio.h>
#include <string.h>
struct Person
{
	int m_id;
	char m_name[120];
	int m_age;
};
struct Person pArr[5] = {
{1, "yosi", 2}, {3, "avi", 4}, {4,"gali",6}, {5,"gal",6}, {4,"sofi",7}
};

void WriteToBin(char _fileName[])
{
	
	struct Person pArr2[5]; 
	size_t size, count;
	FILE* ptr1;
	ptr1 = fopen(_fileName , "w" );
	if (ptr1 == NULL)
	{
		return;
	}
	size = sizeof(struct Person);
	count = sizeof(pArr)/ sizeof(pArr[0]);
	fwrite (pArr, size, count, ptr1);
	fclose(ptr1);
	ptr1 = fopen(_fileName , "r" );
	if (ptr1 == NULL)
	{
		return;
	}
	fread(pArr2, size, count, ptr1);
	printf("%d %s %d", pArr2[3].m_id, pArr2[3].m_name, pArr2[3].m_age);
	fclose(ptr1);
}
int CountLetters(char _fileName[])
{
	int A[53] = {0}, c;

    FILE *ptr = fopen(_fileName, "r");
    if (ptr == NULL)
    {
       return -1;
    }

    while((c = fgetc(ptr)) != EOF)
    {
        if ( c >= 'a' && c <= 'z' )
        {
            c-='a'; 
            A[c + 26]++;
        }
        else if ( c >= 'A' && c <= 'Z' )
        {
            c-='A';
            A[c]++;
        }
        else if (c == '\n')
        {
             continue;
        }
       
    }
    for (c = 0; c < 'Z' - 'A' + 1; c++)
    {
            printf("%c: %d\n", c+'A', A[c]);
    } 
    for (c = 0; c < 'Z' - 'A' + 1; c++)
    {
            printf("%c: %d\n", c+'a', A[c+26]);
    } 
    fclose(ptr);
    return 0;
}

void fileCount(char _fileName[])
{
	FILE* chPtr;
	char curr; 
	int in_word = 0;
	int charCount = 0, wordCount = 0, lineCount = 0;
	chPtr = fopen(_fileName , "r" );
	if (chPtr == NULL)
	{
		return;
	}
	
	
	while ((curr = fgetc(chPtr))!= EOF)
	{
		charCount++;
		if (curr == ' ' || curr == '\n')
		{
			if (in_word)
			{
        			in_word = 0;
				wordCount++;
			}
			if (curr == '\n')
			{
			lineCount++;
			}
		}
		else
		{
			 in_word = 1;
		}
	}
	fclose(chPtr );
	
	printf("%d\n",charCount);
	printf("%d\n",wordCount);
	printf("%d\n",lineCount);
	return; 
}
void myTail(char _fileName[], int linesNum)
{
	int i, pos, count;
	FILE* chPtr;
	char str[150];
	chPtr = fopen(_fileName , "r" );
	if (chPtr == NULL)
	{
		return;
	}
	fseek(chPtr,0, SEEK_END); 
	pos = ftell(chPtr);
	
	for (i = pos; i > 0; i++)
	{
		if(fgetc(chPtr) == '\n')
		{
			count++;
		}
		if(count == linesNum)
		{
			break;
		}
		fseek(chPtr, -2, SEEK_CUR);
	}
	fgets(str, 150, chPtr);
	while (!feof(chPtr))
	{
		printf("%s", str);
		fgets(str, 150, chPtr);
	} 
	fclose(chPtr );
}
void CompareFiles(char _fileName1[], char _fileName2[])
{
	int i, line = 1;
	FILE* ptr1; FILE* ptr2;
	char str1[150], str2[150]; 
	ptr1 = fopen(_fileName1 , "r" );
	if (ptr1 == NULL)
	{
		return;
	}
	ptr2 = fopen(_fileName2 , "r" );
	if (ptr2 == NULL)
	{
		return;
	}
	while (!feof(ptr1) || !feof(ptr2))
	{
		fgets(str1, 150, ptr1);
		fgets(str2, 150, ptr2);
		if (strcmp(str1, str2) != 0)
		{
			printf("%d\n", line);
		}
		line++;
	} 
	fclose(ptr1 );
	fclose(ptr2 );
}
void CountWord(char _fileName[])
{
	int count = 0, i, line = 1;
	FILE* ptr1; FILE* ptr2;
	char str1[15], str2[15], str3[15]; 
	ptr1 = fopen(_fileName , "r" );
	if (ptr1 == NULL)
	{
		return;
	}
	fscanf(ptr1, "%s%s", str1, str2);
	ptr2 = fopen(str1 , "r" );
	if (ptr2 == NULL)
	{
		return;
	}
	while (!feof(ptr2))
	{
		fscanf(ptr2, "%s", str3);
		if (strcmp(str2, str3) == 0)
		{
			count++;
		}
	}
	printf("In file %s the word %s appeared %d times", str1, str2, count);
	fclose(ptr1 );
	fclose(ptr2 );
}

int main()
{
	/*fileCount("diary.h");
	myTail("diary.h",10);
	CompareFiles("enum.h","enum1.h");
	CountWord("somefile.txt");
	WriteToBin("person");*/
	CountLetters("sometext.txt");
}
   	
   	
