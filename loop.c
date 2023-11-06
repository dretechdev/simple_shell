#include "main.h"

/**
 * hsh - main shell loop function.
 * @info: the parameter
 * @av: the argument vector
 * Return: 0 (success), 1 (error), or error code
 */

int hsh(info_t *info, char **av)
{
	ssize_t res = 0;
	int buil_ret = 0;

	while (res != -1 && buil_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		res = get_input(info);
		if (res != -1)
		{
			set_info(info, av);
			buil_ret = find_buil(info);
			if (buil_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (buil_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (buil_ret);
}

/**
 * find_builtin - function to finds a builtin command
 * @info: the parameter
 * Return: -1 if builtin not found, 0 if builtin executed successfully,
 *	1 if builtin found but not successful,-2 if builtin signals exit()
 */

int find_buil(info_t *info)
{
	int j, built_in_ret = -1;
	builtin_table builtin_tbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (j = 0; builtin_tbl[j].type; j++)
		if (_strcmp(info->argv[0], builtin_tbl[j].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtin_tbl[j].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - function to find a command in the PATH
 * @info: the parameter
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int a, b;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, b = 0; info->arg[a]; a++)
		if (!is_delimeter(info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_path(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || get_env(info, "PATH=")
			|| info->argv[0][0] == '/')
			&& is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an executable thread to run command
 * @info: the parameter
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

