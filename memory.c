#include "shell.h"

/**
 *
 * Bfree frees a pointer & NULLs the address
 *
 * @ptr : Address of pointer to free.
 *
 * return : 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

