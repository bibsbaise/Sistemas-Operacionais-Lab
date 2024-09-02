#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 128

int main(){
    const char *arquivo_entrada = "lab2_ex3_origem.txt";
    const char *arquivo_destino = "lab2_ex3_destino.txt";
    char buffer[BUFFER_SIZE];
    
    //Abre o arquivo origem apenas para leitura
    int fd_origem = open(arquivo_entrada, O_RDONLY);
    if (fd_origem == -1) {
        perror("Erro ao abrir o arquivo.");
        return EXIT_FAILURE;
    }
    
    //Abre e cria o arquivo destino apenas para escrita
    int fd_destino = open(arquivo_destino, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_destino == -1) {
        perror("Erro ao abrir o arquivo de destino.");
        close(fd_origem);
        return EXIT_FAILURE;
    }
    
    ssize_t bytes_read, bytes_written;
    // Lê o arquivo origem e escreve no arquivo destino
    while ((bytes_read = read(fd_origem, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(fd_destino, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Erro ao escrever no arquivo de destino.");
            close(fd_origem);
            close(fd_destino);
            return EXIT_FAILURE;
        }
    }
    
    // Verificar erros na leitura
    if (bytes_read == -1) {
        perror("Erro ao ler o arquivo de origem.");
        close(fd_origem);
        close(fd_destino);
        return EXIT_FAILURE;
    }
    
    // Fechar os arquivos
    if (close(fd_origem) == -1) {
        perror("Erro ao fechar o arquivo de origem.");
        close(fd_destino);
        return EXIT_FAILURE;
    }
    
    if (close(fd_destino) == -1) {
        perror("Erro ao fechar o arquivo de destino.");
        return EXIT_FAILURE;
    }
    
    printf("Sucesso!");

    return EXIT_SUCCESS;
    
}
