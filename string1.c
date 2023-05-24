#include "shell.h"

/**
 *
 * strcpy Copies a string
 *
 * @dest : Destination.
 *
 * @src : Source
 *
 * return : Pointer to destination.
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 *
 * strdup Duplicates Strg.
 *
 * @str : String to duplicate.
 *
 * return : pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int lth = 0;
	char *rt;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lth++;
	rt = malloc(sizeof(char) * (lth + 1));
	if (!rt)
		return (NULL);
	for (lth++; lth--;)
		rt[lth] = *--str;
	return (rt);
}

/**
 *
 * puts Prints input string.
 *
 * @str : Strg to be printed.
 *
 * return : Nothing.
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 *
 * putchar Writes character c to stdout.
 *
 * @c : Character to print.
 *
 * return : On success 1.
 * On errors, -1 is returned, & errno is set appropriately.
 */
int _putchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

