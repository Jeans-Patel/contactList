#include "header.h"

void userinput(FILE * fp)
{
	char buffer[1000];
	int i = 0;
	int j = 0;
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
		data[i].fn = malloc(strlen(buffer)+1);
		strcpy(data[i].fn, buffer);
		person[i].first_name_posn = ftell(fp) + 20;
		
		printf("Last Name: ");
		fgets(buffer, 1000, stdin);
		strtok(buffer, "\n");
		data[i].ln = malloc(strlen(buffer)+1);
		strcpy(data[i].ln, buffer);
		person[i].last_name_posn = ftell(fp) + 20 + strlen(data[i].fn)+1;

		printf("Company Name: ");
		fgets(buffer, 1000, stdin);
		strtok(buffer, "\n");
		data[i].cn = malloc(strlen(buffer)+1);
		strcpy(data[i].cn, buffer);
		person[i].company_name_posn = ftell(fp) + 20 + strlen(data[i].fn) + 1 + strlen(data[i].ln) + 1;

		printf("Phone Number (enter only number): ");
		fgets(buffer, 1000, stdin);
		fscanf(stdin, "%lu", &person[i].phone_number);
		fgetc(stdin);

		printf("Email: ");
		fgets(buffer, 1000, stdin);
		strtok(buffer, "\n");
		data[i].email = malloc(strlen(buffer)+1);
		strcpy(data[i].email, buffer);
		person[i].email_posn = ftell(fp);

		person[i].next = ftell(fp);

		fwrite(contact[i].first_name_posn, sizeof(long), 1, fp);
		fwrite(contact[i].last_name_posn, sizeof(long), 1, fp);
		fwrite(contact[i].company_name_posn, sizeof(long), 1, fp);
		fwrite(contact[i].email_posn, sizeof(long), 1, fp);
		fwrite(contact[i].next, sizeof(long), 1, fp);



		i++;
	}

	for (j = 0; j < i; ++j)
	{
		


	}
}