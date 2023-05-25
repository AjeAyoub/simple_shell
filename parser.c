#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
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
 * dup_chars - Duplicates characters from a string.
 * @pathstr: The source string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int ii = 0, kk = 0;

	for (kk = 0, ii = start; ii < stop; ii++)
		if (pathstr[ii] != ':')
			buf[kk++] = pathstr[ii];
	buf[kk] = 0;
	return (buf);
}

/**
 * find_path - Finds the full path of a command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found, or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int ii = 0, curr_poss = 0;
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
		if (!pathstr[ii] || pathstr[ii] == ':')
		{
			path = dup_chars(pathstr, curr_poss, ii);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[ii])
				break;
			curr_poss = ii;
		}
		ii++;
	}
	return (NULL);
}

