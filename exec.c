#include "shell.h"
#include <fcntl.h>

/**
 * execute_command - fonction to execute a command in the simple shell
 * @cmd: the command to execute
 *
 * Return: 0 on success, or -1 on failure
 */
int execute_command(command_t *cmd)
{
	pid_t pid;

	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
	{
		fprintf(stderr, "Error: Invalid command.\n");
		return (-1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		execute_child_process(cmd);
	}
	else
	{
		execute_parent_process(cmd, pid);
	}
	return (0);
}

/**
 * execute_child_process - function tha execute the child process
 * @cmd: the command chile process to execute
 *
 * Return: void
 */
void execute_child_process(command_t *cmd)
{
	int fd;

	if (cmd->input_redirect != NULL)
	{
		fd = open(cmd->input_redirect, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->output_redirect != NULL)
	{
		fd = open(cmd->output_redirect, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (execvp(cmd->args[0], cmd->args) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

/**
 * execute_parent_process - fonction to execute the parent process of a command
 * @cmd: the command to process execute
 * @child_pid: the process ID of the child process
 *
 * Return: void
 */
void execute_parent_process(command_t *cmd, pid_t child_pid)
{
	int status;

	if (!cmd->background)
	{
		waitpid(child_pid, &status, 0);
	}
}
