#include "shell.h"

/**
 * execute_command - Executes a single command.
 * @args: An array of command-line arguments.
 * Return: 0 on success, non-zero value on failure.
 */
int execute_command(char **args)
{
pid_t pid = fork();
int status;

if (pid == -1)
{
perror("fork");
return (-1);
}
else if (pid == 0)
{
execvp(args[0], args);
perror(args[0]);
exit(EXIT_FAILURE);
}
if (waitpid(pid, &status, 0) == -1)
{
perror("waitpid");
return (-1);
}
if (WIFEXITED(status))
{
return (WEXITSTATUS(status));
}
else if (WIFSIGNALED(status))
{
fprintf(stderr, "Process %d terminated by signal %d\n", pid, WTERMSIG(status));
return (-1);
}
else
{
fprintf(stderr, "Process %d terminated abnormally\n", pid);
return (-1);
}
}

/**
 * execute_pipeline - Executes a pipeline of commands separated
 * by the '|' character.
 * @args: An array of command-line arguments.
 * @num_args: The number of command-line arguments.
 * Return: The exit status of the last command in the pipeline.
 */
int execute_pipeline(char **args, int num_args)
{
int i;
/*int status = 0;*/
int operator_pos = -1;

for (i = 0; i < num_args; i++)
{
if (is_logical_operator(args[i]))
{
operator_pos = i;
break;
}
}
if (operator_pos == -1)
{
return (execute_command(args));
}
else
{
return (run_logical_operator(args, num_args, operator_pos));
}
}

/**
 * parse_pipeline - Parse a pipe line separated by the '|' character.
 * @line: The input string containing the pipeline.
 * @args: An array of command-line arguments.
 * Return: The number of command-line arguments.
 */
int parse_pipeline(char *line, char **args)
{
int num_args = 0;
char *token = strtok(line, "|");

while (token != NULL && num_args < MAX_ARGS)
{
args[num_args] = strtok(token, "\n");
num_args++;

token = strtok(NULL, "|");
}

return (num_args);
}

/**
 * parse_args - Parses a string of command-line arguments
 * separated by whitespace.
 * @line: The input string containing the arguments.
 * @args:  An array of command-line arguments.
 * Return:  The number of command-line arguments.
 */
int parse_args(char *line, char **args)
{
int num_args = 0;
char *token = strtok(line, " ");

while (token != NULL && num_args < MAX_ARGS)
{
args[num_args] = token;
num_args++;

token = strtok(NULL, " ");
}

args[num_args] = NULL;

return (num_args);
}

/**
 * is_logical_operator -  Checks if a token is a logical operator.
 * @token: The token to check.
 * Return: 1 if the token is a logical operator, 0 otherwise.
 */
int is_logical_operator(char *token)
{
	return (strcmp(token, "&&") == 0 || strcmp(token, "||") == 0);
}
