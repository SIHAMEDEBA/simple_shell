#include "main.h"

/**
 * custom_find_command - Finds the specified
 * command in the directories listed in PATH.
 *
 * @command: The command to search for.
 *
 * Return: A string representing the
 * folder where the command is located.
 **/

char *custom_find_command(char *command)
{
	DIR *dir_ptr;
	struct dirent *entry;
	char *current_cmd;
	char **env_var = environ;

	while (*env_var != NULL)
	{
		if (!strcmp_dir_name(*env_var, "PATH"))
		{
			char *path_variable = strtok(*env_var, "=");
			char *path_value = strtok(NULL, "=");

			if (path_value != NULL)
			{
				char *path_token = strtok(path_value, ":");

				while (path_token != NULL)
				{
					dir_ptr = opendir(path_token);

					if (dir_ptr == NULL)
					{
						perror("Error: Unable to open directory");
					}
					else
					{
					while ((entry = readdir(dir_ptr)))
						{
							current_cmd = entry->d_name;
							if (current_cmd != NULL && !strcmp_dir_name(current_cmd, command))
							{
								closedir(dir_ptr);
								return (path_token);
							}
						}
						closedir(dir_ptr);
					}
					path_token = strtok(NULL, ":");
				}
			}
		}
		env_var++;
	}
	return "Error: Command Not Found";
}
