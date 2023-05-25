#include "shell.h"

/**
 * is_chain - Tests if the current char in the buffer is a chain delimiter.
 * @info: The parameter struct.
 * @buf: The char buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t jj = *p;

	if (buf[jj] == '|' && buf[jj + 1] == '|')
	{
		buf[jj] = '\0';
		jj++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[jj] == '&' && buf[jj + 1] == '&')
	{
		buf[jj] = '\0';
		jj++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[jj] == ';') /* Found end of this command */
	{
		buf[jj] = '\0'; /* Replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = jj;
	return (1);
}

/**
 * check_chain - Checks if we should continue chaining based on
 * the last status.
 * @info: The parameter struct.
 * @buf: The char buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t jj = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = '\0';
			jj = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = '\0';
			jj = len;
		}
	}

	*p = jj;
}

/**
 * replace_alias - Replaces an alias in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int ii;
	list_t *node;
	char *pp;

	for (ii = 0; ii < 10; ii++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int ii = 0;
	list_t *node;

	for (ii = 0; info->argv[ii]; ii++)
	{
		if (info->argv[ii][0] != '$' || !info->argv[ii][1])
			continue;

		if (!_strcmp(info->argv[ii], "$?"))
		{
			replace_string(&(info->argv[ii]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[ii], "$$"))
		{
			replace_string(&(info->argv[ii]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[ii][1], '=');
		if (node)
		{
			replace_string(&(info->argv[ii]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[ii], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

