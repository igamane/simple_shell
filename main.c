#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute(char **argument, char **buf, size_t *n, char *arge[], char *argv[]);

void prompt(char **buf, size_t *n, char *arge[], char *argv[])
{
    size_t len;
    char **argument;
    int read;
    char *del;
    char *token;
    char *tokenTwo;
    char *buf_duplicate;
    int j, k, l;

    del = " ";
    j = 0;
    k = 0;

    printf("#cisfun$ ");
    read = getline(buf, n, stdin);

    if (read == -1)
    {
        printf("\n");
        exit(-1);
    }

    len = strlen(*buf);
    if (len > 0 && (*buf)[len - 1] == '\n')
    {
        (*buf)[len - 1] = '\0';
    }

    buf_duplicate = strdup(*buf);

    token = strtok(*buf, del);
    while (token)
    {
        token = strtok(NULL, del);
        j++;
    }

    argument = malloc(sizeof(char *) * (j + 1)); // +1 for NULL

    printf("%s\n", buf_duplicate);

    tokenTwo = strtok(buf_duplicate, del);
    argument[0] = tokenTwo;

    k = 1;
    while (tokenTwo)
    {
        tokenTwo = strtok(NULL, del);
        argument[k] = tokenTwo;
        k++;
    }
    free(buf_duplicate);
    argument[k] = NULL;

    for (l = 0; l < k; l++)
    {
        printf("%s\n", argument[l]);
    }

    execute(argument, buf, n, arge, argv);
    free(argument);
}

void execute(char **argument, char **buf, size_t *n, char *arge[], char *argv[])
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

int main(int argc __attribute__((unused)), char *argv[], char *arge[])
{
    char *buf;
    size_t n;

    buf = NULL;
    n = 0;

    prompt(&buf, &n, arge, argv);

    free(buf);
    return 0;
}
