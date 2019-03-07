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
			person = realloc(person, sizeof(contact) * (i+1));
			data = realloc(data, sizeof(contactdata) * (i+1));
		}

		printf("First Name: ");
		fgets(buffer, 1000, stdin);
		strtok(buffer, "\n");
		data[i].firstname = malloc(strlen(buffer)+1);
		strcpy(data[i].firstname, buffer);
		person[i].first_name_posn = ftell(fp);
		fwrite(buffer, strlen(buffer)+1, 1, fp);

		printf("Last Name: ");
		fgets(buffer, 1000, stdin);
		strtok(buffer, "\n");
		data[i].lastname = malloc(strlen(buffer)+1);
		strcpy(data[i].lastname, buffer);
		person[i].last_name_posn = ftell(fp);
		strtok(buffer, "\n");
		fwrite(buffer, strlen(buffer)+1, 1, fp);
		
		printf("Company Name: ");
		fgets(buffer, 1000, stdin);
		strtok(buffer, "\n");
		data[i].companyname = malloc(strlen(buffer)+1);
		strcpy(data[i].companyname, buffer);
		person[i].company_name_posn = ftell(fp);
		strtok(buffer, "\n");
		fwrite(buffer, strlen(buffer)+1, 1, fp);

		printf("Phone Number (enter only number): ");
		fscanf(stdin, "%lu", &person[i].phone_number);
		fgetc(stdin);

		printf("Email: ");
		fgets(buffer, 1000, stdin);
		strtok(buffer, "\n");
		data[i].email = malloc(strlen(buffer)+1);
		strcpy(data[i].email, buffer);
		person[i].email_posn = ftell(fp);
		strtok(buffer, "\n");
		fwrite(buffer, strlen(buffer)+1, 1, fp);

		person[i].next = ftell(fp);
		i++;
	}
}