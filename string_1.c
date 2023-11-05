#include "main.h"

/**
 * _strcpy - This function copies a string
 * @dest: This is the destination
 * @src: This is the source
 * Return: The pointer to the destination
 */
char *_strcpy(char *dest, char *src)
{
	int integer = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[integer])
	{
		dest[integer] = src[integer];
		integer++;
	}
	dest[integer] = 0;
	return (dest);
}

/**
 * _strdup - This duplicates a string
 * @str: This is the string to duplicate
 * Return: The pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int l = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	for (l++; l--;)
		r[l] = *--str;
	return (r);
}

/**
 * _puts - This function prints an input string
 * @str: This is the string to be printed
 * Return: This should not return anything
 */
void _puts(char *str)
{
	int y = 0;

	if (!str)
		return;
	while (str[y] != '\0')
	{
		_putchar(str[y]);
		y++;
	}
}

/**
 * _putchar - This writes the character c into the standard output
 * @c: This is the charater to print
 * Return: 1 on success or -1 on error and "errno" is set
 */
int _putchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
