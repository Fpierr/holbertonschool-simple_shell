#include "shell.h"

/**
 * get_next_symbol - a lexer function that identificate the symbols type
 * @input: the symbol to input in the terminal
 *
 * Return: the symbol type
 */
symbol_t *get_next_symbol(char *input)
{
	symbol_t *symbol;
	size_t len;
	char *start;

	if (input == NULL || *input == '\0')
		return (NULL);

	symbol = malloc(sizeof(symbol_t));
	if (symbol == NULL)
	{
		fprintf(stderr, "Error: Memory allocation for symbol failed\n");
		exit(EXIT_FAILURE);
	}
	symbol->value = NULL;

	while (*input == ' ' || *input == '\t')
		input++;

	/* Identifiying symbol */
	if (*input == '\0')
	{
		symbol->type = SYMBOL_EOL;
	}
	else if (*input == '|')
	{
		symbol->type = SYMBOL_PIPE;
		symbol->value = strdup("|");
		input++;
	}
	else if (*input == '<')
	{
		symbol->type = SYMBOL_REDIRECT_IN;
		symbol->value = strdup("<");
		input++;
	}
	else if (*input == '>')
	{
		symbol->type = SYMBOL_REDIRECT_OUT;
		symbol->value = strdup(">");
		input++;
	}
	else if (*input == '&')
	{
		symbol->type = SYMBOL_BACKGROUND;
		symbol->value = strdup("&");
		input++;
	}
	else if (*input == ';')
	{
		symbol->type = SYMBOL_SEMICOLON;
		symbol->value = strdup(";");
		input++;
	}
	else
	{
		symbol->type = SYMBOL_WORD;
		start = input;

		while (*input != ' ' && *input != '\t' && *input != '\0' &&
				*input != '|' && *input != '<' && *input != '>' &&
				*input != '&' && *input != ';')
		{
			input++;
		}
		len = input - start;
		symbol->value = malloc(len + 1);
		strncpy(symbol->value, start, len);
		symbol->value[len] = '\0';
	}
	return (symbol);
}

/**
 * free_symbol - free symbol
 * @symbol: the symbol to free
 *
 * Return: void
 */
void free_symbol(symbol_t *symbol)
{
	if (symbol != NULL)
	{
		free(symbol->value);
		free(symbol);
	}
}
