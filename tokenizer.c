#include "shell.h"

/**
 *
 * strtow Splits  strg into words.
 *
 * Repeat delimiters ar ignored.
 *
 * @str : input string.
 *
 * @d: Delimeter strg.
 * return : pointer to array of strings, or NULL on failure.
 */

char **strtow(char *str, char *d)
{
	int j, k, l, n, numword = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (j = 0; str[j] != '\0'; j++)
		if (!is_delim(str[j], d) && (is_delim(str[j + 1], d) || !str[j + 1]))
			numword++;

	if (numword == 0)
		return (NULL);
	s = malloc((1 + numword) * sizeof(char *));
	if (!s)
		return (NULL);
	for (j = 0, k = 0; k < numword; k++)
	{
		while (is_delim(str[j], d))
			j++;
		l = 0;
		while (!is_delim(str[j + l], d) && str[j + l])
			l++;
		s[k] = malloc((l + 1) * sizeof(char));
		if (!s[k])
		{
			for (l = 0; l < k; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < l; m++)
			s[k][m] = str[j++];
		s[k][m] = 0;
	}
	s[k] = NULL;
	return (s);
}

/**
 *
 * Strtow2 splits string into word.
 *
 * @str : input string.
 *
 * @d : delimeter.
 * Return : pointer to array of strings, or NULL on failure.
 *
 */
char **strtow2(char *str, char d)
{
	int j, k, l, n, numword = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (j = 0; str[j] != '\0'; j++)
		if ((str[j] != d && str[j + 1] == d) ||
				    (str[j] != d && !str[j + 1]) || str[j + 1] == d)
			numword++;
	if (numword == 0)
		return (NULL);
	s = malloc((1 + numword) * sizeof(char *));
	if (!s)
		return (NULL);
	for (j = 0, k = 0; k < numword; k++)
	{
		while (str[j] == d && str[j] != d)
			j++;
		l = 0;
		while (str[j + l] != d && str[j + l] && str[j + l] != d)
			l++;
		s[k] = malloc((l + 1) * sizeof(char));
		if (!s[k])
		{
			for (l = 0; l < k; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s[k][n] = str[j++];
		s[k][n] = 0;
	}
	s[k] = NULL;
	return (s);
}

