#include "shell.h"

/**
 * print_parent_pid - print the parent process PID
 *
 * Return: Always 0.
 */
int print_parent_pid(void)
{
	pid_t my_pid;

	my_pid = getpid();
	printf("\nPid du processus parend : %u\n", my_pid);
		return (0);
}
