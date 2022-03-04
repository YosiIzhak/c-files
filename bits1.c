#include <stdio.h>
#include <stdlib.h>

#define INT_LENGTH 32
#define TRUE 1
#define FALSE 0

int CheckSign(int _num)
{
	int sign;
	_num >>= INT_LENGTH -1;
	sign = _num& 1;
	return sign^=(1 << 0);
	
}

int CompareInts(int _x, int _y)
{
	int pos2;
	int res = _x - _y;
	int pos = CheckSign(res);
	pos2 ^= pos;
	return (pos*_x +pos2*_y);
}
int main()
{
	printf("%d\n ", CheckSign(200));
	printf("%d\n ", CompareInts(200, 300));
}
