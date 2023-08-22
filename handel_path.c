#include "main.h"

/**
 * handel_path - handel the path
 *
 * @argument: arguments
 *
 * return: none
 */

void handel_path(char **argument)
{
	char *executable, *path, *del, *path_cpy, *token, *concat;
	char **directories;
	int i, exefile, j;
	struct stat file;

	path = getenv("PATH"), del = ":", executable = strdup(argument[0]);
	directories = malloc(sizeof(char *) * 64);
	i = 0, j = 0;
	if (executable[0] != '/')
	{
		path_cpy = strdup(path);
		token = strtok(path_cpy, del);
		while (token)
		{
			directories[i] = token;
			token = strtok(NULL, del);
			i++;
		}
		free(path_cpy);
		directories[i] = NULL;
		while (directories[j] != NULL)
		{
			concat = malloc(strlen(directories[j]) + strlen(executable) + 2);
			strcpy(concat, directories[j]);
			concat = strcat(concat, "/");
			concat = strcat(concat, executable);
			exefile = stat(concat, &file);
			j++;
			if (exefile == 0)
			{
				argument[0] = concat;
				break;
			} else if (exefile == -1)
			{
				free(concat);
				continue;
			}
			free(concat);
		}
	}
}
