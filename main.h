#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void execmd(char **argv);
char *get_location(char *command)
{
    char *path, *path_copy;
    path = getenv("PATH");

}

