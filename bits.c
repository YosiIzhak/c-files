#include<stdio.h>
#include<string.h>
unsigned char CheckBit(unsigned char _byte, int _N)
{
	unsigned char test;
	test = _byte&(1<<_N);
	return test;
}

int CountBits(unsigned char _byte)
{
	int count = 0;
	
	while (_byte)
	{
		count+= _byte & 1;
		_byte >>= 1;
	} 
	return count;
}
int CountBitsInt(unsigned int _num)
{
	int count = 0;
	
	while (_num)
	{
		count+= _num & 1;
		_num >>= 1;
	} 
	return count;
}
unsigned char InvertBits(unsigned char _num)
{
	unsigned i = 8;
	unsigned char res = _num;
	res ^= (255);
	
    for (i = 1 << (i - 1); i > 0; i = i / 2)
    {
    	(res & i) ? printf("1") : printf("0");
    }
    putchar('\n');
	return res;
}
unsigned char RotateBits(unsigned char _byte, int _num)
{
	int i, size = 8, j = 8;
	unsigned char res = _byte;
	unsigned char temp = 0;
	for (i = _num - 1; i >= 0; i--)
	{
		temp += res & (1 << i); 
		1 << temp;
	}
	_byte >>= _num;
	temp <<= (size - _num);
	res = _byte | temp;
	for (j = 1 << (j - 1); j > 0; j = j / 2)
    	{
    		(res & j) ? printf("1") : printf("0");
    	}
    		
	return res;
}
	
int Compress (unsigned char* _str)
{
	int first = 0, second = 0, i = 0, j = 0 , z = 8;
	if(_str == NULL)
	{
		return 0;
	}
	while (_str[i] != '\0')
    	{
        	first = _str[i] -'a' + 1; 
        	first <<= 4;
        	i++;
        	/* if str length is odd*/
        	if (_str[i] != '\0')
        	{
        		second = _str[i] -'a' + 1; 
        		_str[j] = first | second;
        	}
        	else
        	{
        		break;
        	}
        	second = 0;
        	printf("%d\n", _str[j]);
        	j++; 
        	i++;
         	
        }
      /*j++; 
      _str[j] = '\0';*/
}

void CheckMemory()
{
	char* ptr;
	int i = 1;	
	ptr =(char*)&i;
	if (*ptr)
	{
		printf ("LE\n");
	}
}
int main()
{
 	/*printf("%u\n", CheckBit(8, 3));
 	printf("%d\n", CountBits(17));
 	printf("%d\n", CountBitsInt(17555555));
 	InvertBits(255);
 	RotateBits(7, 4);
 	unsigned char arr[] = "abcabc";
 	Compress(arr);*/
 	CheckMemory();
 	return -1;
} 
