#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64
int execute_command(char **args);
int execute_pipeline(char **args, int num_args);
int parse_pipeline(char *line, char **args);
int parse_args(char *line, char **args);
int is_logical_operator(char *token);
int run_logical_operator(char **args, int num_args, int operator_pos);
/* Function prototypes */
void print_prompt(void);
void read_input(char *input);
void parse_input(char *input, char **args);
void execute_command(char **args);
int is_builtin(char *command);
void handle_builtin(char **args);
void handle_external(char **args);
void handle_error(char *message);

#endif /* SHELL_  */
