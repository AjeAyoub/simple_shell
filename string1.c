#include "shell.h"

/**
 * _strcpy - Copies a string.
 * @dest: The destination.
 * @src: The source.
 *
 * Return: Pointer to destination.
 */
char *_strcpy(char *dest, char *src)
{
	int ii = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[ii])
	{
		dest[ii] = src[ii];
		ii++;
	}
	dest[ii] = '\0';
	return (dest);
}

/**
 * _strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *rett;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	rett = malloc(sizeof(char) * (length + 1));
	if (!rett)
		return (NULL);
	for (length++; length--;)
		rett[length] = *--str;
	return (rett);
}

/**
 * _puts - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _puts(char *str)
{
	int ii = 0;

	if (!str)
		return;
	while (str[ii] != '\0')
	{
		_putchar(str[ii]);
		ii++;
	}
}

/**
 * _putchar - Writes the character c to stdout.
 * @c: The character to print.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int ii;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ii >= WRITE_BUF_SIZE)
	{
		write(1, buf, ii);
		ii = 0;
	}
	if (c != BUF_FLUSH)
		buf[ii++] = c;
	return (1);
}

