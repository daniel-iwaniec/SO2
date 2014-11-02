#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>

int main() {
    pid_t childPid;
    size_t size;
    int status;
    char *command = NULL;
    char program[1000];
    char path[1000];
    char * pch;
    char * arguments[100];
    char * p = NULL;
    char ** res = NULL;

    int n_spaces = 0, i;

    while (1) {
        printf("COMMAND: ");

        if (getline(&command, &size, stdin) == -1) {
            printf("NIE PODANO KOMENDY\n");
            exit(EXIT_FAILURE);
        }
        size = strlen(command) - 1;
        if (command[size] == '\n') {
            command[size] = '\0';
        }
        
        char * p = strtok(command, " ");
        while (p) {
            res = realloc(res, sizeof (char*) * ++n_spaces);
            if (res == NULL)
                exit(-1);
            res[n_spaces - 1] = p;
            p = strtok(NULL, " ");
        }

        res = realloc(res, sizeof (char*) * (n_spaces + 1));
        res[n_spaces] = 0;

        for (i = 0; i < (n_spaces + 1); ++i)
            printf("res[%d] = %s\n", i, res[i]);

        childPid = fork();

        if (childPid != 0) {
            childPid = wait(&status);

            if (strcmp(res[0], "exit") == 0) {
                exit(EXIT_SUCCESS);
            }

            if (WEXITSTATUS(status) != 0) {
                printf("KOMENDA NIEOBSLUGIWANA\n");
            }
        } else {
            if (access("/cygwin64/bin/", F_OK) == 0) {
                strcpy(path, "/cygwin64/bin/");
            } else {
                strcpy(path, "/bin/");
            }
            strcat(path, res[0]);

            if (access(path, F_OK) == 0) {
                execv(path, res);
                exit(EXIT_SUCCESS);
            } else {
                exit(EXIT_FAILURE);
            }
        }
    }

    return EXIT_SUCCESS;
}
