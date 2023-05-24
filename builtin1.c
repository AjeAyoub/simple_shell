#include "shell.h"

/**
 * myhistory - displays the history list, one command by line,
 * preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * @
 * return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset - alias sets alias to string.
 * @info: parameter struct.
 *
 * @str: the string alias.
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *b, s;
	int rt;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	s = *b;
	*b = 0;
	rt = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*b = s;
	return (rt);
}

/**
 * set alias sets alias to string.
 * @info: parameter struct.
 *
 * @str: the string alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print alias prints an alias string.
 *
 * @node : the alias node.
 *
 * Return : Always 0 on success, 1 on error.
 *
 */
int print_alias(list_t *node)
{
	char *b = NULL, *h = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (h = node->str; h <= b; h++)
		_putchar(*h);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 *
 * myalias mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 * Used to maintain.
 *
 * constant function  prototype.
 *  Return: Always 0.
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		b = _strchr(info->argv[j], '=');
		if (b)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}

