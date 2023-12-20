#include "shell.h"

/**
 * execute_builtin - Execute a built-in command identified in a command struct
 * @cmd: a pointer to the structure representing the command
 * Description: this function include cd, exit, ls, pwd and env.
 *
 * Return: 0 on success or an error code on faillure
 */
int execute_builtin(command_t *cmd)
{
	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
	{
		fprintf(stderr, "Error: Invalid builtin command.\n");
		return (-1);
	}
	if (strcmp(cmd->args[0], "cd") == 0)
	{
		return (execute_cd(cmd));
	}
	else if (strcmp(cmd->args[0], "env") == 0)
	{
		return (execute_env());
	}
	else if (strcmp(cmd->args[0], "ls") == 0)
	{
		return (execute_ls(cmd));
	}
	else if (strcmp(cmd->args[0], "pwd") == 0)
	{
		return (execute_pwd());
	}
	else if (strcmp(cmd->args[0], "exit") == 0)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		fprintf(stderr, "Error: Unknown builtin command: %s\n", cmd->args[0]);
		return (-1);
	}

	return (0);
}

/**
 * execute_cd - Execute the 'cd' built-in command
 * @cmd: the structure command to execute
 *
 * Return: 0 on success or -1 on failure
 */
int execute_cd(command_t *cmd)
{
	if (cmd->args[1] != NULL)
	{
		if (chdir(cmd->args[1]) != 0)
		{
			perror("chdir");
			return (-1);
		}
	}
	else
	{
		fprintf(stderr, "Error: Missing directory argument for 'cd'.\n");
		return (-1);
	}

	return (0);
}

/**
 * execute_ls - execute the 'ls' and 'ls -al' builtin command
 * @cmd: the command to execute
 *
 * Return: 0 on success, or -1 on failure
 */
int execute_ls(command_t *cmd)
{
	if (cmd->args[1] != NULL && strcmp(cmd->args[1], "-al") == 0)
	{
		system("ls -al");
	}
	else if (cmd->args[1] != NULL && strcmp(cmd->args[1], "-l") == 0)
	{
		system("ls -l");
	}
	else
	{
		system("ls");
	}
	return (0);
}

/**
 * execute_pwd - execute the 'pwd' built-in command
 *
 * Return: 0 on success, or -1 on failure
 */
int execute_pwd(void)
{
	char cwd[INPUT_SIZE_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd");
		return (-1);
	}

	return (0);
}

/**
 * execute_env - execute the 'env' built-in command in the simple shell project
 *
 * Return: 0.
 */
int execute_env(void)
{
	system("env");
	return (0);
}
