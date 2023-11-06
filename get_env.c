#include "main.h"

/**
 * get_environ - the string array copy of our environ
 * @info: Structure containing potential arguments.
 * Return: 0
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * un_setenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 *  Return: 1 (delete), otherwise 0
 * @var: the string env var property
 */

int un_setenv(info_t *info, char *var)
{
	list_t *nodes = info->env;
	size_t j = 0;
	char *pr;

	if (!nodes || !var)
		return (0);

	while (nodes)
	{
		pr = starts_with(nodes->str, var);
		if (pr && *pr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			nodes = info->env;
			continue;
		}
		nodes = nodes->next;
		j++;
	}
	return (info->env_changed);
}

/**
 * set_env - Initialize a new environment variable or modify
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: 0
 */

int set_env(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *nodes;
	char *pr;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	nodes = info->env;
	while (nodes)
	{
		pr = starts_with(nodes->str, var);
		if (pr && *pr == '=')
		{
			free(nodes->str);
			nodes->str = buff;
			info->env_changed = 1;
			return (0);
		}
		nodes = nodes->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

