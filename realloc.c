#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @s: Pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The number of bytes to be filled.
 * Return: Pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int ii;

	for (ii = 0; ii < n; ii++)
		s[ii] = b;
	return (s);
}

/**
 * ffree - Frees a string of strings.
 * @pp: The string of strings.
 */
void ffree(char **pp)
{
	char **aa = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(aa);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous dynamically allocated block.
 * @old_size: The byte size of the previous block.
 * @new_size: The byte size of the new block.
 *
 * Return: Pointer to the reallocated block of memory.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pp;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pp = malloc(new_size);
	if (!pp)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pp[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pp);
}

