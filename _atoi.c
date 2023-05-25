#include "shell.h"

/**
 * interactive - returns true if the shell is in interactive mode
 * @info: pointer to the info_t struct
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if a character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isalpha - checks for an alphabetic character
 * @c: The character to check
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in the string, the converted number otherwise
 */
int _atoi(char *s)
{
	int ii, signn = 1, flagg = 0, outputt;
	unsigned int resultt = 0;

	for (ii = 0; s[ii] != '\0' && flagg != 2; ii++)
	{
		if (s[ii] == '-')
			signn *= -1;

		if (s[ii] >= '0' && s[ii] <= '9')
		{
			flagg = 1;
			resultt *= 10;
			resultt += (s[ii] - '0');
		}
		else if (flagg == 1)
			flagg = 2;
	}

	if (signn == -1)
		outputt = -resultt;
	else
		outputt = resultt;

	return (outputt);
}

