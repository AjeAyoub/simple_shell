#include "shell.h"

/**
 * input_buf buffers chained commands
 *
 * @info : parameter struct.
 *
 * @buf : address of buffer.
 * @len : address of len var.
 *
 * Return : bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t t = 0;
	size_t len_b = 0;

	if (!*len) /* if nothing left in buffer, fill it */
	{
		/* bfree((void **)info->cmd_buf); */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		t = getline(buf, &len_b, stdin);
#else
		t = _getline(info, buf, &len_b);
#endif
		if (t > 0)
		{
			if ((*buf)[t - 1] == '\n')
			{
				(*buf)[t - 1] = '\0'; /*remove trailing newline */
				t--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/*  if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = t;
				info->cmd_buf = buf;
			}
		}
	}
	return (t);
}

/**
 *
 * get_input gets line minus the newline
 * @info : parameter struct.
 *
 * Return : bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /*  the ';' command chain buffer */
	static size_t j, k, len;
	ssize_t t = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	t = input_buf(info, &buf, &len);
	if (t == -1) /*  EOF*/
		return (-1);
	if (len) /* we have commands left in chain buffer */
	{
		k = j; /* init new iterator  to current buf position */
		p = buf + j; /*  get pointer for return */

		check_chain(info, buf, &k, j, len);
		while (k < len) /* iterate to semicolon or  end */
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}

		j = k + 1; /* increment  past nulled ';'' */
		if (j >= len) /*  reached end  buffer? */
		{
			j = len = 0; /* reset  position & length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /*pass back pointer to current command position */
		return (_strlen(p)); /*return length of current command */
	}

	*buf_p = buf; /*else not chain, pass back buffer from _getline() */
	return (t); /*return length of buffer from _getline() */
}

/**
 *
 * read_buf reeads  buffer
 * @info : parameter struct.
 *
 * @buf : buffer.
 * @j : size
 *
 * Return: t.
 *
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t t = 0;

	if (*i)
		return (0);
	t = read(info->readfd, buf, READ_BUF_SIZE);
	if (t >= 0)
		*i = t;
	return (t);
}

/**
 *
 * getline gets the next line of input from STDIN.
 * @info : parameter struct.
 * @ptr : address of pointer to buffer, preallocated or NULL.
 *
 * @length : size of preallocated ptr buffer if not NULL.
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t l;
	ssize_t t = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (j == len)
		j = len = 0;

	t = read_buf(info, buf, &len);
	if (t == -1 || (t == 0 && len == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	l = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + l : l + 1);
	if (!new_p) /* MALLOC FAILURE!*/
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + j, l - j);
	else
		_strncpy(new_p, buf + j, l - j + 1);

	s += l - j;
	j = l;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 *
 * sigintHandler blocks ctrl-C
 *
 * @sig_num : the signal number.
 * Return : void.
 *
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

