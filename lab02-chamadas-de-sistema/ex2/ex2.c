#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 128

int main(void) {
    const char *arquivo_entrada = "lab2_ex2.txt";
    char buffer[BUFFER_SIZE];
    int qnt_linha = 0;
    
    // Abre o arquivo apenas para leitura
    int fd = open(arquivo_entrada, O_RDONLY);
    if (fd == -1) {
        perror("Erro ao abrir o arquivo.");
        return EXIT_FAILURE;
    }
    
    ssize_t bytes_read;
    // Ler o arquivo
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        // Contar o número de quebras de linha
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                qnt_linha++;
            }
        }
    }
    
    // Verificar erros na leitura
    if (bytes_read == -1) {
        perror("Erro ao ler o arquivo.");
        close(fd);
        return EXIT_FAILURE;
    }
    
    // Contar a última linha se o arquivo não terminar com uma nova linha
    if (bytes_read == 0 && buffer[bytes_read - 1] != '\n') {
        qnt_linha++;
    }
    
    // Fechar o arquivo
    if (close(fd) == -1) {
        perror("Erro ao fechar o arquivo.");
        return EXIT_FAILURE;
    }
    
    // Resultado
    printf("Número total de linhas: %d\n", qnt_linha);

    return EXIT_SUCCESS;
}