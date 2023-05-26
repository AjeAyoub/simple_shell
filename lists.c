#include "shell.h"

/**
 * add_node - Adds a node to the start of the list.
 * @head: Address of pointer to head node.
 * @str: String field of the node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the new head of the list.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_headd;

	if (!head)
		return (NULL);
	new_headd = malloc(sizeof(list_t));
	if (!new_headd)
		return (NULL);
	_memset((void *)new_headd, 0, sizeof(list_t));
	new_headd->num = num;
	if (str)
	{
		new_headd->str = _strdup(str);
		if (!new_headd->str)
		{
			free(new_headd);
			return (NULL);
		}
	}
	new_headd->next = *head;
	*head = new_headd;
	return (new_headd);
}

/**
 * add_node_end - Adds a node to the end of the list.
 * @head: Address of pointer to head node.
 * @str: String field of the node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the new node.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nod, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	_memset((void *)new_nod, 0, sizeof(list_t));
	new_nod->num = num;
	if (str)
	{
		new_nod->str = _strdup(str);
		if (!new_nod->str)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_nod;
	}
	else
		*head = new_nod;
	return (new_nod);
}

/**
 * print_list_str - Prints only the str element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: The number of nodes in the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t ii = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		ii++;
	}
	return (ii);
}

/**
 * delete_node_at_index - Deletes a node at the given index.
 * @head: Address of pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_nod;
	unsigned int ii = 0;

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
		if (ii == index)
		{
			prev_nod->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		ii++;
		prev_nod = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Frees all nodes of a list.
 * @head_ptr: Address of pointer to the head node.
 *
 * Return: void.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_nod, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_nod = node->next;
		free(node->str);
		free(node);
		node = next_nod;
	}
	*head_ptr = NULL;
}
