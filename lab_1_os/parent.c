#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_LINE_LENGTH 1024

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid1, pid2;
    char filename1[MAX_LINE_LENGTH], filename2[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];
    int line_number = 0;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    printf("Enter filename for child1: ");
    fgets(filename1, sizeof(filename1), stdin);
    filename1[strcspn(filename1, "\n")] = '\0';

    printf("Enter filename for child2: ");
    fgets(filename2, sizeof(filename2), stdin);
    filename2[strcspn(filename2, "\n")] = '\0';

    // Создаем первый дочерний процесс
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipe1[1]); 
        close(pipe2[0]); 
        close(pipe2[1]); 

        dup2(pipe1[0], STDIN_FILENO);
        close(pipe1[0]);

        execl("./child", "./child", filename1, NULL);
        perror("execl error");
        exit(EXIT_FAILURE);
    }

    // Создаем второй дочерний процесс
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipe2[1]); 
        close(pipe1[0]); 
        close(pipe1[1]); 

        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[0]);

        execl("./child", "./child", filename2, NULL);
        perror("execl error");
        exit(EXIT_FAILURE);
    }

    // Родительский процесс
    close(pipe1[0]); 
    close(pipe2[0]); 

    while (fgets(line, sizeof(line), stdin)) {
        line_number++;
        if (line_number % 2 == 1) {
            write(pipe1[1], line, strlen(line) + 1);
        } else {
            write(pipe2[1], line, strlen(line) + 1);
        }
    }

    close(pipe1[1]);
    close(pipe2[1]);

    wait(NULL);
    wait(NULL);

    printf("Parent process finished.\n");
    return 0;
}
