#include "shell.h"

/**
* run_logical_operator -  Executes a pipeline of commands based on the outcome
* of the previous command.
*
* @args : all argementes
* @num_args:  The number of command-line arguments.
* @opertor_pos: The position of the logical operator in the array.
* Return: Exit Value By Status
*/
int run_logical_operator(char **args, int num_args, int opertor_pos)
{
args[opertor_pos] = NULL;
int status = 0;

status = execute_command(args);

if (strcmp(args[opertor_pos], "&&") == 0 && status == 0)
{
return (execute_pipeline(args + opertor_pos + 1, num_args - opertor_pos - 1));
}
else if (strcmp(args[opertor_pos], "||") == 0 && status != 0)
{
return (execute_pipeline(args + opertor_pos + 1, num_args - opertor_pos - 1));
}
else
{
return (status);
}
