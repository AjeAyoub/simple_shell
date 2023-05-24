#include "shell.h"

/**
 *strncpy copie a string
 *@dest : the destination string to be copied to.
 *
 *@src : the source string.
 * 
 *@n : the amount of characters to be copied.

 *Return : the concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int j, k;
	char *s = dest;

	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		k = j;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 *strncat concatenates two strings.

 *@dest : the first string.

 *@src : the second string.

 *@n : the amount of bytes to be maximally used.

 *Return : the concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int k, l;
	char *s = dest;

	j = 0;
	k = 0;
	while (dest[j] != '\0')
		j++;
	while (src[k] != '\0' && k < n)
	{
		dest[j] = src[k];
		j++;
		k++;
	}
	if (k < n)
		dest[j] = '\0';
	return (s);
}

/**
 *
 *strchr locates a character in string

 *@s :  string to be a parsed.

 *@c : character to look for.
 *Return :(s) a pointer to the memory area s.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

