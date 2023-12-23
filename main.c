#include"./head.h"
int main(void)
{
	char* p = NULL;

	p = arabic2Chinese("1024567");
	printf("%s\n", p);

	//char num[13] = { 0 };
	//int start = 1600008000;
	//for (int i = start; i <= start + 3000; i++)
	//{
	//	sprintf(num, "%d", i);
	//	p = arabic2Chinese(num);
	//	printf("%s\n", p);
	//}
	return 0;
}