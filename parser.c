#include "shell.h"

/**
 * parse_command - fonction to alayze a command symbol
 * @symbol: the symbol to parse
 *
 * Return: 0 on success, -1 on faillure
 */
command_t *parse_command(symbol_t **symbol)
{
	int i = 0;

	command_t *cmd = malloc(sizeof(command_t));

	if (cmd == NULL)
	{
		fprintf(stderr, "Error: Memory allocation for command structure failed.\n");
		return (NULL);
	}
	cmd->args = NULL;
	cmd->input_redirect = NULL;
	cmd->output_redirect = NULL;
	cmd->background = 0;

	if (symbol == NULL || *symbol == NULL)
		return (NULL);
	while (symbol[i] != NULL)
	{
		if (symbol[i]->type == SYMBOL_WORD)
		{
			cmd->args = realloc(cmd->args, (i + 2) * sizeof(char *));
			cmd->args[i] = strdup(symbol[i]->value);
			cmd->args[i + 1] = NULL;
		}
		else if (symbol[i]->type == SYMBOL_REDIRECT_IN)
		{
			i++;
			if (symbol[i] != NULL && symbol[i]->type == SYMBOL_WORD)
				cmd->input_redirect = strdup(symbol[i]->value);
			else
			{
				fprintf(stderr, "Error: Missing filename alter '<'.\n");
				free_command(cmd);
				return (NULL);
			}
		}
		else if (symbol[i]->type == SYMBOL_REDIRECT_OUT)
		{
			i++;
			if (symbol[i] != NULL && symbol[i]->type == SYMBOL_WORD)
				cmd->output_redirect = strdup(symbol[i]->value);
			else
			{
				fprintf(stderr, "Error: Missing filename alter '>'.\n");
				free_command(cmd);
				return (NULL);
			}
		}
		else if (symbol[i]->type == SYMBOL_BACKGROUND)
			cmd->background = 1;
		i++;
	}
	return (cmd);
}

/**
 * free_command - function to free a command structure memory
 * @cmd: the command structure to free
 *
 * Return: void
 */
void free_command(command_t *cmd)
{
	int i = 0;

	if (cmd != NULL)
	{
		if (cmd->args != NULL)
		{
			for (i = 0; cmd->args[i] != NULL; i++)
				free(cmd->args[i]);
			free(cmd->args);
		}
		free(cmd->input_redirect);
		free(cmd->output_redirect);
		free(cmd);
	}
}
