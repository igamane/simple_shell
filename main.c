#include "main.h"

/*
 * main - the main function
 *
 * @argc: argument count
 * @argv: argument vector
 * @arge: argument envirement variables
 *
 * return: always 0
 */

int main(int argc __attribute__((unused)),
	char *argv[],
	char *arge[])
{
	char *buf;
	size_t n;

	buf = NULL;
	n = 0;

	prompt(&buf, &n, arge, argv);

	free(buf);
	return (0);
}
