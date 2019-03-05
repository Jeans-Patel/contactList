#include "header.h"

int main(int argc, char ** argv)
{
	FILE * fp = fopen("myContactList.db", "ab");
	

	if (fp == NULL)
	{
		printf("There was an error with the file,\n");
		exit(1);
	}

	void userinput();


	fclose(fp);
	return 0;
}