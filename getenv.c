#include "shell.h"

/**
 * get_environ returns the string array copy of our environ
 *
 * @info : Structure containing potential arguments.
 * Used to maintaiin.
 * constant functions prototype.
 *
 * Return: Always 0
 *
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unsetenv Remove an environment variable
 *
 * @info : Structure containing potential arguments.
 * Used to maintaiin.
 *  constant function prototype
 *  Return: 1 on delete, 0 otherwise.
 *
 * @var : the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t j = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * Setenv initialize a new environment variable.
 *  Or modify an existing one
 * @info : structure containing potential arguments.
 * used to maintain.
 *
 *    constant function prototype.
 * @var : the string env var property.
 * @value: the string env var value.
 *
 *  return: always 0
 *
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *b;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		b = starts_with(node->str, var);
		if (b && *b == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

