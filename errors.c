#include "shell.h"

/**
 * _eputs - prints a string to stderr
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int ii = 0;

	if (!str)
		return;
	while (str[ii] != '\0')
	{
		_eputchar(str[ii]);
		ii++;
	}
}

/**
 * _eputchar - writes the character 'c' to stderr
 * @c: The character to print
 *
 * Return: On success 1. On error, -1 is returned, and errno is set
 * appropriately.
 */
int _eputchar(char c)
{
	static int ii;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ii >= WRITE_BUF_SIZE)
	{
		write(2, buf, ii);
		ii = 0;
	}
	if (c != BUF_FLUSH)
		buf[ii++] = c;
	return (1);
}

/**
 * _putfd - writes the character 'c' to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1. On error, -1 is returned, and errno is set
 * appropriately.
 */
int _putfd(char c, int fd)
{
	static int ii;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ii >= WRITE_BUF_SIZE)
	{
		write(fd, buf, ii);
		ii = 0;
	}
	if (c != BUF_FLUSH)
		buf[ii++] = c;
	return (1);
}

/**
 * _putsfd - prints a string to the given file descriptor
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written
 */
int _putsfd(char *str, int fd)
{
	int ii = 0;

	if (!str)
		return (0);
	while (*str)
	{
		ii += _putfd(*str++, fd);
	}
	return (ii);
}

