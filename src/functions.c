#include "header.h"

void userInput(FILE * fp)
{
    /* Declaring variables */
    char buffer[1002];
    int i;
    int check1 = 0;
    int length[4];
    char * fn;
    char * ln;
    char * cn;
    char * pn;
    char * e;
    contact * person;

    /* Making sure we start adding stuff to the end */
    fseek(fp, 0, SEEK_END);

    /* While loop keep running until the user enters "No\n" */
    while (1)
    {
        /* Asks the user for Yes or No */
        printf("Do you wish to enter a new contact? (Yes or No)?: ");
        fgets(buffer, 5, stdin);
        
        /* If the user enters "No\n" the while loop stops
        (no further questions are asked, goes back to main) */
        if(strcmp(buffer, "No\n") == 0)
        {
            break;
        }

        /* Dynamically allocates an instance of the struct that will
        hold the addresses and initializing them to 0 */
        person = malloc(sizeof(contact));
        person->phone_number = 0;
        person->first_name_posn = 0;
        person->last_name_posn = 0;
        person->company_name_posn = 0;
        person->email_posn = 0;
        person->next = 0;

        /* Asks for the first name */
        printf("First Name: ");
        fgets(buffer, 1002, stdin);
        /* Removes '\n' */
        strtok(buffer, "\n");
        /* Dynamically allocate a string to store the first name */
        fn = malloc(strlen(buffer)+1);
        if (strcmp(buffer, "\n") == 0)
        {
            /* If the user entered nothing then it sets the address of
            first name to 0 and calculates the address of last name */
            person->first_name_posn = 0;
            person->last_name_posn = ftell(fp) + sizeof(contact);
            fn[0] = '\0';
            length[0] = 0;

        }
        else
        {
            /* If the user enters something then it calculates the address
            of first name (current address) and last name (next address) */
            strcpy(fn, buffer);
            person->first_name_posn = ftell(fp) + sizeof(contact);
            length[0] = strlen(buffer) + 1;
            person->last_name_posn = person->first_name_posn + length[0];
        }
        
        /* Exact same steps except with last name instead. */
        printf("Last Name: ");
        fgets(buffer, 1002, stdin);
        strtok(buffer, "\n");
        ln = malloc(strlen(buffer)+1);
        if (strcmp(buffer, "\n") == 0)
        {
            /* 
            Logic is a bit different here
            If they enter nothing I first calculate the position
            of the next name using the calculations from the previous
            fgets(). Then I set the pointer to 0
            */
            person->company_name_posn = person->last_name_posn;
            person->last_name_posn = 0;
            ln[0] = '\0';
            length[1] = 0;
        }
        else
        {
            strcpy(ln, buffer);
            length[1] = strlen(buffer) + 1;
            person->company_name_posn = person->last_name_posn + length[1];
        }

        /* Exact same steps except with company name instead */
        printf("Company Name: ");
        fgets(buffer, 1002, stdin);
        strtok(buffer, "\n");
        cn = malloc(strlen(buffer)+1);
        if (strcmp(buffer, "\n") == 0)
        {
            person->email_posn = person->company_name_posn;
            person->company_name_posn = 0;
            cn[0] = '\0';
            length[2] = 0;

        }
        else
        {
            strcpy(cn, buffer);
            length[2] = strlen(buffer) + 1;
            person->email_posn = person->company_name_posn + length[2];
        }
        
        /* Reading phone number */
        do
        {
            /* Recets the check */
            check1 = 0;
            printf("Phone Number (enter only number): ");
            fgets(buffer, 1002, stdin);
            strtok(buffer, "\n");
            for (i = 0; i < strlen(buffer); ++i)
            {
                /* Checks if each character they entered is a number, if not
                it will change the check to repeat the loop. */
                if(isdigit(buffer[i]) == 0)
                {
                    check1 = 1;
                }
            }
            if(check1 == 0)
            {
                /* If they only entered numbers it sets the phone_number to their input */
                person->phone_number = strtol(buffer, &pn, 10);
            }
        } while(check1 != 0);

        /* Same logic as company name */
        printf("Email: ");
        fgets(buffer, 1002, stdin);
        strtok(buffer, "\n");
        e = malloc(strlen(buffer)+1);
        if (strcmp(buffer, "\n") == 0)
        {
            person->next = person->email_posn;
            person->email_posn = 0;
            e[0] = '\0';
            length[3] = 0;
        }
        else
        {
            strcpy(e, buffer);
            length[3] = strlen(buffer) + 1;
            person->next = person->email_posn + length[3];
        }

        /* Writes the addresses to the file */
        fwrite(person, sizeof(contact), 1, fp);
        
        /* Writes the actual data to the file */
        fwrite(fn, length[0], 1, fp);
        fwrite(ln, length[1], 1, fp);
        fwrite(cn, length[2], 1, fp);
        fwrite(e, length[3], 1, fp);

        /* Free dynamically allocated memory */
        free(fn);
        free(ln);
        free(cn);
        free(e);
        free(person);

        /* Point them to NULL so they can be reused when it loops */
        fn = NULL;
        ln = NULL;
        cn = NULL;
        e = NULL;
        person = NULL;
    }
    
}

int userRead(FILE * fp)
{
    /* Declaring variables */
    char buffer[1002];
    int check1 = 0;
    int returnvalue = 0;
    unsigned long phonenumber;
    contact * addresses;

    /* Move to the beginning of the file to check all entries */
    fseek(fp, 0, SEEK_SET);

    /* Asking the user */
    printf("Do you wish to retrieve a contact? (Yes or No)?: ");
    fgets(buffer, 5, stdin);
    
    if(strcmp(buffer, "No\n") != 0)
    {   
        returnvalue = 1;
        /* Dynamically allocates memory */
        addresses = malloc(sizeof(contact));

        /* Asks for the phone number */
        printf("Phone Number: ");
        fscanf(stdin, "%lu", &phonenumber);
        fgetc(stdin);

        while(1)
        {
            /* Reads the addresses from the file and puts them in the struct */
            fread(addresses, sizeof(contact), 1, fp);

            /* Stop the while loop if the phone number is found */
            if(addresses->phone_number == phonenumber)
            {
                check1 = 0;
                break;
            }
            /* If the end of file is reached before finding the number then it breaks
            the loop */
            else if(feof(fp))
            {
                check1 = 1;
                break;
            }
            /* If the number isn't found or the eof isnt reached then it goes to
            the next set of addresses */
            else
            {
                fseek(fp, addresses->next, SEEK_SET);   
            }
        }

        /* If the end of file is reached it prints the message, else it prints the information */
        if (check1 == 1)
        {
            printf("No match found\n");
        }
        else
        {
            /* If the address points to 0 it doesnt print any information */
            if(addresses->first_name_posn == 0)
            {
                printf("First Name:\n");
            }
            else
            {
                /* If the address is not 0 then it moves to that position in the file
                and reads it */
                fseek(fp, addresses->first_name_posn, SEEK_SET);
                fread(buffer, addresses->last_name_posn - addresses->first_name_posn, 1, fp);
                printf("First Name: %s\n", buffer);
            }

            /* Same logic as first name */
            if(addresses->last_name_posn == 0)
            {
                printf("Last Name:\n");
            }
            else
            {
                fseek(fp, addresses->last_name_posn, SEEK_SET);
                fread(buffer, addresses->company_name_posn - addresses->last_name_posn, 1, fp);
                printf("Last Name: %s\n", buffer);
            }
            
            /* Same logic as first name */
            if(addresses->company_name_posn == 0)
            {
                printf("Company Name:\n");
            }
            else
            {
                fseek(fp, addresses->company_name_posn, SEEK_SET);
                fread(buffer, addresses->email_posn - addresses->company_name_posn, 1, fp);
                printf("Company Name: %s\n", buffer);
            }

            /* Prints the number they wanted to find */
            printf("Phone Number: %lu\n", addresses->phone_number);

            /* Same logic as first name */
            if(addresses->email_posn == 0)
            {
                printf("Email:\n");
            }
            else
            {
                fseek(fp, addresses->email_posn, SEEK_SET);
                fread(buffer, addresses->next - addresses->email_posn, 1, fp);
                printf("Email: %s\n", buffer);
            }

        }
        /*Free dynamically allocated struct*/
        free(addresses);  
    }
    /* Returns 1 if they answered Yes, 0 if they answerd No 
    (further explained in main)*/
    return(returnvalue);
}