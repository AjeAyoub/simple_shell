#include "shell.h"

/**
 * Get_history files gets the history file
 * @info : parameter struct.
 *
 * Return: allocated string containg history File.
 */

char *get_history_file(info_t *info)
{
	char *bf, *dr;

	dr = _getenv(info, "HOME=");
	if (!dr)
		return (NULL);
	bf = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
	if (!bf)
		return (NULL);
	bf[0] = 0;
	_strcpy(bf, dr);
	_strcat(bf, "/");
	_strcat(bf, HIST_FILE);
	return (bf);
}

/**
 *
 * Write_history creates a file or appends to an existing file.
 *
 * @info : the parameter struct.
 *
 * return : 1 on success, else -1
 *
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filen = get_history_file(info);
	list_t *node = NULL;

	if (!filen)
		return (-1);

	fd = open(filen, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filen);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 *
 * read_history reads history From file
 * @info : the parameter struct.
 *
 * return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int j, last = 0, linec = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *bf = NULL, *filen = get_history_file(info);

	if (!filen)
		return (0);

	fd = open(filen, O_RDONLY);
	free(filen);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	bf = malloc(sizeof(char) * (fsize + 1));
	if (!bf)
		return (0);
	rdlen = read(fd, bf, fsize);
	bf[fsize] = 0;
	if (rdlen <= 0)
		return (free(bf), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
		if (bf[j] == '\n')
		{
			bf[j] = 0;
			build_history_list(info, bf + last, linec++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(info, bf + last, linec++);
	free(bf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 *
 * Build_history_list Adds entry to a history linked list
 *
 * @info : Structure containing potential arguments.
 * used to maintain.
 *
 * @bf : buffer.
 *
 * @linec : the history linec, histcount.
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 *
 * Renumber_history renumbers the history linked list after changes
 * @info : structure containing potential arguments.
 * used to maintain.
 *
 * return : the new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}

