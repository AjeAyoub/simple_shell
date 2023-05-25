#include "shell.h"

/**
 * hsh - Main shell loop.
 * @info: The parameter and return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t rr = 0;
	int builtin_rett = 0;

	while (rr != -1 && builtin_rett != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		rr = get_input(info);
		if (rr != -1)
		{
			set_info(info, av);
			builtin_rett = find_builtin(info);
			if (builtin_rett == -1)
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
	if (builtin_rett == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_rett);
}

/**
 * find_builtin - Finds a builtin command.
 * @info: The parameter and return info struct.
 *
 * Return: -1 if builtin not found,
 *	0 if builtin executed successfully,
 *	1 if builtin found but not successful,
 *	2 if builtin signals exit().
 */
int find_builtin(info_t *info)
{
	int ii, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (ii = 0; builtintbl[ii].type; ii++)
		if (_strcmp(info->argv[0], builtintbl[ii].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[ii].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - Finds a command in PATH.
 * @info: The parameter and return info struct.
 *
 * Return: void.
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int ii, kk;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (ii = 0, kk = 0; info->arg[ii]; ki++)
		if (!is_delim(info->arg[ii], " \t\n"))
			kk++;
	if (!kk)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - Forks an exec thread to run the command.
 * @info: The parameter and return info struct.
 *
 * Return: void.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pidd;

	child_pidd = fork();
	if (child_pidd == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pidd == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
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

