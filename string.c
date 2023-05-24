#include "shell.h"

/**
 *
 * strlen Returns length of String.
 *
 * @s : String whose length to check.
 *
 * return: integer length of string.
 */
int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 *
 * strcmp Performs lexicogarphics comparison of 2 strangs.
 *
 * @s1 : First strang.
 *
 * @s2 : Second strang.
 *
 * return : negative if S1 smaller than S2, positive if s1 greater
 * than s2, zero if s1 == s2.
 *
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 *
 * Starts_with Checks if needle starts with haystack
 *
 * @haystack : String to search.
 *
 * @needle : Substring to find.
 *
 * return : Address of next char of haystack or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 *
 * strcat  concatenates 2 strings
 *
 * @dest : Destination buffer.
 *
 * @src : Source buffer.
 *
 * return : Pointer to destination buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *rt = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (rt);
}

