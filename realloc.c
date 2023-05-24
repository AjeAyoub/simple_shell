#include "shell.h"

/*
 * *
 * memset Fills memory with constant byte.
 *
 * @s : Pointer to memory area.
 *
 * @b : Byte to fill *s with.
 * @n : Amount of bytes to be filled.
 *
 * return : s pointer to memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 *
 * ffree Frees String of strings.
 *
 * @pp : Str of strings
 */
void ffree(char **pp)
{
	char **b = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(b);
}

/**
 *
 * realloc Reallocates block of memory
 *
 * @ptr : pointer to previous malloc'ated Block.
 *
 * @old_size : Byte size of previous block.
 *
 * @new_size : Byte size of new block.
 *
 * return : pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

