#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc > 1) {
        printf("hola %s\n", argv[1]);
    }

    exit(EXIT_SUCCESS);
}