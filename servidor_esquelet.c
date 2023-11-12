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
#include <pthread.h>

struct Datos {
    //short id;           // Id del usuario
    short opcion;       // Operacion que escoja el usuario
    float numeros[2]; // Numeros maximos que introducira el usuario
    float resultado;    
    //short cookies[50];
};

#define MAX_CLIENTS 3
#define PORT 12345
int num_clients = 3; // TE QUE SER UNA GLOBAL EN AQUEST CAS! 

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

    if (exponent == 0){
        return 1;
    }else{
        return pow(n1,exponent);
    }

}

//Funcio per a fer l'arrel quadrada amb el radicant que vulguis
float arrelQuadrada(float n1){
    return sqrt(n1);
}

//Funcio que fa el modul#define _USE_MATH_DEFINESalcula el factorial
int factorial(int n) {
    if (n == 0 || n == 1) { 
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

float modulo(int m){
    return abs(m);
}

// Trigonometricas

float seno (float num) {
    return sin((num * M_PI) / 180.0);
}

float coseno (float num) { 
    return cos((num * M_PI) / 180.0);
}

float tangente (float num) {
    return tan((num * M_PI) / 180.0);
}

float arcSeno (float num) {
    return (asin(num)*180)/ M_PI;
}

float arcCoseno (float num) {
    return (acos(num)*180)/ M_PI;
}

float arcTangente (float num) {
    return (atan(num)*180)/ M_PI;
}


void* mantenir_client(void* client_socket) {
    int client_fd = *(int*)client_socket;
    char buffer[1024];
    int result;
    bool salir;
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        read (client_fd, &salir, sizeof(salir));
        if (salir) {
            num_clients--;
            printf("Cliente ha cerrado la conexión [%d]\n", num_clients);
            break; // Cerramos la conexion. (Nota no podriamos hacerlo con un bool en el while por que ejecutaria todo el resto, interesa salir directamente).
        }
        struct Datos datos;
        read(client_fd, &datos.opcion, sizeof(datos.opcion));
        switch (datos.opcion) {
                case 1: // Suma
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    read(client_fd, &datos.numeros[1], sizeof(datos.numeros[1]));
                    datos.resultado = suma(datos.numeros[0], datos.numeros[1]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));
                    break;
                case 2: // Resta
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    read(client_fd, &datos.numeros[1], sizeof(datos.numeros[1]));
                    datos.resultado = resta(datos.numeros[0], datos.numeros[1]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));
                    break;
                case 3: // Multiplicación
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    read(client_fd, &datos.numeros[1], sizeof(datos.numeros[1]));
                    datos.resultado = multiplicacio(datos.numeros[0], datos.numeros[1]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));
                    break;
                case 4: // División
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    read(client_fd, &datos.numeros[1], sizeof(datos.numeros[1]));
                    datos.resultado = divisio(datos.numeros[0], datos.numeros[1]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));
                    break;
                 case 5: // Seno
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = seno(datos.numeros[0]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));
                    break;
                case 6: // Coseno
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = coseno(datos.numeros[0]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));                    
                    break;
                case 7: // Tangente
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = tangente(datos.numeros[0]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));     
                    break;
                case 8: // ArcoSeno
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = arcSeno(datos.numeros[0]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));     
                    break;
                case 9: // ArcoCoseno
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = arcCoseno(datos.numeros[0]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));     
                    break;
                case 10: // ArcoTangente
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = arcTangente(datos.numeros[0]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));     
                    break;
                case 11: // Potencia
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    read(client_fd, &datos.numeros[1], sizeof(datos.numeros[1]));
                    datos.resultado = potencia(datos.numeros[0], datos.numeros[1]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));
                    break;
                case 12: // Raiz Quadrada
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = arrelQuadrada(datos.numeros[0]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));
                    break;
                case 13: // Modulo
                    read(client_fd, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = modulo(datos.numeros[0]);
                    write(client_fd, &datos.resultado, sizeof(datos.resultado));     
                    break;
                default:
                    printf("Opción no válida. Inténtalo de nuevo.\n");
                    break;
            }
        }
    close(client_fd);
    free(client_socket);

         
}


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
    
    // Lógica del servidor para manejar la solicitud del cliente.
    while (1) {
        printf("Servidor en espera de conexiones...\n");
        if (num_clients > MAX_CLIENTS) {
            printf("Número máximo de clientes alcanzado. Espere...\n");
            sleep(1);
            continue; // Espera si se alcanzó el máximo de clientes.
        }

        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client_socket < 0) {
            perror("Error al aceptar la conexión del cliente");
            continue; // Continuar esperando conexiones.
        }
        num_clients++;
        printf("Cliente conectado! [%d]\n", num_clients);
        

        // Crea un hilo para manejar la conexión del cliente
        pthread_t thread; // Generar variable tipo pthread.
        int* client_fd = (int*)malloc(sizeof(int)); // Reserva memoria din (se guarda descriptor del cliente), se asigna dir memoria a puntero client_fd.
        *client_fd = client_socket; // Asignamos valor descriptor cliente.
        pthread_create(&thread, NULL, mantenir_client, (void*)client_fd); // Creamos el hilo usando la funcion manternir_client.

        // Se liberara espacio en memoria, cpu, etc automaticamente cuando termine el hilo.
        pthread_detach(thread);
    }
    
    close(server_socket);
    return 0;
}
















