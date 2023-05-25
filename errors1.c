#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: The string to be converted
 * Return: 0 if no numbers in the string, the converted number otherwise
 *         -1 on error
 */
int _erratoi(char *s)
{
	int ii = 0;
	unsigned long int rslt = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (ii = 0; s[ii] != '\0'; ii++)
	{
		if (s[ii] >= '0' && s[ii] <= '9')
		{
			rslt *= 10;
			rslt += (s[ii] - '0');
			if (rslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rslt);
}

/**
 * print_error - prints an error message
 * @info: The parameter and return info struct
 * @estr: The string containing the specified error type
 * Return: Nothing
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - prints a decimal (integer) number (base 10)
 * @input: The input number
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int ii, cnt = 0;
	unsigned int _abs_, currentt;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		cnt++;
	}
	else
		_abs_ = input;
	currentt = _abs_;
	for (ii = 1000000000; ii > 1; ii /= 10)
	{
		if (_abs_ / ii)
		{
			__putchar('0' + currentt / ii);
			cnt++;
		}
		currentt %= ii;
	}
	__putchar('0' + currentt);
	cnt++;

	return (cnt);
}

/**
 * convert_number - converts a number to a string
 * @num: The number to convert
 * @base: The base of the conversion
 * @flags: Argument flags
 *
 * Return: The converted string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char signn = 0;
	char *ptr;
	unsigned long nn = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		nn = -num;
		signn = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[nn % base];
		nn /= base;
	} while (nn != 0);

	if (signn)
		*--ptr = signn;
	return (ptr);
}

/**
 * remove_comments - replaces the first instance of '#' with '\0'
 * @buf: The address of the string to modify
 *
 * Return: Always 0
 */
void remove_comments(char *buf)
{
	int ii;

	for (ii = 0; buf[ii] != '\0'; ii++)
	{
		if (buf[ii] == '#' && (!ii || buf[ii - 1] == ' '))
		{
			buf[ii] = '\0';
			break;
		}
	}
}

