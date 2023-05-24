#include "shell.h"
/**
 * take_line - take line from user and put it into file
 *
 * Return: 1 if success - error if failed
 * if: fp equal NULL print error measage
 * else: printf $ and take me line
 */
char *take_line()
{
	FILE *fp == NULL;
	char *line = NULL;
	size_t len = 0;
	/* Open file for writing*/
fp = fopen("test1.txt", "w");
if (fp == NULL)
{
	printf("Error opening file\n");
	exit(1);
}
/* Read a line of input from the user*/
printf("($)");
getline(&line, &len, stdin);
/* Write the line to the file*/
fprintf(fp, "%s", line);
/* Close the file and free memory*/
return (line);
fclose(fp);
/*return (fp);*/
free(line);
}
