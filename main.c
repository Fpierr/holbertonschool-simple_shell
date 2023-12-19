#include "shell.h"

<<<<<<< HEAD
/**
 * main - entry point for the shell program
 *
 * display_prompt - displays the shell prompt
 * display_result - displays the result of a command execution
 * @result: the result code of the command execution
 * display_error - displays an error massage
 * @message: the error message to be displayed
 * display_command - displays information about a command
 * @cmd: a pointer to the structure representing the command
 * Return: always 0
 */

int main(void)
{
	display_prompt();

	command_t *cmd;

	cmd.args = (char *[]){"ls", "-l", NULL};
	cmd.input_redirect = NULL;
	cmd.output_redirect = NULL;
	cmd.background = 0;

	display_command(&cmd);

	int result = 0;

	display_result(result);

	const char *errorMessage = "an error occurred";

	display_error(errorMessage);

	return (0);
}
=======
int main(void)
{
	char input[INPUT_SIZE_MAX];
	
	// Initialiser les gestionnaires de signaux
	setup_signal_handlers();

	while (1)
	{
		// Afficher le prompt
		display_prompt();
		
		// Lire la commande de l'utilisateur
		if (fgets(input, INPUT_SIZE_MAX, stdin) == NULL)
		{
			fprintf(stderr, "Error reading input.\n");
			continue;
		}

		// Supprimer le saut de ligne final
		input[strcspn(input, "\n")] = '\0';
		
		// Analyser la ligne de commande
		symbol_t *symbol[INPUT_SIZE_MAX];
		int symbol_count = 0;
		
		symbol_t *current_symbol = get_next_symbol(input);
		while (current_symbol != NULL)
		{
			symbol[symbol_count] = current_symbol;
			symbol_count++;
			current_symbol = get_next_symbol(NULL);
		}
		symbol[symbol_count] = NULL; // Marquer la fin de la liste de symboles
		
		// Ignorer une ligne vide
		if (symbol_count == 0)
		{
			continue;
		}
		// Vérifier les commandes intégrées
		command_t *builtin_cmd = parse_command(symbol);
		if (builtin_cmd != NULL)
		{
			int result = execute_builtin(builtin_cmd);
			display_result(result);
			free_command(builtin_cmd);
		}
		else
		{
			// Exécuter la commande externe
			int result = execute_command(parse_command(symbol));
			display_result(result);
		}
		// Libérer les symboles
		for (int i = 0; i < symbol_count; i++)
		{
			free_symbol(symbol[i]);
		}
	}
	return (0);
}

>>>>>>> 93b89c7c754b62834a7a99a87800e3b8840a0ee4
