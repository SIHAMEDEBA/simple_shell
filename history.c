#include "main.h"

/**
 * get_hstfile - gets history file
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hstfile(info_t *inf)
{
	char *buf, *dir;

	dir = _getenv(inf, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * wrt_hst - creates a file, or appends to an existing file
 * @inf: parameter struct
 *
 * Return: 1 on success, else -1
 */
int wrt_hst(info_t *inf)
{
	ssize_t fd;
	char *filename = get_hstfile(inf);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * rd_hst - reads history from file
 * @inf: parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int rd_hst(info_t *inf)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hstfile(inf);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hst_ls(inf, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_hst_ls(inf, buf + last, linecount++);
	free(buf);
	inf->histcount = linecount;
	while (inf->histcount-- >= HIST_MAX)
		dlt_nodex(&(inf->history), 0);
	num_hst(inf);
	return (inf->histcount);
}

/**
 * build_hst_ls - adds entry to a history linked list
 * @inf: strctr containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: history linecount, histcount
 *
 * Return: Always 0
 */
int build_hst_ls(info_t *inf, char *buf, int linecount)
{
	list_t *node = NULL;

	if (inf->history)
		node = inf->history;
	end_node(&node, buf, linecount);

	if (!inf->history)
		inf->history = node;
	return (0);
}

/**
 * num_hst - renumbers history linked list after changes
 * @inf: strctr containing potential arguments. Used to maintain
 *
 * Return: new histcount
 */
int num_hst(info_t *inf)
{
	list_t *node = inf->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (inf->histcount = i);
}
