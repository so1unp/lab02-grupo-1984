#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "Uso: %s [s|f] origen destino\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char modo = argv[1][0];
    char buffer[BUF_SIZE];

    if (modo == 's') {
        int fd_in = open(argv[2], O_RDONLY);
        if (fd_in < 0) { perror("Error origen"); exit(EXIT_FAILURE); }

        int fd_out = open(argv[3], O_WRONLY | O_CREAT | O_EXCL, 0644);
        if (fd_out < 0) { perror("Error destino"); close(fd_in); exit(EXIT_FAILURE); }

        ssize_t n;
        while ((n = read(fd_in, buffer, BUF_SIZE)) > 0) {
            if (write(fd_out, buffer, n) != n) {
                perror("Error escritura");
                close(fd_in);
                close(fd_out);
                exit(EXIT_FAILURE);
            }
        }

        if (n < 0) {
            perror("Error lectura");
            close(fd_in);
            close(fd_out);
            exit(EXIT_FAILURE);
        }

        close(fd_in);
        close(fd_out);
    }

    else if (modo == 'f') {
        FILE *f_in = fopen(argv[2], "rb");
        if (!f_in) { perror("Error origen"); exit(EXIT_FAILURE); }

        FILE *f_out = fopen(argv[3], "wbx");
        if (!f_out) { perror("Error destino"); fclose(f_in); exit(EXIT_FAILURE); }

        size_t n;
        while ((n = fread(buffer, 1, BUF_SIZE, f_in)) > 0) {
            if (fwrite(buffer, 1, n, f_out) != n) {
                perror("Error escritura");
                fclose(f_in);
                fclose(f_out);
                exit(EXIT_FAILURE);
            }
        }

        if (ferror(f_in)) {
            perror("Error lectura");
            fclose(f_in);
            fclose(f_out);
            exit(EXIT_FAILURE);
        }

        fclose(f_in);
        fclose(f_out);
    }

    else {
        fprintf(stderr, "Modo invalido. Use 's' o 'f'\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}