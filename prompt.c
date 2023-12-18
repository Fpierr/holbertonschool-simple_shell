#include "shell"

/**
 * display_prompt - displays the prompt
 *
 * Return: void
 */
void display_prompt(void)
{
printf("$ ");
}
/**
 * display_result - displays the result of a commande execution
 * @result: the result code of the command
 * Return: void
 */
void display_result(int result)
{
	if (result == 0)
	{
		printf("command executed successfully.\n");
	}
	else
	{
		printf("command execution failed.\n");
	}
}
/**
 * display_error - displays an error message
 * @message: the error message to display
 * Return: void
 */
void display_error(const char *message)
{
	fprintf(stderr, "Error: %s\n", message);
}
/**
 * display_command - displays information about a command
 * @cmd: a pointer to the command structure
 * Return: void
 */
void display_command(command_t *cmd)
{
	if (cmd == NULL || cmd->args == NULL || cmd->args[0] == NULL)
	{
		fprintf(stderr, "Error: invalid command.\n");
		return;
	}
	printf("command:");

	for (int i = 0; cmd->args[i] != NULL; i++)
	{
		printf("%s ", cmd->args[i]);
	}
	printf("\n");

	if (cmd->input_redirect != NULL)
	{
		printf("input redirect: %s\n", cmd->input_redirect);
	}
	if (cmd->output_redirect != NULL)
	{
	printf("output redirect: %s\n", cmd->output_redirect);
	}
	if (cmd->blackground)
	{
	printf("blackground execution: yes\n");
	}
}
