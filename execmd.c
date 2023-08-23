#include "main.h"

void execmd(char **argv){
    char *co = NULL, *actual_co = NULL;

    if (argv){
        /* get the co */
        co = argv[0];

        /* generate the path to this co before passing it to execve */
        actual_co = get_location(co);

        /* execute the actual co with execve */
        if (execve(actual_co, argv, NULL) == -1){
            perror("Error:");
        }
    }

}

