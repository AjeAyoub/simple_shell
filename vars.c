#include "shell.h"

/**
 *
 * is_chain Test if current char in buffer is chain delimeter.
 *
 * @info : Parameter struct.
 *
 * @buf : Char buffer.
 *
 * @p : Address of curent positions in buffer.
 *
 * return : 1 if chaine delimeter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';') /* found end of this cmd */
	{
		buf[k] = 0; /* replace semicolon with  Null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 *
 * check_chain checks We should continue chaining based at last status.
 *
 * @info : Parameter struct.
 *
 * @buf : Char buffer.
 *
 * @pc : Address of current position in buff.
 * 
 * @i : Starting position in buff.
 *
 * @len : length of buff.
 *
 * return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 *
 * replace_alias Replaces aliases in tokenized string.
 *
 * @info : parameter struct
 *
 * return: 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int j;
	list_t *node;
	char *b;

	for (j = 0; j < 10; j++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		b = _strchr(node->str, '=');
		if (!b)
			return (0);
		b = _strdup(b + 1);
		if (!b)
			return (0);
		info->argv[0] = b;
	}
	return (1);
}

/**
 *
 * replace_vars Replaces vars in tokenized string.
 *
 * @info : prm struct.
 *
 * return : 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int j = 0;
	list_t *node;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!_strcmp(info->argv[j], "$?"))
		{
			replace_string(&(info->argv[j]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[j], "$$"))
		{
			replace_string(&(info->argv[j]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[j][1], '=');
		if (node)
		{
			replace_string(&(info->argv[j]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[j], _strdup(""));

	}
	return (0);
}

/**
 *
 * replace_string Replaces str.
 *
 * @old : Address of old str.
 *
 * @new : new str.
 *
 * return: 1 if replaced, 0 otherwises.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

