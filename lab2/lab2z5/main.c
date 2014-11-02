#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    pid_t childPid;
    int firstRun = 1;
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
            childPid = wait();
            if (strcmp(command, "exit") == 0) {
                exit(EXIT_SUCCESS);
            }
        } else {
            printf("%s", command);
            exit(EXIT_SUCCESS);
        }
    }

    return EXIT_SUCCESS;
}
