#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


// paginas Manual: fork 2, pipe 2 (plantilla), dup 2

int main (int argc, char ** argv){
    int pipefd[2]; // Extremo de escritura fd[1] y lecutra fd[0]
    pid_t cpid;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0) {    /* Hijo de tubería y ejecuta com2 arg2 */
        dup2(pipefd[0], 0); // Redirecciona entrada estándar al extremo de lectura
        close(pipefd[1]);          /* Close unused write end */
        close(pipefd[0]);
        execlp(argv[3], argv[3], argv[4]);
        _exit(EXIT_SUCCESS);
    }
    else { /* Padre  de tubería y ejecuta com1 arg1*/
        dup2(pipefd[1], 1); // Redirecciona salida estándar al extremo de escritura
        close(pipefd[0]);          /* Close unused read end */
        close(pipefd[1]);       /* Reader will see EOF */
        execlp(argv[1], argv[1], argv[2]);
        exit(EXIT_SUCCESS);
    }
}