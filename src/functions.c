#include "header.h"

void userinput(FILE * fp)
{
	char buffer[1000];
	int i = 0;
	contact * person = malloc(sizeof(contact));
	contactdata * data = malloc(sizeof(contactdata));

	printf("Initial value: %ld\n", person->first_name_posn);

	while (free)
	{
		printf("Do you wish to enter a new contact? (Yes or No)?: ");
		fgets(buffer, 5, stdin);
		
		if(strcmp(buffer, "No\n") == 0)
		{
			break;
		}

		if(i != 0)
		{
			person = realloc(person, sizeof(contact)* (i+1));
		}

		printf("First Name: ");
		fgets(buffer, 1000, stdin);
		
		person[i].first_name_posn = ftell(fp);

		strtok(buffer, "\n");
		fwrite(buffer, strlen(buffer)+1, 1, fp);

		printf("Last Name: ");
		fgets(buffer, 1000, stdin);
		person[i].last_name_posn = ftell(fp);
		strtok(buffer, "\n");
		fwrite(buffer, strlen(buffer)+1, 1, fp);
		
		printf("Company Name: ");
		fgets(buffer, 1000, stdin);
		person[i].company_name_posn = ftell(fp);
		strtok(buffer, "\n");
		fwrite(buffer, strlen(buffer)+1, 1, fp);

		printf("Phone Number (enter only number): ");
		fscanf(stdin, "%lu", &person[i].phone_number);
		fgetc(stdin);

		printf("Email: ");
		fgets(buffer, 1000, stdin);
		person[i].email_posn = ftell(fp);
		strtok(buffer, "\n");
		fwrite(buffer, strlen(buffer)+1, 1, fp);

		person[i].next = ftell(fp);
		i++;
	}
}