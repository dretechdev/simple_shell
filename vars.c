#include "main.h"

/**
 * _ischain - This program tests if the current char in the buffer
 * is a delimeter
 * @info: This is the parameter struct
 * @buf: This is the character buffer
 * @p: This is the address of current position in the buffer
 * Return: 1 if chain delimeter, or 0 otherwise
 */
int _ischain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = k;
	return (1);
}

/**
 * _checkagain - This checks the continuity of chaining based on last status
 * @info: This is the parameter structure
 * @buf: The buffer
 * @p: This is the current position in the buffer
 * @i: This os the starting point in the buffer
 * @len: This is the buffer's length
 * Return: void
 */
void _checkagain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t q = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			q = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			q = len;
		}
	}
	*p = q;
}

/**
 * _replace_alias - This replaces an aliase in the tokenized string
 * @info: This is the parameter struct
 * Return: 1 if replaced successfully, otherwise 0
 */
int _replace_alias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_ starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - This function replaces vars in the tokenized string
 * @info: This is the parameter struct
 * Return: 1 if replaced, or 0 otherwise
 */
int replace_vars(info_t *info)
{
	int e = 0;
	list_t *node;

	for (e = 0; info->argv[e]; e++)
	{
		if (info->argv[e][0] != '$' || !info->argv[e][1])
			continue;

		if (!_strcmp(info->argv[e], "$?"))
		{
			replace_string(&(info->argv[e]), _strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[e], "$$"))
		{
			replace_string(&(info->argv[e]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->, &info->argv[e][1], '=');
		if (node)
		{
			replace_string(&(info->argv[e]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[e], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - This function replaces string
 * @old_str: This is the address of old string
 * @new_str: This is the address of new string
 * Return: 1 if replaced OR 0 if otherwise
 */
int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}
