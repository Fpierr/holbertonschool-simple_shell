#include "shell.h"

/**
 * interactive_mode - define de interactive mode in the shell
 *
 * Return: void
 */
void interactive_mode(void)
{
	char input[INPUT_SIZE_MAX];
	int symbol_count;
	symbol_t *symbol[INPUT_SIZE_MAX];
	symbol_t *current_symbol;
	command_t *builtin_cmd;
	int result, i;

	setup_signal_handlers();
	while (1)
	{
		display_prompt(); /* Display prompt */
		if (fgets(input, INPUT_SIZE_MAX, stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\nReceived Ctrl+D (EOF)\n");
				break;
			}
			else
			{
				perror("Error reading input.\n");
				continue;
			}
		}
		input[strcspn(input, "\n")] = '\0';
		symbol_count = 0;

		current_symbol = get_next_symbol(input);
		while (current_symbol != NULL)
		{
			symbol[symbol_count] = current_symbol;
			symbol_count++;
			current_symbol = get_next_symbol(NULL);
		}
		if (strcmp(symbol[0]->value, "exit") == 0)
		{
			for (i = 0; i < symbol_count; i++)
				free_symbol(symbol[i]);
			exit(EXIT_SUCCESS);
		}
		builtin_cmd = parse_command(symbol); /* check the builtin command */
		if (builtin_cmd != NULL)
		{
			result = execute_builtin(builtin_cmd);
			free_command(builtin_cmd);
		}
		else
		{
			result = execute_command(parse_command(symbol));
		}
		for (i = 0; i < symbol_count; i++)
			free_symbol(symbol[i]);
		display_result(result);
	}
}

/**
 * non_interactive_mode - define mode of extern command in the shell
 *
 * Return: void
 */
void non_interactive_mode(void)
{
	char input[INPUT_SIZE_MAX];
	int symbol_count = 0;
	symbol_t *symbol[INPUT_SIZE_MAX];
	symbol_t *current_symbol;
	command_t *builtin_cmd;
	int result, i;

	while (fgets(input, INPUT_SIZE_MAX, stdin) != NULL)
	{
		input[strcspn(input, "\n")] = '\0';
		symbol_count = 0;

		current_symbol = get_next_symbol(input);
		while (current_symbol != NULL)
		{
			symbol[symbol_count] = current_symbol;
			symbol_count++;
			current_symbol = get_next_symbol(NULL);
		}
		if (strcmp(symbol[0]->value, "exit") == 0)
		{
			for (i = 0; i < symbol_count; i++)
				free_symbol(symbol[i]);
			exit(EXIT_SUCCESS);
		}
		builtin_cmd = parse_command(symbol);
		if (builtin_cmd != NULL)
		{
			result = execute_builtin(builtin_cmd);
			free_command(builtin_cmd);
		}
		else
		{
			result = execute_command(parse_command(symbol));
		}
		for (i = 0; i < symbol_count; i++)
			free_symbol(symbol[i]);
		display_result(result);
	}
}
