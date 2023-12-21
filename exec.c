#include "shell.h"

/**
 * execute_command - fonction to execute a command in the simple shell
 * @cmd: the command to execute
 *
 * Return: 0 on success, or -1 on failure
 */
int execute_command(command_t *cmd)
{
	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
	{
		fprintf(stderr, "Error: Invalid command.\n");
		return (-1);
	}

	if (strchr(cmd->args[0], '/') != NULL)
	{
		return (execute_direct_command(cmd));
	}
	else
	{
		return (execute_command_in_path(cmd));
	}
	return (0);
}

/**
 * execute_direct_command - Execute a command given with a full path
 * @cmd: a pointer to the structure representing the command
 *
 * Return: 0 on success, or -1 on failure
 */
int execute_direct_command(command_t *cmd)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		execve(cmd->args[0], cmd->args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (WIFEXITED(status) ? WEXITSTATUS(status) : -1);
	}

	return (0);
}

/**
 * execute_command_in_path - Search for and execute a command in PATH
 * @cmd: a pointer structure representing the command
 *
 * Return: 0 on success or -1 on failure
 */
int execute_command_in_path(command_t *cmd)
{
	char *path;
	char *path_copy;
	char *symbol;
	char *full_path;
	int status = -1;

	path = getenv("PATH");
	path_copy = strdup(path);
	symbol = strtok(path_copy, ":");

	while (symbol != NULL)
	{
		full_path = malloc(strlen(symbol) + strlen(cmd->args[0]) + 2);
		sprintf(full_path, "%s/%s", symbol, cmd->args[0]);

		if (access(full_path, X_OK) == 0)
		{
			status = execute_direct_command(cmd);
			free(full_path);
			break;
		}
		free(full_path);
		symbol = strtok(NULL, ":");
	}
	free(path_copy);

	return (status);
}
