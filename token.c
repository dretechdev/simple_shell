#include "main.h"

/**
 * strtow - This splits a string into words and ignores the repeated delimers
 * @str: This is the input string
 * @d: This is the delimeter string
 * Return: Returns a pointer to an array of strings, ir NULL if failure occurs
 */

char **strtow(char *str, char *d)
{
	int a, b, c, e, nwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delimeter(str[a], d) && (is_delimeter(str[a + 1], d) || !str[a + 1]))
			nwords++;
	if (nwords == 0)
		return (NULL);
	s = malloc((1 + nwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < nwords; b++)
	{
		while (is_delimeter(str[a], d))
			a++;
		c = 0;
		while (!is_delimeter(str[a + c], d) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - This splits a string into words
 * @str: This is the input string
 * @d: This is the delimeter
 * Return: Returns a pointer to an array of strings or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int a, b, c, e, nwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d)
				|| (str[a] != d && !str[a + 1])
				|| str[a + 1] == d)
			nwords++;
	if (nwords == 0)
		return (NULL);
	s = malloc((1 + nwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < nwords; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < c; e++)
			s[b][e] = str[a++];
		s[b][e] = 0;
	}
	s[b] = NULL;
	return (s);
}
