#include "header.h"

int main()
{
	FILE * fp = fopen("myContactList.db", "ab");
	/*openfile(argc);*/

	if (fp == NULL)
	{
		printf("There was an error with the file,\n");
		exit(1);
	}

	return 0;
}