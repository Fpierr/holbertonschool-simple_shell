#include "shell.h"

/**
 * execute_builtin - Execute a built-in command identified in a command struct
 * @cmd: a pointer to the structure representing the command
 * Description: this function include cd and exit.
 *
 * Return: 0 on success or an error code on faillure
 */
int execute_builtin(command_t *cmd)
{
	if (cmd == NULL || cmd->args[0] == NULL || cmd->args == NULL)
	{
		fprintf(stderr, "Error: Invalid builtin command.\n");
		return (-1);
	}
	if (strcmp(cmd->args[0], "cd") == 0)
	{
		if (cmd->args[1] != NULL)
		{
			if (cmd->args[1] != 0)
			{
				perror("chdir");
				return (-1);
			}
		}
		else
		{
			fprintf(stderr, "Error: MIssing directory argument for 'cd'.\n");
			return (-1);
		}
	}
	else if (strcmp(cmd->args[0], "exit") == 0)
		exit(EXIT_SUCCESS);
	else
	{
		fprintf(stderr, "Error: Unknown builtin command: %s\n", cmd->args[0]);
		return (-1);
	}

	return (0);
}
