#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *         a constant function prototype.
 *
 * Return: exits with a given exit status (0) if info->argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheckk;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitcheckk = _erratoi(info->argv[1]);
		if (exitcheckk == -1)
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
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *         a constant function prototype.
 *
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *ss, *dirr, buffer[1024];
	int chdir_rett;

	s = getcwd(buffer, 1024);
	if (!ss)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirr = _getenv(info, "HOME=");
		if (!dirr)
			chdir_rett = /* TODO: what should this be? */
				chdir((dirr = _getenv(info, "PWD=")) ? dirr : "/");
		else
			chdir_rett = chdir(dirr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_rett = /* TODO: what should this be? */
			chdir((dirr = _getenv(info, "OLDPWD=")) ? dirr : "/");
	}
	else
		chdir_rett = chdir(info->argv[1]);
	if (chdir_rett == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - prints help information
 * @info: Structure containing potential arguments. Used to maintain
 *         a constant function prototype.
 *
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_arrayy;

	arg_arrayy = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arrayy); /* temp att_unused workaround */
	return (0);
}
