#include "shell.h"

/**
 * main - Simple Shell (Hsh)
 * @argc: Argument Count
 * @argv:Argument Value
 * Return: Exit Value By Status
 */

int main(__attribute__((unused)) int argc, char **argv)
{
	char *input, **cmd;
	int cont = 0, statue = 1, st = 0;

	if (argv[1] != NULL)
		read_file(argv[1], argv);
	signal(SIGINT, signal_to_handel);
	while (statue)
	{
		cont++;
		if (isatty(STDIN_FILENO))
			prompt();
		input = _getline();
		if (input[0] == '\0')
		{
			continue;
		}
		history(input);
		cmd = parse_cmd(input);
		if (_strcmp(cmd[0], "exit") == 0)
		{
			exit_bul(cmd, input, argv, cont);
		}
		else if (check_builtin(cmd) == 0)
		{
			st = handle_builtin(cmd, st);
			free_all(cmd, input);
			continue;
		}
		else
		{
			st = check_cmd(cmd, input, cont, argv);

		}
		free_all(cmd, input);
	}
	return (statue);
}
/**
 * check_builtin - check builtin
 *
 * @cmd:command to check
 * Return: 0 Succes -1 Fail
 */
int check_builtin(char **cmd)
{
	bul_t fun[] = {
		{"cd", NULL},
		{"help", NULL},
		{"echo", NULL},
		{"history", NULL},
		{NULL, NULL}
	};
	int ii = 0;
		if (*cmd == NULL)
	{
		return (-1);
	}

	while ((fun + ii)->command)
	{
		if (_strcmp(cmd[0], (fun + ii)->command) == 0)
			return (0);
		ii++;
	}
	return (-1);
}
/**
 * creat_envi - Creat Array of Enviroment Variable
 * @envi: Array of Enviroment Variable
 * Return: Void
 */
<<<<<<< HEAD
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
=======
void creat_envi(char **envi)
{
	int ii;

	for (ii = 0; environ[ii]; ii++)
		envi[ii] = _strdup(environ[ii]);
	envi[ii] = NULL;
>>>>>>> 1d2743e0d9b9b3a40f7b97f68a3f7cbd5eccc4f3
}
