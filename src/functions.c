FILE * openfile(int argc)
{
	FILE * fptr = fopen("myContactList.db", "ab");
	return fptr;
}