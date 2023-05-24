#include "shell.h"
/**
 * main - Entry point for the shell
 *
 * Return: Always 0 on success
 */
int main()
{
char line[MAX_LINE_LEN];
char *args[MAX_ARGS]; 
while (1)
{
printf("$ ");
fflush(stdout);
if (fgets(line, MAX_LINE_LEN, stdin) == NULL)
{
break;
}
int num_args = parse_pipeline(line, args);
if (num_args > 0)
{
execute_pipeline(args, num_args);
}
}
return 0;
}
