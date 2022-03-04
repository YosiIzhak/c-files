#include <stdio.h>
#include <stdlib.h>
#define CHAR_OPTIONS 256
#define CHAR_LENGTH 8
#define INT_LENGTH 32


int CountBitsChar(unsigned char _num)
{
	int count = 0;
	
	while (_num)
	{
		count+= _num & 1;
		_num >>= 1;
	} 
	return count;
}
static void BuildLUT(char* table)
{
	int i =0;
	for(i = 0; i < CHAR_OPTIONS; i++)
	{
		table[i] = CountBitsChar(i);
	}
}

int countBitInChar(unsigned char _num, char* table)
{
	return table[_num];
}
int countBitInInt(unsigned int _num, char* table)
{
	int count = 0;
	unsigned char temp;
	while (_num)
	{
		temp = _num & 0xff;
		count += countBitInChar(temp, table);
		_num >>= 8;
	} 
	return count;
}
/**********************************************************/
int ReverseBitsChar(unsigned char _num)
{
	int i, rev = 0;
	
	for (i = 0; i < CHAR_LENGTH; i++)
	{
		rev <<= 1;
		rev+= _num & 1;
		_num >>= 1;
		
	} 
	return rev;
}
static void BuildReverseLUT(char* revTable)
{
	int i =0;
	for(i = 0; i < CHAR_OPTIONS; i++)
	{
		revTable[i] = ReverseBitsChar(i);
	}
}
int reverseBitInChar(unsigned char _num, char* revTable)
{
	return revTable[_num];
}
int ReverseBitInInt(unsigned int _num, char* revTable)
{
	int i, reverse = 0;
	unsigned char temp;
	for (i = 0; i < (INT_LENGTH/ CHAR_LENGTH -1); i++)
	{
		temp = _num & 0xff;
		reverse += reverseBitInChar(temp, revTable);
		_num >>= 8;
		reverse <<= 8;
	} 
	return reverse;
}
/**********************************************************/
char ReverseTwoBitsChar(unsigned char _num)
{
	int i, j;
	char rev = 0;
	char revTwo[4] = {0};
	for (i = 0; i < CHAR_LENGTH / 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			revTwo[i] <<= 1;
			revTwo[i]+= _num & 1;
			_num >>= 1;
		}
	} 
	for (j = 3; j >= 0; j--)
	{
		rev <<= 2;
		rev += revTwo[j];
	}
	return rev;
}
static void BuildReverseTwoLUT(char* revTwoTable)
{
	int i =0;
	for(i = 0; i < CHAR_OPTIONS; i++)
	{
		revTwoTable[i] = ReverseTwoBitsChar(i);
	}
}
int reverseTwoBitInChar(unsigned char _num, char* revTwoTable)
{
	return revTwoTable[_num];
}
int ReverseTwoBitInInt(unsigned int _num, char* revTwoTable)
{
	int i, j, reverse = 0;
	char revTwo[4] = {0};
	unsigned char temp;
	for (i = 0; i < (INT_LENGTH/ CHAR_LENGTH); i++)
	{
		temp = _num & 0xff;
		revTwo[i] = reverseTwoBitInChar(temp, revTwoTable);
		_num >>= 8;
	} 
	for (j = 3; j >= 0; j--)
	{
		reverse <<= 8;
		reverse += revTwo[j];
	}
	return reverse;
}
/**********************************************************/
int offsetThirdBitChar(unsigned char _num)
{
	int offset = 0, count = 0;
	while (_num)
	{
		count+= _num & 1;
		_num >>= 1;
		offset++;
		if (count == 3)
		{
			return count;
		}
	} 
	return count;
}
static void BuildoffsetThirdBitLUT(char* offsetTable)
{
	int i =0;
	for(i = 0; i < CHAR_OPTIONS; i++)
	{
		offsetTable[i] = offsetThirdBitChar(i);
	}
}
char OffsetThirdBitInChar(unsigned char _num, char* offsetTable)
{
	return offsetTable[_num];
}
/*********/
int offsetFirstBitChar(unsigned char _num)
{
	int offset = 0, count = 0;
	while (_num)
	{
		count+= _num & 1;
		_num >>= 1;
		offset++;
		if (count == 1)
		{
			return offset;
		}
	} 
	return offset;
}
static void BuildoffsetFirstBitLUT(char* offsetFirstBitTable)
{
	int i =0;
	for(i = 0; i < CHAR_OPTIONS; i++)
	{
		offsetFirstBitTable[i] = offsetFirstBitChar(i);
	}
}
char OffsetFirstBitInCh(unsigned char _num, char* offsetFirstBitTable)
{
	return offsetFirstBitTable[_num];
}
/*********/
int offsetSecondBitChar(unsigned char _num)
{
	int offset = 0, count = 0;
	while (_num)
	{
		count+= _num & 1;
		_num >>= 1;
		offset++;
		if (count == 2)
		{
			return offset;
		}
	} 
	return offset;
}
static void BuildoffsetSecondBitLUT(char* offsetSecondBitTable)
{
	int i =0;
	for(i = 0; i < CHAR_OPTIONS; i++)
	{
		offsetSecondBitTable[i] = offsetSecondBitChar(i);
	}
}
char OffsetSecondBitInCh(unsigned char _num, char* offsetSecondBitTable)
{
	return offsetSecondBitTable[_num];
}
/********/
int offsetThirdBitCr(unsigned char _num)
{
	int offset = 0, count = 0;
	while (_num)
	{
		count+= _num & 1;
		_num >>= 1;
		offset++;
		if (count == 3)
		{
			return offset;
		}
	} 
	return offset;
}
static void BuildoffsetThirdBit(char* offsetThirdBit)
{
	int i =0;
	for(i = 0; i < CHAR_OPTIONS; i++)
	{
		offsetThirdBit[i] = offsetThirdBitCr(i);
	}
}
char OffsetThirdBitInCh(unsigned char _num, char* offsetThirdBit)
{
	return offsetThirdBit[_num];
}
/********/
int offsetThirdBitInt(unsigned int _num)
{
	static char table[CHAR_OPTIONS];
	static char revTable[CHAR_OPTIONS];
	static char revTwoTable[CHAR_OPTIONS];
	static char offsetTable[CHAR_OPTIONS];
	static char offsetFirstBitTable[CHAR_OPTIONS];
	static char offsetSecondBitTable[CHAR_OPTIONS];
	static char offsetThirdBit[CHAR_OPTIONS];
	static int flag = 0;
	int i, j, count = 0, sumOffset = -1, tempOffset = 0;
	/* sumOffset = -1 because the first index is 0*/
	unsigned char temp, tempCount;
	if (flag == 0)
	{
		BuildLUT(table);
		BuildReverseLUT(revTable);
		BuildReverseTwoLUT(revTwoTable);
		BuildoffsetThirdBitLUT(offsetTable);
		BuildoffsetThirdBit(offsetThirdBit);
		BuildoffsetSecondBitLUT(offsetSecondBitTable);
		BuildoffsetFirstBitLUT(offsetFirstBitTable);
		flag = 1;
	}
	for (i = 0; i < (INT_LENGTH/ CHAR_LENGTH); i++)
	{
		temp = _num & 0xff;
		tempCount = OffsetThirdBitInChar(temp, offsetTable);
		count += tempCount;
		if (count >= 3)
		{
			count -= tempCount;
			if (count == 0)
			{
				tempOffset = OffsetThirdBitInCh(temp, offsetThirdBit);
			}
			if (count == 1)
			{
				tempOffset =  OffsetSecondBitInCh(temp, offsetSecondBitTable);
			}
			if (count == 2)
			{
				tempOffset =  OffsetFirstBitInCh(temp, offsetFirstBitTable);
			}
			sumOffset += tempOffset;
			return sumOffset;
		}
		sumOffset += 8;
		_num >>= 8;
	} 
	return -1;
}

/**********************************************************/
int main()
{
	
	unsigned int res;
	
	
	/*res = countBitInChar(31, table);
	printf("%d\n", res);
	res = countBitInInt(259, table);
	printf("%d\n", res);
	res = ReverseBitInInt(2, revTable);
	printf("%d\n", res);
	res = ReverseTwoBitInInt(4, revTwoTable);
	printf("%d\n", res);*/
	res = offsetThirdBitInt(984968516);
	printf("%d\n", res);
	
}






