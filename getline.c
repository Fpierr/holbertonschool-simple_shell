#include "shell.h"

/**
 * getline_sh - Read and display a command from the user.
 *
 * Return: 0 on success, 1 on failure.
 */
int getline_sh(void)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t read_line;

	if (isatty(STDIN_FILENO))
	{
		display_prompt();
	}
	read_line = getline(&line, &n, stdin);
	if (read_line == -1)
	{
		perror("Error reading the command");
		return (1);
	}
	printf("Command read: %s", line);
	free(line);
	return (0);
}
