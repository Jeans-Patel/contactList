#include "header.h"

int main(int argc, char ** argv)
{
	FILE * fp = openfile(argc);

	if (fp == NULL)
	{
		printf("There was an error with the file,\n");
		exit(1);
	}

	return 0;
}