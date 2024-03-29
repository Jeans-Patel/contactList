#ifndef __HEADERH__
#define __HEADERH__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct contact {
    unsigned long phone_number;
    long first_name_posn;
    long last_name_posn;
    long company_name_posn;
    long email_posn;
    long next;
};

typedef struct contact contact;

void userInput(FILE * fp);
int userRead(FILE * fp);
#endif