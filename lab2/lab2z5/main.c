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
    char path[1000];
    char * p = NULL;
    char ** res = NULL;

    int n_spaces = 0, i;

    while (1) {
        printf("COMMAND: ");
        getline(&command, &size, stdin);

        size = strlen(command) - 1;
        if (command[size] == '\n') {
            command[size] = '\0';
        }

        n_spaces = 0;
        p = strtok(command, " ");
        while (p) {
            res = realloc(res, sizeof (char*) * ++n_spaces);
            res[n_spaces - 1] = p;
            p = strtok(NULL, " ");
        }
        res = realloc(res, sizeof (char*) * (n_spaces + 1));
        res[n_spaces] = 0;

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
