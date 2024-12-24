#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

void remove_vowels(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src == 'a' || *src == 'e' || *src == 'i' || *src == 'o' || *src == 'u' ||
            *src == 'A' || *src == 'E' || *src == 'I' || *src == 'O' || *src == 'U') {
            src++;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, stdin)) {
        remove_vowels(line);
        write(file, line, strlen(line));
    }

    close(file);
    printf("Child process finished.\n");
    return 0;
}
