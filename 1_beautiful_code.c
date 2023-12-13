#include <stdio.h>
#include <string.h>

/**
 * main - Entry point main
 * Description: search and print the number of lawercase letter in a string.
 *
 * Return: 0
 */
int main(void)
{
	char str[] = "ADBazerds qazertyuio pmlkjhgf dsqwxcvbn ,;ù";
	int i = 0;
	int len = 0;
	int count = 0;

	while (str[len] != '\0')
	{
		len++;
	}
	for (i = 0; i < len; i++)
	{
		if (str[i] >= 97 && str[i] <= 122)
		{
			putchar(str[i]);
			count++;
		}
	}
	if (count != 0)
		printf("\nThe number of lawercase alphabet is %d\n !", count);
	else
	{
		printf("\nNo lawercase letter found !\n");
	}

	return (0);
}
