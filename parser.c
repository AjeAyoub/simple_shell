#include "shell.h"

/**
 *
 * is_cmd Determines if file is executable command.
 *
 * @info : Info struct.
 *
 * @path : path to the file.
 *
 * return : 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stt st;

	(void)info;
	if (!path || stt(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 *
 * dup_chars Duplicates characters
 *
 * @pathstr : PATH string.
 *
 * @start : Starting index.
 *
 * @stop : Stopping index.
 *
 * return : Pointer to new buffer.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char bf[1024];
	int j = 0, l = 0;

	for (l = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[l++] = pathstr[j];
	bf[l] = 0;
	return (bf);
}

/**
 *
 * find_path Finds this cmd in PATH string.
 *
 * @info : Info struct.
 * @pathstr : PATH string.
 *
 * @cmd : Cmd to find.
 *
 * return: full path of cmd if found or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, curr_ps = 0;
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
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_chars(pathstr, curr_ps, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_ps = j;
		}
		j++;
	}
	return (NULL);
}

