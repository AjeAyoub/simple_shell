#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: The destination string to be copied to
 * @src: The source string
 * @n: The number of characters to be copied
 * Return: The concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int ii, jj;
	char *s = dest;

	ii = 0;
	while (src[ii] != '\0' && ii < n - 1)
	{
		dest[ii] = src[ii];
		ii++;
	}
	if (ii < n)
	{
		jj = ii;
		while (jj < n)
		{
			dest[jj] = '\0';
			jj++;
		}
	}
	return (s);
}

/**
 * _strncat - concatenates two strings
 * @dest: The first string
 * @src: The second string
 * @n: The maximum number of bytes to be used
 * Return: The concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int ii, jj;
	char *s = dest;

	ii = 0;
	jj = 0;
	while (dest[ii] != '\0')
		ii++;
	while (src[jj] != '\0' && jj < n)
	{
		dest[ii] = src[jj];
		ii++;
		jj++;
	}
	if (jj < n)
		dest[ii] = '\0';
	return (s);
}

/**
 * _strchr - locates a character in a string
 * @s: The string to be parsed
 * @c: The character to look for
 * Return: A pointer to the memory area s, or NULL if the character
 * is not found
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

