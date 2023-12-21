#include "shell.h"

/**
 * main - Entry point main
 * @argc: the number of arguments
 * @argv: the list of arg
 *
 * Return: 0 on success or -1 on failure
 */
int main(int argc, char *argv[])
{
	(void)argv;

	printf("PATH: %s\n", getenv("PATH"));
	if (argc == 1)
	{
		interactive_mode();
	}
	else
	{
		non_interactive_mode();
	}
	return (0);
}
