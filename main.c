#include "shell.h"

int main(void)
{
	char input[INPUT_SIZE_MAX];
	int symbol_count = 0;
	symbol_t *symbol[INPUT_SIZE_MAX], *current_symbol;
	command_t *builtin_cmd;
	int result, i;

	setup_signal_handlers(); /* initialize the manage signal */
	while (1)
	{
		display_prompt(); /* Display the prompt */
		if (fgets(input, INPUT_SIZE_MAX, stdin) == NULL)
		{
			fprintf(stderr, "Error reading input.\n");
			continue;
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
			display_result(result);
			free_command(builtin_cmd);
		}
		else /* Exeute the extern command */
		{
			result = execute_command(parse_command(symbol));
			display_result(result);
		}
		for (i = 0; i < symbol_count; i++) /* free symbols */
			free_symbol(symbol[i]);
	}
	return (0);
}
