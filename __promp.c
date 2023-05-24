#include "shell.h"

/**
 * prompt - Display Shell Prompt
 */
void prompt(void)
{
	PRINTER("$ ");
}
/**
 * print_error - Display Error Based on Command and How Many Time Shell Looped
 * @input:User Input
 * @counter:Simple Shell Count Loop
 * @argv:Program Name
 * Return: Void
 */
void print_error(char *input, int counter, char **argv)
{
	char *era;

	PRINTER(argv[0]);
	PRINTER(": ");
	era = _itoa(counter);
	PRINTER(era);
	free(era);
	PRINTER(": ");
	PRINTER(input);
	PRINTER(": not found\n");
}
