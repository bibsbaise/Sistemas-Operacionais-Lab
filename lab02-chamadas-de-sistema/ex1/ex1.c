#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 128

int main(void){
    const char *arquivo_entrada = "lab2_ex1.txt";
    char buffer[BUFFER_SIZE + 1];
    
    // Abre o arquivo apenas para leitura
    int fd = open(arquivo_entrada, O_RDONLY);
    
    if (fd == -1) {
        perror("Erro ao abrir o arquivo.");
        return EXIT_FAILURE;
    }
    
    ssize_t bytes_read;
    
    // Ler o arquivo
    while((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0){
        buffer[bytes_read] = '\0'; // Adiciona o terminador nulo no final do buffer
        printf("%s", buffer); // Imprime o conteúdo do buffer na saída padrão
    }
    
    // Verificar erros na leitura
    if (bytes_read == -1) {
        perror("Erro ao ler o arquivo.");
        close(fd);
        return EXIT_FAILURE;
    }
    
    // Fechar o arquivo
    if (close(fd) == -1) {
        perror("Erro ao fechar o arquivo.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

