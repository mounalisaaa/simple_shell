#include "shell.h"
int _strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}
/**
 * _strcat - concatenate two strings
 *
 * @dest: destination string
 * @src: source srting
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
  * _strcpy - copys str to another
  * @dest: destination string
  * @src: the str that we gonna copy
  *
  * Return: the pointer to dst
  */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (*(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';

	return (dest);
}
/**
 * _strdup - duplicate str and returns a ptr to newly allocated str.
 * @str: ptr to be duplicated.
 * Return: NULL or str1.
 */
char *_strdup(char *str)
{
	char *str1;
	unsigned int len;

	if (str == 0)
	{
		return (NULL);
	}
	len = _strlen(str) + 1;
	str1 = (char *)malloc(sizeof(char) * len);
	if (str1 == 0)
	{
		return (NULL);
	}
	_memcpy(str1, str, len);
	return (str1);
}
/**
 * _memcpy - function that copies memory area.
 * @dest: destination memory area.
 * @src: source memory ares.
 * @n: number of bytes to be copied.
 * Return: dest.
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

