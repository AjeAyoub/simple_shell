#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: Parameter struct
 * @buf: Address of buffer
 * @len: Address of len var
 *
 * Return: Bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t rr = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rr = getline(buf, &len_p, stdin);
#else
		rr = _getline(info, buf, &len_p);
#endif
		if (rr > 0)
		{
			if ((*buf)[rr - 1] == '\n')
			{
				(*buf)[rr - 1] = '\0'; /* Remove trailing newline */
				rr--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) Is this a command chain? */
			{
				*len = rr;
				info->cmd_buf = buf;
			}
		}
	}
	return (rr);
}

/**
 * get_input - gets a line minus the newline
 * @info: Parameter struct
 *
 * Return: Bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* The ';' command chain buffer */
	static size_t ii, jj, len;
	ssize_t rr = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	rr = input_buf(info, &buf, &len);
	if (rr == -1) /* EOF */
		return (-1);
	if (len) /* We have commands left in the chain buffer */
	{
		jj = ii; /* Initialize new iterator to current buf position */
		p = buf + ii; /* Get pointer for return */

		check_chain(info, buf, &jj, ii, len);
		while (jj < len) /* Iterate to semicolon or end */
		{
			if (is_chain(info, buf, &jj))
				break;
			jj++;
		}

		ii = jj + 1; /* Increment past nulled ';' */
		if (ii >= len) /* Reached end of buffer? */
		{
			ii = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Pass back pointer to current command position */
		return (_strlen(p)); /* Return length of current command */
	}

	*buf_p = buf; /* Else not a chain, pass back buffer from _getline() */
	return (rr); /* Return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: Parameter struct
 * @buf: Buffer
 * @ii: Size
 *
 * Return: rr
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t rr = 0;

	if (*i)
		return (0);
	rr = read(info->readfd, buf, READ_BUF_SIZE);
	if (rr >= 0)
		*i = rr;
	return (rr);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: Parameter struct
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t ii, len;
	size_t kk;
	ssize_t rr = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (ii == len)
		ii = len = 0;

	rr = read_buf(info, buf, &len);
	if (rr == -1 || (rr == 0 && len == 0))
		return (-1);

	c = _strchr(buf + ii, '\n');
	kk = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + kk : kk + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, kk - ii);
	else
		_strncpy(new_p, buf + ii, kk - ii + 1);

	s += kk - ii;
	ii = kk;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: The signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

