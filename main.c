#include "main.h"

/**
 *tokenization - function for the custom shell program.
 *
 *@inputLine: The number of command-line arguments
 *@argv: An array of command-line argument strings
 *@charsRead: charact read
 * Return:0 successful -1 error
 */

int tokenization(char *inputLine, char **argv, ssize_t charsRead)
{
	char *inputLineCopy = NULL, *token;
	const char *delimiter = " \n";
	int tokenCount = 0, index;

	inputLineCopy = malloc(sizeof(char) * charsRead);

	if (inputLineCopy == NULL)
	{
		perror("myshell: memory allocation error");
		return (-1);
	}
	strcpy(inputLineCopy, inputLine);
	token = strtok(inputLine, delimiter);
	while (token != NULL)
	{
		tokenCount++;
		token = strtok(NULL, delimiter);
	}
	tokenCount++;
	argv = malloc(sizeof(char *) * tokenCount);
	token = strtok(inputLineCopy, delimiter);
	token = strtok(NULL, delimiter);
	for (index = 0; token != NULL; index++)
	{
		argv[index] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[index], token);
		token = strtok(NULL, delimiter);
	}
	argv[index] = NULL;
	execmd(argv);
	free(inputLineCopy);
	return (0);
}

/**
 * main - function of the shell program.
 *
 * @argc: number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Return: Returns integer
 */

int main(int argc, char **argv)
{
	char *shellPrompt = "(MyShell) $ ";
	char *inputLine = NULL;
	size_t bufferSize = 0;
	ssize_t charsRead;

	(void)argc;

	while (1)
	{
		printf("%s", shellPrompt);
		charsRead = getline(&inputLine, &bufferSize, stdin);
		if (charsRead == -1)
		{
			printf("Exiting shell....\n");
			return (-1);
		}

		tokenization(inputLine, argv, charsRead);
	}
	free(inputLine);
	return (0);
}
