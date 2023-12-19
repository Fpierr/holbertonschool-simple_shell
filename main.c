#include "shell.h"

/**
 * main - entry point for the shell program
 *
 * display_prompt - displays the shell prompt
 * display_result - displays the result of a command execution
 * @result: the result code of the command execution
 * display_error - displays an error massage
 * @message: the error message to be displayed
 * display_command - displays information about a command
 * @cmd: a pointer to the structure representing the command
 * Return: always 0
 */

int main(void)
{
	display_prompt();

	command_t *cmd;

	cmd.args = (char *[]){"ls", "-l", NULL};
	cmd.input_redirect = NULL;
	cmd.output_redirect = NULL;
	cmd.background = 0;

	display_command(&cmd);

	int result = 0;

	display_result(result);

	const char *errorMessage = "an error occurred";

	display_error(errorMessage);

	return (0);
}
