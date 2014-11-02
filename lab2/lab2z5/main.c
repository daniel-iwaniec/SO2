#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/unistd.h>

int main() {
    pid_t childPid;
    int status, firstRun = 1;
    char command[100];

    while (1) {
        if (!firstRun) {
            printf("\n");
        } else {
            firstRun = 0;
        }
        printf("COMMAND: ");

        scanf("%s", command);

        childPid = fork();

        if (childPid != 0) {
            childPid = wait(&status);
            if (strcmp(command, "exit") == 0) {
                exit(EXIT_SUCCESS);
            }
        } else {
            execl(strcat("/bin/", command), command, NULL);
        }
    }

    return EXIT_SUCCESS;
}
