#include "shell.h"

/**
 * display_prompt - Displays the prompt for the shell
 *
 * Return: void
 */
void display_prompt(void)
{
	printf("$ ");
}

/**
 * display_result -  Display the result for execute command in the shell
 * @result: the number to display
 *
 * Return: void
 */
void display_result(int result)
{
	if (result == 0)
	{
		printf("\nCommand executed succefully.`\n");
	}
	else
	{
		printf("\nCommand execution failed");
	}
}

/**
 * display_error - display the error message to execute command
 * @msg: the message to display
 *
 * Return: void
 */
void display_error(const char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
}
