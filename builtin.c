#include "shell.h"

/**
 * _myexit - exit the shell.
 * @info: Structure containing potential arguments.
 *
 * This function handles the "exit" command. If an exit argument is provided,
 * it converts it to an integer and sets it as the error number in the info
 * structure. If the exit argument is not a valid number, an error message is
 * printed. If no exit argument is provided, the error number is set to -1.
 *
 * Return: -2 to indicate the shell should exit.
 */
int _myexit(info_t *info)
{
	int exitchck;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitchck = _erratoi(info->argv[1]);
		if (exitchck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - change the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * This function handles the "cd" command. If no argument is provided,
 * it changes
 * the current directory to the home directory. If the argument is "-",
 * it changes
 * the current directory to the previous working directory (if available).
 * Otherwise,
 * it changes the current directory to the specified directory. The environment
 * variables "OLDPWD" and "PWD" are updated accordingly.
 *
 * Return: Always 0.
 */
int _mycd(info_t *info)
{
	char *c, *dr, buffer[1024];
	int chdr_rt;

	c = getcwd(buffer, 1024);
	if (!c)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dr = _getenv(info, "HOME=");
		if (!dr)
			chdr_rt = chdr((dr = _getenv(info, "PWD=")) ? dr : "/");
		else
			chdr_rt = chdr(dr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdr_rt = chdr((dr = _getenv(info, "OLDPWD=")) ? dr : "/");
	}
	else
		chdr_rt = chdr(info->argv[1]);
	if (chdr_rt == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - display help information.
 * @info: Structure containing potential arguments.
 *
 * This function handles the "help" command. It displays a help message
 * indicating that the function is not yet implemented.
 *
 * Return: Always 0.
 */
int _myhelp(info_t *info)
{
	char **arg_arry;

	arg_arry = info->argv;
	_puts("help call works. Function not yet implemented\n");
	if (0)
		_puts(*arg_arry); /* temp att_unused workaround */
	return (0);
}

