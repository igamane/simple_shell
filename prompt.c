#include "main.h"

/**
 * prompt - display the prompt to the user
 *
 * @buf: buf
 * @n: n
 * @arge: envirement variables argument
 * @argv: arguments
 *
 * return: none
 */

void prompt(char **buf, size_t *n, char *arge[], char *argv[])
{
	size_t len;
	char **argument;
	int read, j;
	char *del, *token;

	del = " ";
	j = 0;
	argument = malloc(sizeof(char *) * 64);
	write(1, "#cisfun$ ", strlen("#cisfun$ "));
	read = getline(buf, n, stdin);

	if (read == -1)
	{
		write(1, "\n", strlen("\n"));
		exit(-1);
	}
	len = strlen(*buf);
	if (len > 0 && (*buf)[len - 1] == '\n')
	{
		(*buf)[len - 1] = '\0';
	}
	if (strcmp(*buf, "exit") == 0)
	{
		write(1, "exit\n\n\n[Disconnected...]\n",
				strlen("exit\n\n\n[Disconnected...]\n"));
		exit(0);
	}

	token = strtok(*buf, del);

	while (token)
	{
		argument[j] = token;
		token = strtok(NULL, del);
		j++;
	}

	argument[j] = NULL;
	execute(argument, buf, n, arge, argv);
	free(argument);
}
