#include "shell.h"

/**
 *
 * List_len Determines length of linked list
 * @h : pointer to first node.
 *
 * return : size of list.
 *
 */
size_t list_len(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 *
 * List_to_strings Returns array of strings of list->str.
 *
 * @head : pointer to first node.
 *
 * return: array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t j = list_len(head), k;
	char **strs;
	char *str;

	if (!head || !j)
		return (NULL);
	strs = malloc(sizeof(char *) * (j + 1));
	if (!strs)
		return (NULL);
	for (j = 0; node; node = node->next, j++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < j; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[j] = str;
	}
	strs[j] = NULL;
	return (strs);
}


/**
 *
 * Print_list prints all elements of  list_t linked list
 *
 * @h : Pointer to first node.
 *
 *
 * return : size of list.
 */
size_t print_list(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 *
 * node_starts_with Returns node whose str starts with prefix
 *
 * @node : Pointer to list head.
 *
 * @prefix : string to match.
 *
 * @c : Next character after prefix to match.
 *
 * return: match node or null.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *b = NULL;

	while (node)
	{
		b = starts_with(node->str, prefix);
		if (b && ((c == -1) || (*b == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 *
 * get_node_index Gets the index of a node
 *
 * @head : Pointer to list head.
 *
 * @node : Pointer to the node.
 *
 * return : index of node or -1.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}

