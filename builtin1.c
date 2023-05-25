#include "shell.h"

/**
 * _myhistory - displays the history list, one command per line,
 *              preceded by line numbers starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 *
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - removes an alias from the alias list
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, cc;
	int rett;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	cc = *p;
	*p = 0;
	rett = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = cc;
	return (rett);
}

/**
 * set_alias - sets an alias to a string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *aa = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (aa = node->str; aa <= p; a++)
			_putchar(*aa);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *         a constant function prototype.
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int ii = 0;
	char *p = NULL;
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
	for (ii = 1; info->argv[ii]; ii++)
	{
		p = _strchr(info->argv[ii], '=');
		if (p)
			set_alias(info, info->argv[ii]);
		else
			print_alias(node_starts_with(info->alias, info->argv[ii], '='));
	}

	return (0);
}

