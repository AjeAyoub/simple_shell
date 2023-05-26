#include "shell.h"

/**
 * get_history_file - Gets the history file.
 * @info: Pointer to the parameter struct.
 *
 * Return: Allocated string containing the history file.
 */
char *get_history_file(info_t *info)
{
	char *buff, *dirr;

	dirr = _getenv(info, "HOME=");
	if (!dirr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	_strcpy(buff, dirr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - Creates a file or appends to an existing file with history.
 * @info: Pointer to the parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fdd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fdd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fdd);
		_putfd('\n', fdd);
	}
	_putfd(BUF_FLUSH, fdd);
	close(fdd);
	return (1);
}

/**
 * read_history - Reads history from a file.
 * @info: Pointer to the parameter struct.
 *
 * Return: The number of history entries read on success, 0 otherwise.
 */
int read_history(info_t *info)
{
	int ii, lastt = 0, linecount = 0;
	ssize_t fdd, rdlen, fsize = 0;
	struct stat stt;
	char *buff = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fdd = open(filename, O_RDONLY);
	free(filename);
	if (fdd == -1)
		return (0);
	if (!fstat(fdd, &stt))
		fsize = stt.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fdd, buff, fsize);
	buff[fsize] = '\0';
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fdd);
	for (ii = 0; ii < fsize; ii++)
		if (buff[ii] == '\n')
		{
			buff[ii] = '\0';
			build_history_list(info, buff + lastt, linecount++);
			lastt = ii + 1;
		}
	if (lastt != ii)
		build_history_list(info, buff + lastt, linecount++);
	free(buff);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds an entry to the history linked list.
 * @info: Pointer to the parameter struct.
 * @buf: Buffer containing the history entry.
 * @linecount: The linecount of the history entry.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nod = NULL;

	if (info->history)
		nod = info->history;
	add_node_end(&nod, buf, linecount);

	if (!info->history)
		info->history = nod;
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @info: Pointer to the parameter struct.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *nod = info->history;
	int ii = 0;

	while (nod)
	{
		nod->num = ii++;
		nod = nod->next;
	}
	return (info->histcount = ii);
}

