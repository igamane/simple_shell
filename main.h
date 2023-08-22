#ifndef PROJECT_HEADER
#define PROJECT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void execute(char **argument, char **buf,
                size_t *n, char *arge[], char *argv[]);
void prompt(char **buf, size_t *n, char *arge[], char *argv[]);
void handel_path(char **argument);

#endif
