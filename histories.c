#include "main.h"

/**
 * get_history_file - gets the history file.
 * @info: parameter struct.
 * Return: allocated string containg history file.
 */

char *get_history_file(info_t *info)
{
	char *str, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	str = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!str)
		return (NULL);
	str[0] = 0;
	_strcpy(str, dir);
	_strcat(str, "/");
	_strcat(str, HIST_FILE);
	return (str);
}

/**
 * write_history - creates a file, or appends to an existing file.
 * @info: the parameter struct.
 * Return: 1 (success), else -1
 */

int write_history(info_t *info)
{
	ssize_t op;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	op = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (op == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, op);
		_putfd('\n', op);
	}
	_putfd(BUF_FLUSH, op);
	close(op);
	return (1);
}

/**
 * read_history - reads history from file.
 * @info: the parameter struct.
 * Return: histcount on success, otherwise 0.
 */

int read_history(info_t *info)
{
	int j, last = 0, lcount = 0;
	ssize_t op, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	op = open(filename, O_RDONLY);
	free(filename);
	if (op == -1)
		return (0);
	if (!fstat(op, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(op, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(op);
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_history_list(info, buf + last, lcount++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(info, buf + last, lcount++);
	free(buf);
	info->histcount = lcount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list.
 * @info: Structure containing potential arguments.
 * @buf: buffer.
 * @linecount: the history linecount, histcount.
 * Return: 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nodes = NULL;

	if (info->history)
		nodes = info->history;
	add_node_end(&nodes, buf, linecount);

	if (!info->history)
		info->history = nodes;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list.
 * @info: Structure containing potential arguments.
 * Return: the new histcount.
 */

int renumber_history(info_t *info)
{
	list_t *nodes = info->history;
	int a = 0;

	while (nodes)
	{
		nodes->num = a++;
		nodes = nodes->next;
	}
	return (info->histcount = a);
}
