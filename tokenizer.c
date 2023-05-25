#include "shell.h"

/**
 * strtow - Splits a string into words. Repeat delimiters are ignored.
 * @str: The input string.
 * @d: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *d)
{
	int ii, jj, kk, mm, numwords = 0;
	char **ss;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";
	for (ii = 0; str[ii] != '\0'; ii++)
		if (!is_delim(str[ii], d) && (is_delim(str[ii + 1], d) || !str[ii + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	ss = malloc((1 + numwords) * sizeof(char *));
	if (!ss)
		return (NULL);
	for (ii = 0, jj = 0; jj < numwords; jj++)
	{
		while (is_delim(str[ii], d))
			ii++;
		kk = 0;
		while (!is_delim(str[ii + kk], d) && str[ii + kk])
			kk++;
		s[jj] = malloc((kk + 1) * sizeof(char));
		if (!ss[jj])
		{
			for (kk = 0; kk < jj; kk++)
				free(ss[kk]);
			free(ss);
			return (NULL);
		}
		for (mm = 0; mm < kk; mm++)
			s[jj][mm] = str[ii++];
		s[jj][mm] = '\0';
	}
	s[jj] = NULL;
	return (ss);
}

/**
 * strtow2 - Splits a string into words.
 * @str: The input string.
 * @d: The delimiter.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow2(char *str, char d)
{
	int ii, jj, kk, mm, numwords = 0;
	char **ss;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	for (ii = 0; str[ii] != '\0'; ii++)
		if ((str[ii] != d && str[ii + 1] == d) ||
		    (str[ii] != d && !str[ii + 1]) || str[ii + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!ss)
		return (NULL);
	for (ii = 0, jj = 0; jj < numwords; jj++)
	{
		while (str[ii] == d && str[ii] != d)
			ii++;
		kk = 0;
		while (str[ii + kk] != d && str[ii + kk] && str[ii + kk] != d)
			kk++;
		s[jj] = malloc((kk + 1) * sizeof(char));
		if (!ss[jj])
		{
			for (kk = 0; kk < jj; kk++)
				free(ss[kk]);
			free(ss);
			return (NULL);
		}
		for (mm = 0; mm < kk; mm++)
			ss[jj][mm] = str[ii++];
		ss[jj][mm] = '\0';
	}
	s[jj] = NULL;
	return (ss);
}

