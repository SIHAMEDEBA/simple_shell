#include "main.h"

/**
 * our_hst - displays history list, one cmd by line, preceded
 *              with line numbers, starting at 0.
 * @inf: strctr containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int our_hst(info_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * alias_str - sets alias to string
 * @inf: parameter struct
 * @str: string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_str(info_t *inf, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = dlt_nodex(&(inf->alias),
		node_getindex(inf->alias, node_strt(inf->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * alias_str1 - sets alias to string
 * @inf: parameter struct
 * @str: string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_str1(info_t *inf, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (alias_str(inf, str));

	alias_str(inf, str);
	return (end_node(&(inf->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics alias builtin (man alias)
 * @inf: strctr containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *inf)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		p = _strchr(inf->argv[i], '=');
		if (p)
			alias_str1(inf, inf->argv[i]);
		else
			print_alias(node_strt(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
