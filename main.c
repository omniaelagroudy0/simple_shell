#include "main.h"

int main(int ac, char **argv){
    char *prompt = "(Eshell) $ ";
    char *ln_pt = NULL, *ln_pt_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;

    /* declaring void variables */
    (void)ac;

    /* Create a loop for the shell's prompt */
    while (1) {
        printf("%s", prompt);
        nchars_read = getline(&ln_pt, &n, stdin);
        /* check if the getline function failed or reached EOF or user use CTRL + D */
        if (nchars_read == -1){
            printf("Exiting shell....\n");
            return (-1);
        }

        /* allocate space for a copy of the ln_pt */
        ln_pt_copy = malloc(sizeof(char) * nchars_read);
        if (ln_pt_copy== NULL){
            perror("tsh: memory allocation error");
            return (-1);
        }
        /* copy ln_pt to ln_pt_copy */
        strcpy(ln_pt_copy, ln_pt);

        /********** split the string (ln_pt) into an array of words ********/
        /* calculate the total number of tokens */
        token = strtok(ln_pt, delim);

        while (token != NULL){
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * num_tokens);

        /* Store each token in the argv array */
        token = strtok(ln_pt_copy, delim);

        for (i = 0; token != NULL; i++){
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        /* execute the command */
        execmd(argv);

    }


    /* free up allocated memory */
    free(ln_pt_copy);
    free(ln_pt);

    return (0);
}

