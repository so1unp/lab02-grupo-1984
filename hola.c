#include <stdio.h>      // printf()
#include <stdlib.h>     // exit()

int main(int argc, char *argv[])
{
    if (argc > 1) {
        printf("hola %s\n", argv[1]);
    }

    // Termina la ejecución del proceso.
    exit(EXIT_SUCCESS);
}