#include "shell.h"

/**
 *
 * hshMain shell loop.
 *
 * @info : Parameter &nd return info struct.
 *
 * @av : Argument vector from main().
 *
 * return : 0 on success, 1 on error, or error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t t = 0;
	int builtin_rt = 0;

	while (t != -1 && builtin_rt != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (t != -1)
		{
			set_info(info, av);
			builtin_rt = find_builtin(info);
			if (builtin_rt == -1)
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
	if (builtin_rt == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_rt);
}

/**
 *
 * find_builtin Finds a builtin command?
 *
 * @info : Parameter &nd return info struct.
 *
 * return : -1 if builtin not found,
 *
 * 0 if builtin executed	 successfully,
 * 1 if builtin 	found but not successful,
 * 2 if builtin signals exit().
 */
int find_builtin(info_t *info)
{
	int j, built_in_rt = -1;
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

	for (j = 0; builtintbl[j].type; j++)
		if (_strcmp(info->argv[0], builtintbl[j].type) == 0)
		{
			info->line_count++;
			built_in_rt = builtintbl[j].func(info);
			break;
		}
	return (built_in_rt);
}

/**
 *
 * find_cmd Finds command in PATH.
 *
 * @info : Parameter &nd return info struct.
 *
 * return : void.
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int j, l;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (j = 0, l = 0; info->arg[j]; j++)
		if (!is_delim(info->arg[j], " \t\n"))
			l++;
	if (!l)
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
 *
 * fork_cmd Forks exec thread to run cmd.
 *
 * @info : Parameter &nd return info struct.
 *
 * return : void.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pd;

	child_pd = fork();
	if (child_pd == -1)
	{
		/* TODO :  PUT ERROR FUNCTION. */
		perror("Error:");
		return;
	}
	if (child_pd == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO : PUT ERROR FUNCTIONs. */
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
