#include "main.h"

/**
 * _strlen - This returns the legth of a string
 * @s: This is the string whose length is to be checked
 * Return: The integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - This performs lexicogarphic comparison of two strings
 * @s1: This is the first string
 * @s2: Thos os the second string
 * Return: -ve if s1 < s2, +ve if s1 > s2, 0 if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 && *s2)
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
 * starts_with - This checks if needle starts with haystack
 * @haystack: This is the string to search
 * @needle: This is the substring to find
 * Return: The address of the next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - This function concatenates two strings
 * @dest: This is the destination buffer
 * @src: This is the source buffer
 * Return: The pointer to te destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}
