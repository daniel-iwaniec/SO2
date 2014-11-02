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
    int i = 0;

    while (1) {
        printf("COMMAND: ");

        if (getline(&command, &size, stdin) == -1) {
            printf("NIE PODANO KOMENDY\n");
            exit(EXIT_FAILURE);
        }
printf("COdsadsa");
        size = strlen(command) - 1;
        if (command[size] == '\n') {
            command[size] = '\0';
        }
printf("%s", command);
        pch = strtok(command, " ");
        strcpy(program, pch);
        arguments[i] = program;
        i++;

        printf("%s", arguments[0]);
        
        while (pch != NULL) {
            pch = strtok(NULL, " ");
            arguments[i] = pch;
            i++;
        }
        arguments[i] = NULL;

        childPid = fork();

        if (childPid != 0) {
            childPid = wait(&status);

            if (strcmp(command, "exit") == 0) {
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
            strcat(path, program);

            if (access(path, F_OK) == 0) {
                //execl(path, program, NULL);
                execv(path, arguments);
                exit(EXIT_SUCCESS);
            } else {
                exit(EXIT_FAILURE);
            }
        }
    }

    return EXIT_SUCCESS;
}
