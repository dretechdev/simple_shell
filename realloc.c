#include "main.h"

/**
 **_memset - function that fills memory with a constant byte.
 *@s: pointer to the memory area.
 *@b: byte to fill *s.
 *@n: the amount of bytes to be filled.
 *Return: a pointer to the memory area.
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * ffree - function that frees a string of strings
 * @pp: string of strings
 */

void ffree(char **pp)
{
	char **i = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(i);
}

/**
 * _realloc - function that reallocates a block of memory.
 * @ptr: pointer to previous malloc.
 * @old_size: size of previous block
 * @new_size: size of new block
 * Return: pointer
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pr = malloc(new_size);
	if (!pr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pr);
}

