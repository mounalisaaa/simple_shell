#include "shell.h"
/**
 * _strncpy - function that copies a string
 *
 * @dest: destination string
 * @src: source srting
 * @n: integer that specify the max num of chars to be copied.
 * Return: dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
/**
 *  _puts - print string to stdout
 * @str: pointer to string.
 * Return: Always 0.
 */
void _puts(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
	_putchar('\n');
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _strcmp - function that compares two strings.
 *
 * @s1: pointer of the first string to be compared.
 * @s2: pointer of the second string to be compared.
 * Return: integer.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
/**
 * _strncmp - compares first n bytes of s1 and s2
 * @s1: string 1
 * @s2: string 2
 * @n: number of bytes to compare
 * Return: int
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while (s1[i] && (i < n))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (0);
}