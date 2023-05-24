#include "shell.h"

/**
 * Executes a single command.
 * @param args An array of command-line arguments.
 * @return 0 on success, non-zero value on failure.
 */
int execute_command(char **args)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0)
    {
        execvp(args[0], args);
        perror(args[0]);
        exit(EXIT_FAILURE);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1)
    {
        perror("waitpid");
        return -1;
    }

    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }
    else if (WIFSIGNALED(status))
    {
        fprintf(stderr, "Process %d terminated by signal %d\n", pid, WTERMSIG(status));
        return -1;
    }
    else
    {
        fprintf(stderr, "Process %d terminated abnormally\n", pid);
        return -1;
    }
}

/**
 * Executes a pipeline of commands separated by the '|' character.
 * @param args An array of command-line arguments.
 * @param num_args The number of command-line arguments.
 * @return The exit status of the last command in the pipeline.
 */
int execute_pipeline(char **args, int num_args)
{
    int i;
    int status = 0;
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
        return execute_command(args);
    }
    else
    {
        return run_logical_operator(args, num_args, operator_pos);
    }
}

/**
 * Parses a pipeline of commands separated by the '|' character.
 * @param line The input string containing the pipeline.
 * @param args An array of command-line arguments.
 * @return The number of command-line arguments.
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

    return num_args;
}

/**
 * Parses a string of command-line arguments separated by whitespace.
 * @param line The input string containing the arguments.
 * @param args An array of command-line arguments.
 * @return The number of command-line arguments.
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

    return num_args;
}

/**
 * Checks if a token is a logical operator.
 * @paramtoken The token to check.
 * @return 1 if the token is a logical operator, 0 otherwise.
 */
int is_logical_operator(char *token)
{
    return strcmp(token, "&&") == 0 || strcmp(token, "||") == 0;
}

/**
 * Executes a pipeline of commands based on the outcome of the previous command.
 * @param args An array of command-line arguments.
 * @param num_args The number of command-line arguments.
 * @param operator_pos The position of the logical operator in the array.
 * @return The exit status of the last command in the pipeline.
 */
int run_logical_operator(char **args, int num_args, int operator_pos)
{
    args[operator_pos] = NULL;

    int status = execute_command(args);

    if (strcmp(args[operator_pos], "&&") == 0 && status == 0)
    {
        return execute_pipeline(args + operator_pos + 1, num_args - operator_pos - 1);
    }
    else if (strcmp(args[operator_pos], "||") == 0 && status != 0)
    {
        return execute_pipeline(args + operator_pos + 1, num_args - operator_pos - 1);
    }
    else
    {
        return status;
    }
}
