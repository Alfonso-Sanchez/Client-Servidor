/* CLIENT (ESQUELET) */

/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MIDA_BUFFER 1024
#define PORT 12345

struct Datos {
    //short id;           // Id del usuario
    short opcion;       // Operacion que escoja el usuario
    float numeros[2]; // Numeros maximos que introducira el usuario
    float resultado;    
    //short cookies[50];
};

void menu () {
    
    printf("1. Suma\n");
    printf("2. Resta\n");
    printf("3. Multiplicacion\n");
    printf("4. Division\n");
    printf("5. Seno\n");
    printf("6. Coseno\n");
    printf("7. Tangente\n");
    printf("8. ArcoSeno\n");
    printf("9. ArcoCoseno\n");
    printf("10. ArcoTangente\n");
    printf("11. Potencia\n");
    printf("12. Raiz Quadrada\n");
    printf("13. Modulo\n");
}


int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    struct Datos datos;


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

    char input[MIDA_BUFFER];
    int result;
    bool salir;
    bool num_max;
    while (1) {

        menu();
        int operacion;
        float resultado;
        printf("Ingrese una operacion a realizar (o 'num fuera de lista' para salir): ");
        //fgets(input, sizeof(input), stdin); // dato cliente 

        scanf("%d", &operacion);

        if (operacion < 1 || operacion > 18) {
            salir = true;
        }
        write(client_socket, &salir, sizeof(salir)); // Indicamos si se va a cerrar la conexion con el cliente. 
        if (salir) {
            break; // Cerramos la conexion. (Nota no podriamos hacerlo con un bool en el while por que ejecutaria todo el resto, interesa salir directamente).
        }

        // Pasamos ahora la opcion seleccionada! 
        datos.opcion = operacion;

        write(client_socket, &datos.opcion, sizeof(datos.opcion));
         switch (datos.opcion) {
            case 1: // Suma
                printf("Has seleccionado SUMAR!\n");
                printf("Numero A: ");
                scanf("%f", &datos.numeros[0]);
                printf("\n");
                printf("Numero B: ");
                scanf("%f", &datos.numeros[1]);
                printf("\n");
                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                write(client_socket, &datos.numeros[1], sizeof(datos.numeros[1]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            case 2: // Resta
                printf("Has seleccionado RESTAR!\n");
                printf("Numero A: ");
                scanf("%f", &datos.numeros[0]);
                printf("\n");
                printf("Numero B: ");
                scanf("%f", &datos.numeros[1]);
                printf("\n");
                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                write(client_socket, &datos.numeros[1], sizeof(datos.numeros[1]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            case 3: // Multiplicación
                printf("Has seleccionado MULTIPLICACION!\n");
                printf("Numero A: ");
                scanf("%f", &datos.numeros[0]);
                printf("\n");
                printf("Numero B: ");
                scanf("%f", &datos.numeros[1]);
                printf("\n");
                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                write(client_socket, &datos.numeros[1], sizeof(datos.numeros[1]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            case 4: // División
                printf("Has seleccionado DIVISION!\n");
                printf("Numero A: ");
                scanf("%f", &datos.numeros[0]);
                printf("\n");
                printf("Numero B: ");
                scanf("%f", &datos.numeros[1]);
                while (datos.numeros[1] == 0) {
                    if (datos.numeros[1] == 0) {
                        printf("No se puede dividir entre 0 :)\n");
                    }
                    printf("\n");
                    printf("Numero B: ");
                    scanf("%f", &datos.numeros[1]);
                }
                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                write(client_socket, &datos.numeros[1], sizeof(datos.numeros[1]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
             case 5: // Seno
                printf("Has seleccionado calcular el SENO!\n");
                printf("Numero: ");
                scanf("%f", &datos.numeros[0]);
                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            case 6: // Coseno
                printf("Has seleccionado calcular el COSENO!\n");
                printf("Numero: ");
                scanf("%f", &datos.numeros[0]);
                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            case 7: // Tangente
                printf("Has seleccionado calcular la TANGENTE!\n");
                printf("Numero: ");
                scanf("%f", &datos.numeros[0]);
                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            case 8: // ArcoSeno
                printf("Has seleccionado calcular el ARCOSENO!\n");
                printf("Numero: ");
                scanf("%f", &datos.numeros[0]);
                while (datos.numeros[0] < -1 || datos.numeros[0] > 1) {
                    printf("El ángulo ingresado no es válido. Debe estar en el rango [-1, 1].\n");
                    scanf("%f", &datos.numeros[0]);
                }
                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            case 9: // ArcoCoseno
                printf("Has seleccionado calcular el ARCOCOSENO!\n");
                printf("Numero: ");
                scanf("%f", &datos.numeros[0]);
                while (datos.numeros[0] < -1 || datos.numeros[0] > 1) {
                    printf("El ángulo ingresado no es válido. Debe estar en el rango [-1, 1].\n");
                    scanf("%f", &datos.numeros[0]);
                }
                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            case 10: // ArcoTangente
                printf("Has seleccionado calcular el ARCOTANGENTE!\n");
                printf("Numero: ");
                scanf("%f", &datos.numeros[0]);
                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            case 11: // Potencia
                printf("Has seleccionado calcular la POTENCIA!\n");
                printf("Numero a elevar: ");
                scanf("%f", &datos.numeros[0]);
                printf("Exponent: ");
                scanf("%f", &datos.numeros[1]);

                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                write(client_socket, &datos.numeros[1], sizeof(datos.numeros[1]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            case 12: // Raiz Quadrada
                printf("Has seleccionado calcular la RAIZ CUADRADA!\n");
                printf("Numero a hacer la raiz: ");
                scanf("%f", &datos.numeros[0]);

                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            case 13: // Modulo
                printf("Has seleccionado calcular el MODULO!\n");
                printf("Numero a hacer el modulo: ");
                scanf("%f", &datos.numeros[0]);

                write(client_socket, &datos.numeros[0], sizeof(datos.numeros[0]));
                read(client_socket, &datos.resultado, sizeof(datos.resultado));
                printf("Resultado %0.2f\n", datos.resultado);
                break;
            default:
                printf("Opción no válida. Inténtalo de nuevo.\n");
                break;
        }
        

    }
    close(client_socket);
    return 0;
}