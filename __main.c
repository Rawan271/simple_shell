#include "shell.h"
/**
 * main - Entry point for the shell
 *
 * Return: Always 0 on success
 */
int main(void)
{
int status, i = 0;
char *line = NULL, *args[MAX_ARGS];
size_t len = 0;
pid_t pid;

while (1)
{ /* Print prompt */
printf("shell> ");/* Read input */
getline(&line, &len, stdin);/* Parse input into arguments */
args[i] = strtok(line, " \n");
while (args[i] != NULL && i < MAX_ARGS - 1)
{i++;
args[i] = strtok(NULL, " \n"); }
args[i] = NULL;
/* Check for built-in commands */
if (strcmp(args[0], "exit") == 0)
{ exit(0); } /* Fork a child process to execute the command */
pid = fork();
if (pid == 0)
{ /* Child process */
execvp(args[0], args);
perror("execvp");
exit(1); }
else if (pid < 0)
{ /* Fork error */ perror("fork");
exit(1); } /* Fork error */
else
{ /* Parent process */
waitpid(pid, &status, 0);
} }
return (0); /*end of main*/
}
