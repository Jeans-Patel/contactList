#include "header.h"

int main(int argc, char ** argv)
{
	FILE * fp = fopen("myContactList.db", "ab+");
	printf("PINEAPPLES\n");

	if (fp == NULL)
	{
		printf("There was an error with the file,\n");
		exit(1);
	}

	userinput(fp);
	/*
	char string[5] = "hi";
	printf("size of int: %ld\n", sizeof(int));
	printf("size of long: %ld\n", sizeof(long int));
	printf("size of char: %ld\n", sizeof(char));
	printf("size of string: %ld\n", sizeof(string));
	*/
	
	fclose(fp);
	return 0;
}