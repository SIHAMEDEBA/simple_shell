#include "main.h"

/**
 * our_env - prints current environment
 * @inf: strctr containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int our_env(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * _getenv - gets value of an environ variable
 * @inf: strctr containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: value
 */
char *_getenv(info_t *inf, const char *name)
{
	list_t *node = inf->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * oursetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: strctr containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int oursetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @inf: strctr containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetenv(inf, inf->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @inf: strctr containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *inf)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		end_node(&node, environ[i], 0);
	inf->env = node;
	return (0);
}
