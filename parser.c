#include "main.h"

/**
 * is_cmd - this function determines if a file is an executable command
 * @info: the info struct.
 * @path: path to the file.
 * Return: 1 if true, otherwise 0
 */

int is_cmd(info_t *info, char *path)
{
	struct stat stt;

	(void)info;
	if (!path || stat(path, &stt))
		return (0);

	if (stt.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - function that  duplicates characters.
 * @pathstr: the PATH string.
 * @start: starting index.
 * @stop: stopping index.
 * Return: pointer to new buffer.
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buff[b++] = pathstr[a];
	buff[b] = 0;
	return (buff);
}

/**
 * find_path - finds cmd in the Path string.
 * @info: the info struct.
 * @pathstr: the Path string.
 * @cmd: the cmd to find.
 * Return: full path of cmd if found or NULL.
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, curr_posit = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = dup_chars(pathstr, curr_posit, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			curr_posit = a;
		}
		a++;
	}
	return (NULL);
}

