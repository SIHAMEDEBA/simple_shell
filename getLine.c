#include "main.h"

/**
 * input_buf - buffers chained commands
 * @inf: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *inf, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in buffer, fill it */
	{
		/*bfree((void **)inf->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(inf, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			inf->linecount_flag = 1;
			remove_comments(*buf);
			build_hst_ls(inf, *buf, inf->histcount++);
			/* if (_strchr(*buf, ';')) is this a cmd chain? */
			{
				*len = r;
				inf->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *inf)
{
	static char *buf; /* ';' cmd chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(inf->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(inf, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(inf, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(inf, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and leng */
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current cmd position */
		return (_strlen(p)); /* return leng of current cmd */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return leng of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @inf: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *inf, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(inf->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets next line of input from STDIN
 * @inf: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @leng: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *inf, char **ptr, size_t *leng)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && leng)
		s = *leng;
	if (i == len)
		i = len = 0;

	r = read_buf(inf, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (leng)
		*leng = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
