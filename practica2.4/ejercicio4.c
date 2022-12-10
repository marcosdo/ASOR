#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


// Manual mkfifo 3

int main(int argc, char **argv){
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *HOME = getenv("HOME"); // getenv 3 
    char *pipe = strcat(HOME, "/pipe");
    printf("HOME: %s\n", pipe);
  	mkfifo(pipe, 0222); // permiso solo escritura w

    int fd = open(pipe, O_WRONLY);
    write(fd, argv[1], strlen(argv[1]));
    close(fd);

    return 0;
}
