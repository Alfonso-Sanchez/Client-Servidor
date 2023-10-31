/* CLIENT (ESQUELET) */

/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//#define MIDA_BUFFER 1024
#define PORT 12345

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error al crear el socket del cliente");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error al conectar al servidor");
        exit(EXIT_FAILURE);
    }

    char input[1024];
    int result;

    while (1) {
        printf("Ingrese un número (o 'exit' para salir): ");
        fgets(input, sizeof(input), stdin);

        write(client_socket, input, strlen(input));

        if (strcmp(input, "exit\n") == 0) {
            break;
        }

        read(client_socket, &result, sizeof(result));
        printf("Resultado: %d\n", result);
    }

    close(client_socket);
    return 0;
}