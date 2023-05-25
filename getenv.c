#include "shell.h"

/**
 * get_environ - Returns the string array copy of our environ.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: String array copy of environ.
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
 * _unsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * @var: The string env var property.
 * Return: 1 on delete, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t ii = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), ii);
			ii = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		ii++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * @var: The string env var property.
 * @value: The string env var value.
 * Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *pp;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		pp = starts_with(node->str, var);
		if (pp && *pp == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

