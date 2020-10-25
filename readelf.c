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
       /* Check the magic Marker */
       printf("Magic Marker \t\t\t");
       printf("%x ",header.e_ident[0]);
       printf("%c ",header.e_ident[1]);
       printf("%c ",header.e_ident[2]);
       printf("%c\n",header.e_ident[3]);

       printf("Archtecture \t\t\t");
       switch(header.e_ident[4])
       {
	       case ELFCLASS32: printf("32-Bit\n");
				break;
	       case ELFCLASS64: printf("64-Bit\n");
				break;
	       case ELFCLASSNONE:
	       default:printf("Invalid\n");
				 break;
	}

       printf("Data format \t\t\t");
       switch(header.e_ident[EI_DATA])
       {
	       case ELFDATA2LSB : printf("2's Complement,Little Endian\n");
				  break;
	       case ELFDATA2MSB : printf("2's Complement,Big Endian\n");
				  break;
	       case ELFDATANONE :
	       default : printf("Unknown Data Format\n");
			 break;
	}
       printf("ELF Version \t\t\t");
       switch(header.e_ident[EI_VERSION])
       {
	       case EV_CURRENT : printf(" 1(current)\n");
				break;
	       default : printf("None\n");
			break;
	}
       
       printf("ABI version \t\t\t");
       switch(header.e_ident[EI_OSABI])
	{
		/* need to be updated */
		default : printf("System V\n");
			  break;
	}

       printf("Type \t\t\t");
       switch(header.e_type)
       {
	       case ET_REL : printf("Relocatble File\n");
			     break;
	       case ET_EXEC : printf("Executable File\n");
			      break;
	       case ET_DYN  : printf("Shared Object\n");
			      break;
	       case ET_CORE : printf("Core File\n");
			      break;
	       case ET_NONE : 
	       default :     printf("Unknown Type\n");
			     break;
	}




}



















