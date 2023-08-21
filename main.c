#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void execute(char** argument, char **buf, size_t *n, char* arge[], char* argv[]);

void prompt(char **buf, size_t *n, char* arge[], char* argv[])
{
    size_t len;
    char **argument;
    int read;
    char *del;
    char *token;
    int j;

    del = " ";
    j = 0;
    argument = malloc(sizeof(char*) * 64);

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
 token = strtok(*buf, del);

    while(token)
    {
            argument[j] = token;
            token = strtok(NULL, del);
            j++;
    }

    argument[j] = NULL;

    execute(argument, buf, n, arge, argv);
    free(argument);
}

void execute(char** argument, char **buf, size_t *n, char* arge[], char* argv[])
{
    pid_t pid;
    int val,i,exefile,j;
    char *executable;
    char *path;
    char *token;
    char *del;
    char **directories;
    char *concat;
    struct stat file;
    char *path_cpy;

    executable = strdup(argument[0]);
    path = getenv("PATH");
    del = ":";
    directories = malloc(sizeof(char *) * 64);
    i = 0;

    if(executable[0] != '/')
    {
            path_cpy = strdup(path);
            token = strtok(path_cpy, del);
            while(token)
{
                    directories[i] = token;
                    token = strtok(NULL, del);
                    i++;
            }
            free(path_cpy);
            directories[i] = NULL;
            j = 0;
            while(directories[j] != NULL)
            {
                    concat = malloc(strlen(directories[j]) + strlen(executable) + 2);
                    strcpy(concat, directories[j]);
                    concat = strcat(concat, "/");
                    concat = strcat(concat, executable);
                    exefile = stat(concat, &file);
                    j++;
                    if(exefile == 0)
                    {
                            argument[0] = concat;
                            break;
                    } else if(exefile == -1)
                    {
                            free(concat);
                           continue;
                    }
                    free(concat);
            }
    }

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
    else
    {
        wait(NULL);
        prompt(buf, n, arge, argv);
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
