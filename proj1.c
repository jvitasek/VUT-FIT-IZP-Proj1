/**
 * @file proj1.c
 * @author Jakub Vitasek <me@jvitasek.cz>
 * @date 22.10.2013
 * @brief 1BIT Project 1: Counting Words
 * 
 * In a nutshell, the program counts words containing a user-specified character
 * and prints the number. The user can utilize multiple modifiers to alter the
 * functionality. It does all of this using no functions from the built-in library
 * <string.h>.
 */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_SIZE 80
#define ARGV_1 1
#define ARGV_2 2

///////////////////////////////////
//            FUNCTION PROTOTYPES
///////////////////////////////////

int arg_type_and_output(int argc, char *argv[]); // Gets the user-side arguments.
int get_c(int c); // Gets a char from stdin.
void print_help(void); // Prints out the help message.
int is_legal(char c); // Checks if the current character is a legal character.
unsigned int string2int(const char *s); // Converts a string into an integer.
int data_type(int argc, char *argv[], int arg_no); // Gets the data type of a specific argument.
int is_debug(int argc, char *argv[]); // Returns 0 when debug is off, returns 1 when debug is on.
void debug(int c, int inside); // Basic debug mode functionality.
int all_words(char c, int i, int dbg, int inside); // Prints the number of all entered words.
int minimal_length(char c, char *argv[], unsigned int i, int dbg, int inside); // Prints the number of words of a minimal given length.
int capital(char c, int i, int dbg, int inside); // Prints the number of words containing a capital letter.
int capital_n(char c, char *argv[], int i, unsigned int position, int dbg, int inside); // Prints the number of words containing a capital letter at a given position.
int number(char c, int i, int dbg, int inside); // Prints the number of words containing any number.
int number_n(char c, char *argv[], int i, unsigned int position, int dbg, int inside); // Prints the number of words containing any number at a given position.
int character(char c, char *argv[], int i, int dbg, int inside); // Prints the number of words containing a given character.
int character_n(char c, char *argv[], int i, unsigned int position, int dbg, int inside); // Prints number of words containing a given char at a given position.

///////////////////////////////////
//                           MAIN
///////////////////////////////////

int main(int argc, char *argv[])
{
	if(argc > 5)
	{
		fprintf(stderr, "\n\033[31;1m ERROR \033[0m\nYou've entered too many arguments.\nTo get the help message, type \"--help\" as the first argument (0 being ./proj1).\n\n");
		return EXIT_FAILURE;
	}
	else if(argc == 1)
	{
		fprintf(stderr, "\n\033[31;1m ERROR \033[0m\nNothing to search for.\nTo get the help message, type \"--help\" as the first argument (0 being ./proj1).\n\n");
		return EXIT_FAILURE;
	}
	arg_type_and_output(argc, argv);
	return 0;
}

///////////////////////////////////
//            FUNCTION DEFINITION
///////////////////////////////////

int get_c(int c)
{
	c = getchar();
	return c;
}
 
int arg_type_and_output(int argc, char *argv[])
{
	int c = 0;
	unsigned int i = 0;
	unsigned int position = 0;
	int inside = 0;
	int dbg = is_debug(argc, argv);
 
	/* Printing help. */
	if((strcmp(argv[1], "--help") == 0) || ((argc == 3) && (strcmp(argv[2], "--help") == 0)) || ((argc == 4) && (strcmp(argv[3], "--help") == 0)))
		print_help();

	/* Printing the number of all entered words.*/
	else if(((strcmp(argv[1], ".") == 0) && (argc == 2)) || ((strcmp(argv[1], ".") == 0) && (argc == 3) && !((data_type(argc, argv, ARGV_2)) == 1)))
		printf("%d\n", all_words(c, i, dbg, inside));
	 
	/* Printing the number of words of a specified minimal length. */
	else if((strcmp(argv[1], ".") == 0) && ((data_type(argc, argv, ARGV_2)) == 1) && (argc >= 3))
	printf("%d\n", minimal_length(c, argv, i, dbg, inside));
	 
	/* Printing the number of words containing a capital letter. */
	else if(((strcmp(argv[1], "^") == 0) && (argc == 2)) || ((strcmp(argv[1], "^") == 0) && (argc == 3) && !((data_type(argc, argv, ARGV_2)) == 1)))
	printf("%d\n", capital(c, i, dbg, inside));
	 
	/* Printing the number of words containing a capital letter at a specified position in the word. */
	else if((strcmp(argv[1], "^") == 0) && (data_type(argc, argv, ARGV_2) == 1) && (argc >= 3))
	printf("%d\n", capital_n(c, argv, i, position, dbg, inside));
	 
	/* Printing the number of words containg any number. */
	else if(((strcmp(argv[1], ":") == 0) && (argc == 2)) || ((strcmp(argv[1], ":") == 0) && (argc == 3) && !((data_type(argc, argv, ARGV_2)) == 1)))
	printf("%d\n", number(c, i, dbg, inside));
	 
	/* Printing the number of words containg any number at a specified position in the word. */
	else if((strcmp(argv[1], ":") == 0) && (data_type(argc, argv, ARGV_2) == 1) && (argc >= 3))
	printf("%d\n", number_n(c, argv, i, position, dbg, inside));
	 
	/* Printing the number of words containing a specified character. */
	else if((((data_type(argc, argv, ARGV_1) == 3 || data_type(argc, argv, ARGV_1) == 1)) && (argc == 2)) || ((argc == 3) && !((data_type(argc, argv, ARGV_2)) == 1)))
	printf("%d\n", character(c, argv, i, dbg, inside));
	 
	/* Printing the number of words containing a specified character at a given position in the word. */
	else if((data_type(argc, argv, ARGV_1) == 3 || data_type(argc, argv, ARGV_1) == 1) && (argc >= 3) && (data_type(argc, argv, ARGV_2) == 1))
	printf("%d\n", character_n(c, argv, i, position, dbg, inside));
	 
	else
	printf("Wrong combination of arguments. If you need help, type \"--help\"\n");
 
        return 0;
}
 
/* Prints the help message. */
void print_help()
{
	printf("\n\033[32;1m HELP \033[0m\n"
					"\n\"Counting Words\" - proj1.\n"
			"Author: Jakub Vitasek (c) 2013\n"
			"The program counts words containing a specified character and prints the no.\n"
			"Program starts upon entering the following prompt:\n"
			"echo 'text' | ./proj1 X [N] [-d]\n"
			"The maximum value of 'text' has to be <= INT_MAX, debug reads 80 chars/word.\n"
			"Param description:\n"
			"  X  Prints the no. of words containing the character X.\n"
			"  .  Prints the no. of all entered words.\n"
			"  :  Prints the no. of words containing any number.\n"
			"  ^  Prints the no. of words containing a capital letter.\n"
			"  X  [N]  Prints no. of words containing the character X at the position [N].\n"
			"  .  [N]  Prints the no. of words of the minimal length [N].\n"
			"  :  [N]  Prints the no. of words containing any number at the position [N].\n"
			"  ^  [N]  Prints the no. of words containing a cap. letter at the position [N].\n"
			"Adding \"-d\" at the end of any the prompt will trigger the debug mode.\n"
			"The debug mode prints all of the entered words.\n\n");
}

/* Checks if the current character is a legal character. */
int is_legal(char c)
{
	if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_') || (c == '-'))
		return 1;
	else
		return 0;
}

/* Returns 0 when debug is off, returns 1 when debug is on. */
int is_debug(int argc, char *argv[])
{
	if((argc == 2) && (strcmp(argv[1], "-d") == 0))
		return 1;
	else if((argc == 3) && (strcmp(argv[2], "-d") == 0))
		return 1;
	else if((argc == 4) && (strcmp(argv[3], "-d") == 0))
		return 1;
	else
		return 0;
}

/* Basic debug mode functionality. */
void debug(int c, int inside)
{
	if(is_legal(c) == 1)   
		putchar(c);
	else if(inside != 2)
		putchar('\n');
}

/* Converts a string into an integer. */
unsigned int string2int(const char *s)
{
	unsigned int n = 0;
	if(!s)
		return 0;
	while(*s)
	{
		if(*s < '0' || *s > '9')
			return 0;
		n = n * 10 + *s - '0';
		s++;
	}
	return n;
}

/* Gets the data type of a specific argument. */
int data_type(int argc, char *argv[], int arg_no)
{
	int is_int = 1;
	int is_char = 0;
	char *type = "";
 
	char *current_char;
	int i = 0;
	for (i = 1; i < argc; i++)
	{
		if(arg_no == 1)
			current_char = argv[1];
		else
			current_char = argv[2];
		is_int = 1;
		while (*current_char != '\0')
		{
			if(*current_char < '0' || *current_char > '9')
			{
				if(*current_char == '.' && is_int == 1)
					is_int = 0;
				else
				{
					is_int = 0;
					is_char = 1;
				}
			}
			current_char++;
		}
 
		type = (is_int)? "int" : "";
		type = (is_char)? "char" : type;
 
		if(strcmp(type, "int") == 0)
			return 1;
		else if(strcmp(type, "char") == 0)
			return 3;
		else
			break;
	}
	return 0;
}

int all_words(char c, int i, int dbg, int inside)
{
	int counter = 0; // Created for telling no input apart from anything else.
	while((c = get_c(c)) != EOF)
	{
		if((is_legal(c) == 1)) // Is there anything coming from stdio?
			counter++;
		if(is_legal(c) == 1)
		{
			if(dbg == 1)
				putchar(c);
			inside = 1;
		}
		else if(inside != 2)
		{
			if(dbg == 1)
				putchar('\n');
			inside = 2;
			i++;
		}
	}
	if(counter > 0)
		return i;
	else
		return 0;
}

int minimal_length(char c, char *argv[], unsigned int i, int dbg, int inside)
{
	int count = 0;
	while((c = get_c(c)) != EOF)
	{
		if(dbg == 1)
			debug(c, inside);
		i++;
		inside = 1;
		while(i == string2int(argv[2]) && (is_legal(c) == 1))
		{
			count++;
			break;
		}
		if(is_legal(c) == 0)
		{
			i = 0;
			inside = 2;
		}
	}
	return count;
}

int capital(char c, int i, int dbg, int inside)
{
	while((c = get_c(c)) != EOF)
	{
		if(dbg == 1)
			debug(c, inside);
		inside = 1;
		if(c >= 'A' && c <= 'Z')
		{
			i++;
			while((c = get_c(c)) != EOF) // To only count the WORDS containing the cap. letter, not all the cap. letters.
			{
				if(dbg == 1)
					debug(c, inside);
				if((is_legal(c) == 0) && (inside != 2))
				{
					inside = 2;
					break;
				}
			}
		}
		if((is_legal(c) == 0) && (inside != 2))
			inside = 2;
	}
	return i;
}

int capital_n(char c, char *argv[], int i, unsigned int position, int dbg, int inside)
{
        while((c = get_c(c)) != EOF)
        {
                if(dbg == 1)
                        debug(c, inside);
                position++;
                inside = 1;
                if((position == string2int(argv[2])) && (c >= 'A' && c <= 'Z'))
                        i++;
                else if((is_legal(c) == 0) && (inside != 2))
                {
                        position = 0;
                        inside = 2;
                }
        }
        return i;
}
 
int number(char c, int i, int dbg, int inside)
{
        while((c = get_c(c)) != EOF)
        {
                if(dbg == 1)
                        debug(c, inside);
                inside = 1;
                if(c >= '0' && c <= '9')
                {
                        i++;
                        while((c = get_c(c)) != EOF) // To only count WORDS containing the number, not all the numbers.
                        {
                                if(dbg == 1)
                                        debug(c, inside);
                                if((is_legal(c) == 0) && (inside != 2))
                                {
                                        inside = 2;
                                        break;
                                }
                        }
                }              
                if((is_legal(c) == 0) && (inside != 2))
                        inside = 2;
        }
        return i;
}
 
int number_n(char c, char *argv[], int i, unsigned int position, int dbg, int inside)
{
        while((c = get_c(c)) != EOF)
        {
                if(dbg == 1)
                        debug(c, inside);
                position++;
                inside = 1;
                if((position == string2int(argv[2])) && (c >= '0' && c <= '9'))
                        i++;
                else if((is_legal(c) == 0) && (inside != 2))
                {
                        position = 0;
                        inside = 2;
                }
        }
        return i;
}
 
int character(char c, char *argv[], int i, int dbg, int inside)
{
	while((c = get_c(c)) != EOF)
	{
		if(dbg == 1)
			debug(c, inside);
		inside = 1;
		if(c == argv[1][0])
		{
			i++;
			while((c = get_c(c)) != EOF) // To only count the WORDS containing the char, not counting all the chars.
			{
				if(dbg == 1)
					debug(c, inside);
				if((is_legal(c) == 0) && (inside != 2))
				{
					inside = 2;
					break;
				}
			}
		}
		else if((is_legal(c) == 0) && (inside != 2))
			inside = 2;
	}
	return i;
}

int character_n(char c, char *argv[], int i, unsigned int position, int dbg, int inside)
{
	while((c = get_c(c)) != EOF)
	{
		if(dbg == 1)
			debug(c, inside);
		position++;
		inside = 1;
		if((position == string2int(argv[2])) && (argv[1][0] == c))
			i++;
		else if((is_legal(c) == 0) && inside != 2)
		{
			position = 0;
			inside = 2;
		}
	}
	return i;
}
