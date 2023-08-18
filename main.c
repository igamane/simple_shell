#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - main function
 *
 * @argc: argument count
 *
 * @argv: argument variables
 *
 * @arge: envirement
 *
 * return: always 0
 */

void execute(char** argument, char **buf, size_t *n, char* arge[], char* argv[]);

void prompt(char **buf, size_t *n, char* arge[], char* argv[])
{
    size_t len;
    char **argument;
    int read;

    argument = malloc(sizeof(char*) * 2);

    printf("#cisfun$ ");
    read = getline(buf, n, stdin);

    if(read == -1)
    {
            printf("\n");
            exit(-1);
    }

    len = strlen(*buf);

    if (len > 0 && (*buf)[len - 1] == '\n')
    {
        (*buf)[len - 1] = '\0';
    }

    argument[0] = *buf;
    argument[1] = NULL;

    execute(argument, buf, n, arge, argv);
    free(argument);
}

void execute(char** argument, char **buf, size_t *n, char* arge[], char* argv[])
{
    pid_t pid;
    int val;

    pid = fork();

    if (pid == 0)
    {
        val = execve(argument[0], argument, arge);
        if (val == -1)
        {
            fprintf(stderr, "%s: ", argv[0]);
            perror("");
            exit(1);
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
        prompt(buf, n, arge, argv);
    }
    else
    {
        perror("fork");
        exit(1);
    }
}

int main(int argc __attribute__((unused)),
         char *argv[],
         char* arge[])
{
    char *buf;
    size_t n;

    buf = NULL;
    n = 0;

    prompt(&buf, &n, arge, argv);

    free(buf);
    return 0;
}
