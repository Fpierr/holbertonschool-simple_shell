#ifndef _SHELL_H_
#define _SHELL_H_

#define INPUT_SIZE_MAX 1024

/* header file library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

/**
 * enum symbol_type_s - Enumeration of the symbol to create a simple shell
 * @SYMBOL_UNKNOWN: a symbol that unknown
 * @SYMBOL_WORD: a symbol that known
 * @SYMBOL_REDIRECT_IN: symbol of redirection in for exemple (<)
 * @SYMBOL_REDIRECT_OUT: a symbol of redirection out (>)
 * @SYMBOL_PIPE: the pipe symbol that separate 2 commands (|)
 * @SYMBOL_BACKGROUND: indicates that the command is execute in background (&)
 * @SYMBOL_SEMICOLON: represente a simicolon (;)
 * @SYMBOL_EOL: indicate the end of a command
 *
 * Description: to enumerate the symbol to use to create the simple shell
 */
typedef enum symbol_type_s
{
	SYMBOL_UNKNOWN,
	SYMBOL_WORD,
	SYMBOL_REDIRECT_IN,
	SYMBOL_REDIRECT_OUT,
	SYMBOL_PIPE,
	SYMBOL_BACKGROUND,
	SYMBOL_SEMICOLON,
	SYMBOL_EOL
} symbol_type_t;

/**
 * struct symbol_s - the structure of the symbol to use
 * @type: the type of symbol
 * @value: a pointer to a string that content associate associate to a symbol
 */
typedef struct symbol_s
{
	symbol_type_t type;
	char *value;
} symbol_t;

symbol_t *get_next_symbol(char *input);
void free_symbol(symbol_t *symbol);
extern char **environ;

/**
 * struct command_s - analyze of syntaxe
 * @args: number of argument to pass in command line
 * @input_redirect: input redicrection (<)
 * @output_redirect: output of redirection (>)
 * @background: in the background
 */
typedef struct command_s
{
	char **args;
	char *input_redirect;
	char *output_redirect;
	int background;
} command_t;

command_t *parse_command(symbol_t **symbol);
void free_command(command_t *cmd);
int execute_command(command_t *cmd);
int execute_direct_command(command_t *cmd);
int execute_command_in_path(command_t *cmd);
int execute_builtin(command_t *cmd);
int execute_cd(command_t *cmd);
int execute_exit(void);
int execute_ls(command_t *cmd);
int execute_pwd(void);
int execute_env(void);
void handle_signal(int signo);
void setup_signal_handlers(void);
int print_parent_pid(void);
void display_prompt(void);
void display_result(int result);
void display_error(const char *msg);
void display_command(command_t *cmd);
void interactive_mode(void);
void non_interactive_mode(void);
char *get_path(char *cmd);

#endif /* SHELL_H */
