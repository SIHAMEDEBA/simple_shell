#include "main.h"

/**
 * interactive - returns true if main is interactive mode
 * @inf: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: char to check
 * @delimiter: delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, fg = 0, output;
	unsigned int resultat = 0;

	for (i = 0; s[i] != '\0' && fg != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			fg = 1;
			resultat *= 10;
			resultat += (s[i] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sign == -1)
		output = -resultat;
	else
		output = resultat;

	return (output);
}
