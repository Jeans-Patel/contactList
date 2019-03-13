#include "header.h"

int main(int argc, char ** argv)
{
    /* Declaring variable */
    int check = 1;
    
    /* Opens the file if it exists or makes it if it doesn't */
    FILE * fp = fopen("myContactList.db", "ab+");

    /* If there's an error it prints and error message and closes the program */
    if (fp == NULL)
    {
        printf("There was an error with the file,\n");
        exit(1);
    }

    /* Keeps asking the user if they want to make a new contact
    or search for a contact until the say No to both */
    while (check != 0)
    {
        userInput(fp);
        check = userRead(fp);
    }
    
    /* Closes the file */
    fclose(fp);
    
    return 0;
}