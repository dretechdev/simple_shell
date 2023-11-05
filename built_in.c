#include "main.h"

/**
 * my_history - displays the history list, one command by line.
 * @info: Structure containing potential arguments.
 *  Return: 0
 */
int my_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string.
 * @info: parameter struct.
 * @str: the string alias.
 * Return: 0 (success), 1 (error)
 */

int unset_alias(info_t *info, char *str)
{
	char *pr, s;
	int r;

	pr = _strchr(str, '=');
	if (!pr)
		return (1);
	s = *pr;
	*pr = 0;
	r = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*pr = s;
	return (r);
}

/**
 * set_alias - sets alias to string.
 * @info: parameter struct.
 * @str: the string alias.
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *pr;

	pr = _strchr(str, '=');
	if (!pr)
		return (1);
	if (!*++pr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string.
 * @nodes: the alias node.
 * Return: 0 (success), 1 (error)
 */
int print_alias(list_t *nodes)
{
	char *pr = NULL, *i = NULL;

	if (nodes)
	{
		pr = _strchr(nodes->str, '=');
		for (i = nodes->str; i <= pr; i++)
			_putchar(*i);
		_putchar('\'');
		_puts(pr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - imitate the alias builtin
 * @info: Structure containing potential arguments.
 *  Return: 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *pr = NULL;
	list_t *nodes = NULL;

	if (info->argc == 1)
	{
		nodes = info->alias;
		while (nodes)
		{
			print_alias(nodes);
			nodes = nodes->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		pr = _strchr(info->argv[i], '=');
		if (pr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
