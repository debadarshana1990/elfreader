#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Typedef And Define */
#define ELF_FILE_ARGUMENT_MISSING 	1
#define ELF_FILE_OPEN_ERROR		2

/*Declaration of function */
void readelf(char *elf);
void elf_help(int ErrorNo)
{

}

int main(int argc, char *argv[])
{
	FILE *user_elf;
	char *string_elf = 0;
	printf("Reading ELF FIle\n");
	if(argc < 2)
	{
		printf("No Elf File found ,provide the path of elf file\n");
		elf_help(ELF_FILE_ARGUMENT_MISSING);
		exit(0);
	}
	/* read the elf file from the provided path */
        user_elf = fopen(argv[1],"rb");

	/* Copy the file to the string */
	if(NULL == user_elf)
	{
		printf("Error in openeing File\n");
		elf_help(ELF_FILE_OPEN_ERROR);
		fclose(user_elf);
		exit(0);
	}
	/* Copy the File Into the string */
	fseek(user_elf,0,SEEK_END);
	long length = ftell(user_elf);
	fseek(user_elf,0,SEEK_SET);
        string_elf = (char *)malloc(sizeof(char)*(length + 1));
	string_elf[length] = '\0';
	fread(string_elf,sizeof(char),length,user_elf);
	/*print the string */
     //	printf("string :%s",string_elf);
        /* Pass the String to Parse Elf */
	readelf(string_elf);
	free(string_elf);
	return 0;
}
void readelf(char *elf)
{
       printf("Parsing ELF \n");
       Elf32_Ehdr header;
       /* Copy Elf to the Header Structure */
       memcpy(&header,elf,sizeof(header));
       printf("%x\n",header.e_ident[0]);
       printf("%c\n",header.e_ident[1]);
       printf("%c\n",header.e_ident[2]);
       printf("%c\n",header.e_ident[3]);
}



















