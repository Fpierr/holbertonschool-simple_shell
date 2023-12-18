#include "shell.h"

/**
 * handle_signal - funtion that handles (manage) a signal receive by the shell
 * @signo: the signal number indicating the type of signal received
 *
 * Return: void
 */
static void handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		printf("\nReceived Ctrl+C\n");
	}
	else if (signo == SIGTSTP)
	{
		printf("\nReceived Ctrl+Z\n");
	}
}

/**
 * setup_signal_handlers - This function set up signal handlers for the shell
 * It installs signal handlers for SIGINT (Ctrl+C) and SIGTSTP (Ctrl+Z)
 *
 * Return: void
 */
void setup_signal_handlers(void)
{
	if (signal(SIGINT, handle_signal) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGTSTP, handle_signal) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
}
