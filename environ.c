#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *         a constant function prototype.
 *
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *         a constant function prototype.
 * @name: env variable name
 *
 * Return: The value of the variable
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *pp;

	while (node)
	{
		pp = starts_with(node->str, name);
		if (pp && *pp)
			return (pp);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - initializes a new environment variable or modifies an existing
 * one
 * @info: Structure containing potential arguments. Used to maintain
 *         a constant function prototype.
 *
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *         a constant function prototype.
 *
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int ii;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (ii = 1; ii < info->argc; ii++)
		_unsetenv(info, info->argv[ii]);

	return (0);
}

/**
 * populate_env_list - populates the environment linked list
 * @info: Structure containing potential arguments. Used to
 * maintain
 *         a constant function prototype.
 *
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t ii;

	for (ii = 0; environ[ii]; ii++)
		add_node_end(&node, environ[ii], 0);
	info->env = node;
	return (0);
}

