#include "main.h"

/**
 * my_env - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: 0
 */
int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @info: Structure containing potential arguments.
 * @name: env var name
 * Return: the value
 */
char *get_env(info_t *info, const char *name)
{
	list_t *nodes = info->env;
	char *pr;

	while (nodes)
	{
		pr = starts_with(nodes->str, name);
		if (pr && *pr)
			return (pr);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * my_setenv - Initialize a new environnement or modify an existing one
 * @info: Structure containing potential arguments.
 *  Return: 0
 */
int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 *  Return: 0
 */

int my_unsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * populate_env_list - populates env linked list.
 * @info: Structure containing potential arguments.
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *nodes = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&nodes, environ[j], 0);
	info->env = nodes;
	return (0);
}
