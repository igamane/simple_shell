#include "main.h"

/**
 * execute - display the prompt to the user
 *
 * @argument: command arguments
 * @buf: buf
 * @n: n
 * @arge: envirement variables argument
 * @argv: arguments
 *
 * return: none
 */

void execute(char **argument, char **buf,
		size_t *n, char *arge[], char *argv[])
{
	pid_t pid;
	int val;

	handel_path(argument);

	pid = fork();
	if (pid == 0)
	{
		val = execve(argument[0], argument, arge);
		if (val == -1)
		{
			fprintf(stderr, "%s: ", argv[0]);
			perror("");
			exit(1);

	} else
	{
		wait(NULL);
		prompt(buf, n, arge, argv);
	}
}
