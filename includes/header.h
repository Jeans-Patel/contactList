#ifndef __HEADERH__
#define __HEADERH__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contact {
	unsigned long phone_number;
	long first_name_posn;
	long last_name_posn;
	long company_name_posn;
	long email_posn;
	long next;
};

typedef struct contactdata {
	char * fn;
	char * ln;
	char * cn;
	char * pn;
	char * e;
} contactdata;

typedef struct contact contact;

void userinput(FILE * fp);
#endif