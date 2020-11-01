#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Typedef And Define */
#define ELF_FILE_ARGUMENT_MISSING 	1
#define ELF_FILE_OPEN_ERROR		2

#define ZERO 					0

Elf64_Ehdr header;

/*Declaration of function */
void readelf_header(char *elf);
void readelf_Pheader(char *elf);
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
	readelf_header(string_elf);
	readelf_Pheader(string_elf);
	free(string_elf);
	return 0;
}
void readelf_header(char *elf)
{
       printf("Parsing ELF \n");

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

       printf("File Type \t\t\t");
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

	printf("Machine Type \t\t\t");
	switch(header.e_machine)
	{
		case EM_M32 : printf("AT&T WE 32100\n");
			      break;
		case EM_SPARC : printf("Sun Microsystems SPARC.\n");
			      break;
		case EM_386 : printf("Intel 80386.\n");
			      break;
		case EM_68K : printf("Motorola 68000\n");
			      break;
		case EM_88K : printf("Motorola 68000\n");
			      break;
		case EM_860 : printf("Intel 80860\n");
			      break;
		case EM_MIPS : printf("MIPS RS3000 Big Endian\n");
			      break;
		case EM_PARISC : printf("HP/PA\n");
			      break;
		case EM_SPARC32PLUS : printf("SPARC with enhanced Instruction Set\n");
			      break;
		case EM_PPC :printf("PowerPC\n");
			     break;
		case EM_PPC64 :printf("PowerPC 64-Bit\n");
			     break;
		case EM_S390 :printf("IBM S/390\n");
			     break;
		case EM_ARM :printf("Advanced RISC Machine\n");
			     break;
		case EM_SH :printf("Renesas SuperH\n");
			     break;
		case EM_SPARCV9 :printf("SPARC v9 64-Bit\n");
			     break;
		case EM_IA_64 :printf("Intel Itanium\n");
			     break;
		case EM_X86_64 :printf("AMD X86_64\n");
			     break;
		case EM_VAX :printf("DEC Vax\n");
			     break;
		case EM_NONE : 
		default :printf("None\n");
			      break;
	}		
	
	printf("Entry Point Address \t\t\t:%x\n",header.e_entry);
	printf("Program Header Offset \t\t\t:%ld\n",header.e_phoff);
	printf("Section Header Offset \t\t\t:%ld\n",header.e_shoff);
	//printf("Processor Flags \t\t\t:%x\n",header.e_flags);
	printf("ELF Header Size \t\t\t:%d\n",header.e_ehsize);
	printf("Program Header size \t\t\t:%d\n",header.e_phentsize);
	printf("Program Header Entries \t\t\t:%d\n",header.e_phnum);
	printf("Section Header size \t\t\t:%d\n",header.e_shentsize);
	printf("Section Header Entries \t\t\t:%d\n",header.e_shnum);
	printf("Section Header Table Index \t\t\t:%d\n",header.e_shstrndx);


}
/* Program Header Information */
void readelf_Pheader(char *elf)
{
	Elf64_Phdr p_header;
	int loop_table = 0;
	//printf("pheadr size :%d\n",sizeof(Elf64_Phdr));
	/* Check for e_phnum to find programme header is available or not */
	if(ZERO != header.e_phnum)
	{

	}
	else
	{
		printf("Program Header Table is not present\n");
	}

	printf("**********************************Program Header Table*************************************\n");
	printf("Type\t\t\t offset\t\t vAddr\t\t pAddr\t\t ");
	printf("FSize\t\t Msize\t\t flags\t\t align\n");
	/* Loop over the Table and display */
	for(loop_table = 0; loop_table < header.e_phnum; loop_table++)
	{
		memcpy(&p_header,&(elf[header.e_phoff + (sizeof(Elf64_Phdr) * loop_table)]), sizeof(Elf64_Phdr));
		char string[6000];
		memcpy(string,&p_header,6000);
		for(char i = 0;i< (sizeof(Elf64_Phdr));i++)
		{
		//	printf("%x  ",string[i]);
		}
		printf("\n");

		switch(p_header.p_type)
		{
		case PT_LOAD :printf("LOAD\t\t\t");
					  break;
		case PT_DYNAMIC :printf("DYNAMIC\t\t\t");
						break;
		case PT_INTERP :printf("INTERP\t\t\t");
						break;
		case PT_NOTE :printf("NOTE\t\t\t");
						break;
		case PT_SHLIB :printf("SHLIB\t\t\t");
						break;
		case PT_PHDR :printf("PHDR\t\t\t");
						break;
		case PT_LOPROC :printf("LOPROC\t\t\t");
						break;
		case PT_HIPROC :printf("HIPROC\t\t\t");
						break;
		case PT_GNU_STACK :printf("GNU_STACK\t\t");
							break;
		case PT_GNU_EH_FRAME : printf("GNU_EH_FRAME\t\t");
							break;
		case PT_GNU_RELRO : printf("GNU_RELRO\t\t");
							break;
		case PT_NULL :
		default:	printf("Undefined\t\t");
				break;

		}
		printf("%lx\t\t",p_header.p_offset);
		printf("%lx\t\t",p_header.p_vaddr);
		printf("%lx\t\t",p_header.p_paddr);
		printf("%lx\t\t",p_header.p_filesz);
		printf("%lx\t\t",p_header.p_memsz);
		switch(p_header.p_flags)
		{
		case 0x04: printf("R\t\t");
					break;
		case 0x02:printf("W\t\t");
					break;
		case 0x01:printf("X\t\t");
					break;
		case 0x07 : printf("RWX\t\t");
					break;
		case 0x03 :printf("WE\t\t");
					break;
		case 0x05 :printf("RE\t\t");
					break;
		case 0x06 :printf("RW\t\t");
					break;
		case 0x00 :
		default : printf("Undefined\t\t");
					break;
		}
		printf("%lx\n",p_header.p_align);

	}
}


















