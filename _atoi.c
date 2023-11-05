#include "main.h"

/**
 * interactive - returns true if shell is interactive mode.
 * @info: struct address.
 * Return: 1 if interactive mode, otherwise 0.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimeter - checks if char is a delimeter.
 * @c: the char to check.
 * @delim: the delimeter string.
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
		{
			return (1);
		}
	return (0);
}

/**
 * is_alpha - checks for alphabetic character.
 * @c: input character.
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an int.
 * @s: the string to be converted.
 * Return: 0 if no numbers in string, converted number otherwise.
 */

int _atoi(char *s)
{
	int i, sig = 1, fg = 0, outp;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && fg != 2; i++)
	{
		if (s[i] == '-')
			sig *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			fg = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sig == -1)
		outp = -result;
	else
		outp = result;

	return (outp);
}
