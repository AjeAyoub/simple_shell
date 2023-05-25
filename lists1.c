#include "shell.h"

/**
 * list_len - Determines the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t list_len(const list_t *h)
{
	size_t ii = 0;

	while (h)
	{
		h = h->next;
		ii++;
	}
	return (ii);
}

/**
 * list_to_strings - Returns an array of strings from the list->str elements.
 * @head: Pointer to the first node.
 *
 * Return: An array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t ii = list_len(head), jj;
	char **strs;
	char *str;

	if (!head || !ii)
		return (NULL);
	strs = malloc(sizeof(char *) * (ii + 1));
	if (!strs)
		return (NULL);
	for (ii = 0; node; node = node->next, ii++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (jj = 0; jj < ii; jj++)
				free(strs[jj]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[ii] = str;
	}
	strs[ii] = NULL;
	return (strs);
}

/**
 * print_list - Prints all elements of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t ii = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		ii++;
	}
	return (ii);
}

/**
 * node_starts_with - Returns the node whose string starts with a prefix.
 * @node: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: The matched node or NULL if not found.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *pp = NULL;

	while (node)
	{
		pp = starts_with(node->str, prefix);
		if (pp && ((c == -1) || (*pp == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in a linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: The index of the node, or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t ii = 0;

	while (head)
	{
		if (head == node)
			return (ii);
		head = head->next;
		ii++;
	}
	return (-1);
}

