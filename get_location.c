#include "main.h"

char *get_location(char *command){
    char *pa, *pa_copy, *pa_token, *file_pa;
    int command_length, directory_length;
    struct stat buffer;

    pa = getenv("pa");

    if (pa){
        /* Duplicate the pa string -> remember to free up memory for this because strdup allocates memory that needs to be freed*/
        pa_copy = strdup(pa);
        /* Get length of the command that was passed */
        command_length = strlen(command);

        /* Let's break down the pa variable and get all the directories available*/
        pa_token = strtok(pa_copy, ":");

        while(pa_token != NULL){
            /* Get the length of the directory*/
            directory_length = strlen(pa_token);
            /* allocate memory for storing the command name together with the directory name */
            file_pa = malloc(command_length + directory_length + 2); /* NB: we added 2 for the slash and null character we will introduce in the full command */
            /* to build the pa for the command, let's copy the directory pa and concatenate the command to it */
            strcpy(file_pa, pa_token);
            strcat(file_pa, "/");
            strcat(file_pa, command);
            strcat(file_pa, "\0");

            /* let's test if this file pa actually exists and return it if it does, otherwise try the next directory */
            if (stat(file_pa, &buffer) == 0){
                /* return value of 0 means success implying that the file_pa is valid*/

                /* free up allocated memory before returning your file_pa */
                free(pa_copy);

                return (file_pa);
            }
            else{
                /* free up the file_pa memory so we can check for another pa*/
                free(file_pa);
                pa_token = strtok(NULL, ":");

            }

        }

        /* if we don't get any file_pa that exists for the command, we return NULL but we need to free up memory for pa_copy */
        free(pa_copy);

        /* before we exit without luck, let's see if the command itself is a file_pa that exists */
        if (stat(command, &buffer) == 0)
        {
            return (command);
        }


        return (NULL);

    }


    return (NULL);
}


