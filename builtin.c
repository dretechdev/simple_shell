#include "main.h"

/**
 * my_exit - exits the shell.
 * @info: Structure containing potential arguments.
 *  Return: exit
 *         (0) if info.argv[0] != "exit"
 */
int my_exit(info_t *info)
{
	int excheck;

	if (info->argv[1])
	{
		excheck = err_atoi(info->argv[1]);
		if (excheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *  Return: 0
 */
int my_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chd_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chd_ret = chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chd_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chd_ret = chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chd_ret = chdir(info->argv[1]);
	if (chd_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current directory
 * @info: Structure containing potential arguments.
 *  Return: 0
 */
int my_help(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}

