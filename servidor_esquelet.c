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

struct Datos {
    //short id;           // Id del usuario
    short opcion;       // Operacion que escoja el usuario
    float numeros[2]; // Numeros maximos que introducira el usuario
    float resultado;    
    int fracA[2];
    int fracB[2];
    int res_frac[2];
    int cuadrica[3];
    //short cookies[50];
};


//#define MIDA_BUFFER 1024
#define PORT 12345

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

//Funcio que fa el modul#define _USE_MATH_DEFINESalcula el factorial
int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
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
    return tot_be;
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
        char buffer[1024];
        int result;
        bool salir;
        printf("Servidor en espera de conexiones...\n");
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        while (1) {
            memset(buffer, 0, sizeof(buffer));
            read (client_socket, &salir, sizeof(salir));
            if (salir) {
                printf("Cliente ha cerrado la conexión.\n");
                break; // Cerramos la conexion. (Nota no podriamos hacerlo con un bool en el while por que ejecutaria todo el resto, interesa salir directamente).
            }
            
            struct Datos datos;
            read(client_socket, &datos.opcion, sizeof(datos.opcion));
            switch (datos.opcion) {
                case 1: // Suma
                    read(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                    read(client_socket, &datos.numeros[1], sizeof(datos.numeros[1]));
                    datos.resultado = suma(datos.numeros[0], datos.numeros[1]);
                    write(client_socket, &datos.resultado, sizeof(datos.resultado));
                    break;
                case 2: // Resta
                    read(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                    read(client_socket, &datos.numeros[1], sizeof(datos.numeros[1]));
                    datos.resultado = resta(datos.numeros[0], datos.numeros[1]);
                    write(client_socket, &datos.resultado, sizeof(datos.resultado));
                    break;
                case 3: // Multiplicación
                    read(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                    read(client_socket, &datos.numeros[1], sizeof(datos.numeros[1]));
                    datos.resultado = multiplicacio(datos.numeros[0], datos.numeros[1]);
                    write(client_socket, &datos.resultado, sizeof(datos.resultado));
                    break;
                case 4: // División
                    read(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                    read(client_socket, &datos.numeros[1], sizeof(datos.numeros[1]));
                    datos.resultado = divisio(datos.numeros[0], datos.numeros[1]);
                    write(client_socket, &datos.resultado, sizeof(datos.resultado));
                    break;
                 case 5: // Seno
                    read(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = seno(datos.numeros[0]);
                    write(client_socket, &datos.resultado, sizeof(datos.resultado));
                    break;
                case 6: // Coseno
                    read(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = coseno(datos.numeros[0]);
                    write(client_socket, &datos.resultado, sizeof(datos.resultado));                    
                    break;
                case 7: // Tangente
                    read(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = tangente(datos.numeros[0]);
                    write(client_socket, &datos.resultado, sizeof(datos.resultado));     
                    break;
                case 8: // ArcoSeno
                    read(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = arcSeno(datos.numeros[0]);
                    write(client_socket, &datos.resultado, sizeof(datos.resultado));     
                    break;
                case 9: // ArcoCoseno
                    read(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = arcCoseno(datos.numeros[0]);
                    write(client_socket, &datos.resultado, sizeof(datos.resultado));     
                    break;
                case 10: // ArcoTangente
                    read(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                    datos.resultado = arcTangente(datos.numeros[0]);
                    write(client_socket, &datos.resultado, sizeof(datos.resultado));     
                    break;
                case 11: // Potencia
                    // Lógica para la potencia
                    break;
                case 12: // Raiz Quadrada
                    // Lógica para la raíz cuadrada
                    break;
                case 13: // Modulo
                    // Lógica para el módulo
                    break;
                case 14: // Suma de Fracciones
                    read(client_socket, &datos.fracA[0], sizeof(datos.fracA[0]));
                    read(client_socket, &datos.fracA[1], sizeof(datos.fracA[1]));
                    read(client_socket, &datos.fracB[0], sizeof(datos.fracB[0]));
                    read(client_socket, &datos.fracB[1], sizeof(datos.fracB[1]));
                    sumarFraccion(datos.fracA[0], datos.fracA[1], datos.fracB[0], datos.fracB[1], &datos.res_frac[0], &datos.res_frac[1]);
                    write(client_socket, &datos.res_frac[0], sizeof(datos.res_frac[0]));
                    write(client_socket, &datos.res_frac[1], sizeof(datos.res_frac[1]));
                    break;
                case 15: // Resta de Fracciones
                    read(client_socket, &datos.fracA[0], sizeof(datos.fracA[0]));
                    read(client_socket, &datos.fracA[1], sizeof(datos.fracA[1]));
                    read(client_socket, &datos.fracB[0], sizeof(datos.fracB[0]));
                    read(client_socket, &datos.fracB[1], sizeof(datos.fracB[1]));
                    restarFraccion(datos.fracA[0], datos.fracA[1], datos.fracB[0], datos.fracB[1], &datos.res_frac[0], &datos.res_frac[1]);
                    write(client_socket, &datos.res_frac[0], sizeof(datos.res_frac[0]));
                    write(client_socket, &datos.res_frac[1], sizeof(datos.res_frac[1]));
                    break;
                case 16: // Multiplicación de Fracciones
                    read(client_socket, &datos.fracA[0], sizeof(datos.fracA[0]));
                    read(client_socket, &datos.fracA[1], sizeof(datos.fracA[1]));
                    read(client_socket, &datos.fracB[0], sizeof(datos.fracB[0]));
                    read(client_socket, &datos.fracB[1], sizeof(datos.fracB[1]));
                    multiplicarFraccion(datos.fracA[0], datos.fracA[1], datos.fracB[0], datos.fracB[1], &datos.res_frac[0], &datos.res_frac[1]);
                    write(client_socket, &datos.res_frac[0], sizeof(datos.res_frac[0]));
                    write(client_socket, &datos.res_frac[1], sizeof(datos.res_frac[1]));
                    break;
                case 17: // División de Fracciones
                    read(client_socket, &datos.fracA[0], sizeof(datos.fracA[0]));
                    read(client_socket, &datos.fracA[1], sizeof(datos.fracA[1]));
                    read(client_socket, &datos.fracB[0], sizeof(datos.fracB[0]));
                    read(client_socket, &datos.fracB[1], sizeof(datos.fracB[1]));
                    dividirFraccion(datos.fracA[0], datos.fracA[1], datos.fracB[0], datos.fracB[1], &datos.res_frac[0], &datos.res_frac[1]);
                    write(client_socket, &datos.res_frac[0], sizeof(datos.res_frac[0]));
                    write(client_socket, &datos.res_frac[1], sizeof(datos.res_frac[1])); // Revisar resultado!!
                    break;
                case 18: // Operación cuadrática
                    // Lógica para la operación cuadrática
                    break;
                default:
                    printf("Opción no válida. Inténtalo de nuevo.\n");
                    break;
            }
        }
        close(client_socket);
    }
    close(server_socket);
    return 0;
}
















