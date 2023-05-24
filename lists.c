#include "shell.h"

/**
 * add_node Adds a node to the start of the list
 *
 * @head : Address of pointer to head node.
 *
 * @strc: Str field of node.
 *
 * @num : node index used by history.
 *
 * return: size of list.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_hd;

	if (!head)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	_memset((void *)new_hd, 0, sizeof(list_t));
	new_hd->num = num;
	if (str)
	{
		new_hd->str = _strdup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *head;
	*head = new_hd;
	return (new_hd);
}

/**
 *
 * Add_node_end Adds  node to end of the list.
 *
 * @head : address of pointer to head node.
 *
 * @str : str field of node.
 *
 * @num : node index used by history.
 *
 * return : size of listd.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nd, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_nd = malloc(sizeof(list_t));
	if (!new_nd)
		return (NULL);
	_memset((void *)new_nd, 0, sizeof(list_t));
	new_nd->num = num;
	if (str)
	{
		new_nd->str = _strdup(str);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_nd;
	}
	else
		*head = new_nd;
	return (new_nd);
}

/**
 * Print_list_str Prints only the str element of a list_t linked list
 * @h : pointer to first node.
 *
 * return: size of list.
 *
 */
size_t print_list_str(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 *
 * Delete_node_at_index Delete node at given indx
 *
 * @head : Address of pointer to first node.
 *
 * @index : index of node to delete.
 *
 * return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * Free_list Frees all nodes of a list
 *
 * @head_ptr : Address of pointer to head node.
 *
 *
 * return: void.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_nd, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_nd = node->next;
		free(node->str);
		free(node);
		node = next_nd;
	}
	*head_ptr = NULL;
}

