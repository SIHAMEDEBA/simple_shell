#include "main.h"

/**
 * execmd -  command with the given arguments.
 *
 * @argv: array of strings
 * Return: void
 */

void execmd(char **argv)
{
	char *command = NULL;

	if (argv)
	{
		command = argv[0];
		if (execve(command, argv, NULL) == -1)
		{
			perror("Error:");
		}
	}
}
