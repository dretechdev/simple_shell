#include "main.h"

/**
 * input_buf - buffers chained commands.
 * @info: parameter struct.
 * @buf: address of buffer.
 * @len: address of len var.
 * Return: bytes read.
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t res = 0;
	size_t len_pr = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		res = getline(buf, &len_pr, stdin);
#else
		res = get_line(info, buf, &len_pr);
#endif
		if (res > 0)
		{
			if ((*buf)[res - 1] == '\n')
			{
				(*buf)[res - 1] = '\0';
				res--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = res;
				info->cmd_buf = buf;
			}
		}
	}
	return (res);
}

/**
 * get_input - gets a line minus the newline.
 * @info: parameter struct.
 * Return: bytes read.
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, leng;
	ssize_t res = 0;
	char **buf_p = &(info->arg), *pr;

	_putchar(BUF_FLUSH);
	res = input_buf(info, &buf, &leng);
	if (res == -1)
		return (-1);
	if (leng)
	{
		j = i;
		pr = buf + i;

		check_chain(info, buf, &j, i, leng);
		while (j < leng)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= leng)
		{
			i = leng = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = pr;
		return (_strlen(pr));
	}

	*buf_p = buf;
	return (res);
}

/**
 * read_buf - reads a buffer.
 * @info: parameter struct.
 * @buf: buffer.
 * @i: size.
 * Return: r
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, leng;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (j == leng)
		j = leng = 0;

	r = read_buf(info, buf, &leng);
	if (r == -1 || (r == 0 && leng == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : leng;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + j, k - j);
	else
		_strncpy(new_p, buf + j, k - j + 1);

	s += k - j;
	j = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
