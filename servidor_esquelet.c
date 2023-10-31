/* SERVIDOR (ESQUELET) */

/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


//#define MIDA_BUFFER 1024
#define PORT 12345


int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error al crear el socket del servidor");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al enlazar el socket del servidor");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Error al escuchar en el socket del servidor");
        exit(EXIT_FAILURE);
    }

    printf("Servidor en espera de conexiones...\n");

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

    // Lógica del servidor para manejar la solicitud del cliente.
    char buffer[1024];
    int result;
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        read(client_socket, buffer, sizeof(buffer));
        printf("Recibido: %s", buffer);

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Cliente ha cerrado la conexión.\n");
            break;
        }

        // Simulamos una operación de suma.
        sscanf(buffer, "%d", &result);
        result = result * 2;
        write(client_socket, &result, sizeof(result));
    }

    close(server_socket);
    return 0;
}



//Funcio per a sumar dos numeros
float suma(float n1, float n2){
    return n1+n2;
}

//Funcio per a restar dos numeros
float resta(float n1, float n2){
    return n1-n2;
}

//Funcio per a multiplicar dos numeros
float multiplicacio(float n1, float n2){
    return n1*n2;
}

//Funcio per a dividir dos numeros
float divisio(float n1, float n2){
    return n1/n2;
}

//Funcio per a elevar un numero a cert exponent
float potencia(float n1, float exponent){
    return pow(n1,exponent);
}

//Funcio per a fer l'arrel quadrada amb el radicant que vulguis
float arrelQuadrada(float n1, int radicant){
    return pow(n1, 1/radicant);
}

//Funcio que fa el modul d'un divisio
float modul(float n1, float n2){
    return fmod(n1,n2);
}

//Funcio recursiva que calcula el factorial
int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

// Trigonometricas

float seno (float num) {
    return sin(num);
}

float coseno (float num) {
    return cos(num);
}

float tangente (float num) {
    return tan(num);
}

float arcSeno (float num) {
    return asin(num);
}

float arcCoseno (float num) {
    return acos(num);
}

float arcTangente (float num) {
    return atan(num);
}

// Operaciones con fracciones
// Función para calcular el MCD usando el algoritmo de Euclides
int calcularMCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void sumarFraccion(int numeradorA, int denominadorA, int numeradorB, int denominadorB, int *numeradorR, int *denominadorR) {
    // Obtener factor común entre denominadorA y denominadorB
    *denominadorR = (denominadorA * denominadorB) / calcularMCD(denominadorA, denominadorB);

    // Ajustar numeradores según el nuevo denominador común
    numeradorA = numeradorA * (*denominadorR / denominadorA);
    numeradorB = numeradorB * (*denominadorR / denominadorB);

    // Sumar los numeradores
    *numeradorR = numeradorA + numeradorB;
}

void restarFraccion(int numeradorA, int denominadorA, int numeradorB, int denominadorB, int *numeradorR, int *denominadorR) {
    // Obtener factor común entre denominadorA y denominadorB
    *denominadorR = (denominadorA * denominadorB) / calcularMCD(denominadorA, denominadorB);

    // Ajustar numeradores según el nuevo denominador común
    numeradorA = numeradorA * (*denominadorR / denominadorA);
    numeradorB = numeradorB * (*denominadorR / denominadorB);

    // Restar los numeradores
    *numeradorR = numeradorA - numeradorB;
}

void multiplicarFraccion(int numeradorA, int denominadorA, int numeradorB, int denominadorB, int *numeradorR, int *denominadorR) {
    // Obtenemos el numeradorR.
    *numeradorR = numeradorA * numeradorB;
    // Obtenemos el denominadorR.
    *denominadorR = denominadorA * denominadorB;
}

void dividirFraccion(int numeradorA, int denominadorA, int numeradorB, int denominadorB, int *numeradorR, int *denominadorR) {
    // Obtenemos el numeradorR.
    *numeradorR = numeradorA * denominadorB;
    // Obtenemos el denominadorR.
    *denominadorR = denominadorA * numeradorB;
}
// Operacion eq 2 grado.
bool realizarCuadratica (int a, int b, int c, float *resultadoP, float *resultadoN) {
    // b^2 - 4*a*c
    bool tot_be = true;
    float raiz = pow(b, 2) - (4 * a * c);
    if (raiz < 0) {
        tot_be = false;
    } else
    {
          raiz = sqrt(raiz);
          int dosa = 2*a;
          int bneg = b * (-1);
          *resultadoP = (bneg + raiz) / dosa;
          *resultadoN = (bneg - raiz) / dosa;
    }
}











