#include "header.h"

void userInput(FILE * fp)
{
    /* Declaring variables */
    char buffer[1000];
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
        fgets(buffer, 1000, stdin);
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
            of first name and last name */
            strcpy(fn, buffer);
            person->first_name_posn = ftell(fp) + sizeof(contact);
            length[0] = strlen(buffer) + 1;
            person->last_name_posn = person->first_name_posn + length[0];
        }
        
        /* Exact same steps except with last name instead. */
        printf("Last Name: ");
        fgets(buffer, 1000, stdin);
        strtok(buffer, "\n");
        ln = malloc(strlen(buffer)+1);
        if (strcmp(buffer, "\n") == 0)
        {
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

        printf("Company Name: ");
        fgets(buffer, 1000, stdin);
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
        
        do
        {
            check1 = 0;
            printf("Phone Number (enter only number): ");
            fgets(buffer, 1000, stdin);
            strtok(buffer, "\n");
            for (i = 0; i < strlen(buffer); ++i)
            {
                if(isdigit(buffer[i]) == 0)
                {
                    check1 = 1;
                }
            }
            if(check1 == 0)
            {
                person->phone_number = strtol(buffer, &pn, 10);
            }
        } while(check1 != 0);

        printf("Email: ");
        fgets(buffer, 1000, stdin);
        strtok(buffer, "\n");
        e = malloc(strlen(buffer)+1);
        if (strcmp(buffer, "\n") == 0)
        {
            person->next = person->email_posn;
            person->email_posn = 0;
        }
        else
        {
            strcpy(e, buffer);
            length[3] = strlen(buffer) + 1;
            person->next = person->email_posn + length[3];
        }

        fwrite(person, sizeof(contact), 1, fp);
        
        fwrite(fn, length[0], 1, fp);
        fwrite(ln, length[1], 1, fp);
        fwrite(cn, length[2], 1, fp);
        fwrite(e, length[3], 1, fp);

        free(fn);
        free(ln);
        free(cn);
        free(e);
        free(person);

        fn = NULL;
        ln = NULL;
        cn = NULL;
        e = NULL;
        person = NULL;
    }
    
}

int userRead(FILE * fp)
{
    char buffer[1000];
    int check1 = 0;
    int returnvalue = 0;
    unsigned long phonenumber;
    contact * addresses;

    fseek(fp, 0, SEEK_SET);

    printf("Do you wish to retrieve a contact? (Yes or No)?: ");
    fgets(buffer, 5, stdin);
    
    if(strcmp(buffer, "No\n") != 0)
    {   
        returnvalue = 1;
        addresses = malloc(sizeof(contact));

        printf("Phone Number: ");
        fscanf(stdin, "%lu", &phonenumber);
        fgetc(stdin);

        while(1)
        {
            fread(addresses, sizeof(contact), 1, fp);
            if(addresses->phone_number == phonenumber)
            {
                check1 = 0;
                break;
            }
            else if(feof(fp))
            {
                check1 = 1;
                break;
            }
            else
            {
                fseek(fp, addresses->next, SEEK_SET);   
            }
        }

        if (check1 == 1)
        {
            printf("No match found\n");
        }
        else
        {
            
            if(addresses->first_name_posn == 0)
            {
                printf("First Name:\n");
            }
            else
            {
                fseek(fp, addresses->first_name_posn, SEEK_SET);
                fread(buffer, addresses->last_name_posn - addresses->first_name_posn, 1, fp);
                printf("First Name: %s\n", buffer);
            }

            
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

            printf("Phone Number: %lu\n", addresses->phone_number);

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
        
    }

    return(returnvalue);
}