#include "main.h"

/**
 * is_cmd - determines if a file is an executable cmd
 * @inf: inf struct
 * @path: path to file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *inf, char *path)
{
	struct stat st;

	(void)inf;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dplc_char - duplicates characters
 * @pathstr: PATH string
 * @start: start ind
 * @stop: stop ind
 *
 * Return: pointer to new buffer
 */
char *dplc_char(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * pathfind - finds cmd in PATH string
 * @inf:  inf struct
 * @pathstr:  PATH string
 * @cmd:  cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *pathfind(info_t *inf, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dplc_char(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(inf, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
