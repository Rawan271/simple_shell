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


#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

/* Function prototypes */
int execute_command(char **args);
int execute_pipeline(char **args, int num_args);
int parse_pipeline(char *line, char **args);
int parse_args(char *line, char **args);
int is_logical_operator(char *token);
int run_logical_operator(char **args, int num_args, int operator_pos);

void print_prompt(void);
void read_input(char *input);
void parse_input(char *input, char **args);
int is_builtin(char *command);
void handle_builtin(char **args);
void handle_external(char **args);
void handle_error(char *message);

#endif /* SHELL_  */
