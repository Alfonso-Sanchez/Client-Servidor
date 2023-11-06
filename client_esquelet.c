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
    int fracA[2];
    int fracB[2];
    int res_frac[2];
    int cuadrica[3];
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
    printf("14. Suma de Fracciones\n");
    printf("15. Resta de Fracciones\n");
    printf("16. Multiplicacion de Fracciones\n");
    printf("17. Division de Fracciones\n");
    printf("18. Realizar operacion quadratica\n");
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
                // Lógica para la potencia
                break;
            case 12: // Raiz Quadrada
                // Lógica para la raíz cuadrada
                break;
            case 13: // Modulo
                // Lógica para el módulo
                break;
            case 14: // Suma de Fracciones
                printf("Has seleccionado SUMA DE FRACCIONES!\n");
                
                printf("Fraccion A\n");
                printf("Numerador: ");
                scanf("%d", &datos.fracA[0]);
                printf("\n");
                printf("Denominador: ");
                scanf("%d", &datos.fracA[1]);
                 while (datos.fracA[1] == 0) {
                    if (datos.fracA[1] == 0) {
                        printf("No se puede dividir entre 0 :)\n");
                    }
                    printf("\n");
                    printf("Denominador: ");
                    scanf("%d", &datos.fracA[1]);
                }


                printf("Fraccion B\n");
                printf("Numerador: ");
                scanf("%d", &datos.fracB[0]);
                printf("\n");
                printf("Denominador: ");
                scanf("%d", &datos.fracB[1]);
                 while (datos.fracB[1] == 0) {
                    if (datos.fracB[1] == 0) {
                        printf("No se puede dividir entre 0 :)\n");
                    }
                    printf("\n");
                    printf("Denominador: ");
                    scanf("%d", &datos.fracB[1]);
                }

                write(client_socket, &datos.fracA[0], sizeof(datos.fracA[0]));
                write(client_socket, &datos.fracA[0], sizeof(datos.fracA[1]));
                write(client_socket, &datos.fracB[0], sizeof(datos.fracB[0]));
                write(client_socket, &datos.fracB[0], sizeof(datos.fracB[1]));
                read(client_socket, &datos.res_frac[0], sizeof(datos.res_frac[0]));
                read(client_socket, &datos.res_frac[1], sizeof(datos.res_frac[1]));

                printf("Resultat es %d | %d \n", datos.res_frac[0], datos.res_frac[1]);
                break;
            case 15: // Resta de Fracciones
                 printf("Has seleccionado RESTA DE FRACCIONES!\n");
                
                printf("Fraccion A\n");
                printf("Numerador: ");
                scanf("%d", &datos.fracA[0]);
                printf("\n");
                printf("Denominador: ");
                scanf("%d", &datos.fracA[1]);
                 while (datos.fracA[1] == 0) {
                    if (datos.fracA[1] == 0) {
                        printf("No se puede dividir entre 0 :)\n");
                    }
                    printf("\n");
                    printf("Denominador: ");
                    scanf("%d", &datos.fracA[1]);
                }


                printf("Fraccion B\n");
                printf("Numerador: ");
                scanf("%d", &datos.fracB[0]);
                printf("\n");
                printf("Denominador: ");
                scanf("%d", &datos.fracB[1]);
                 while (datos.fracB[1] == 0) {
                    if (datos.fracB[1] == 0) {
                        printf("No se puede dividir entre 0 :)\n");
                    }
                    printf("\n");
                    printf("Denominador: ");
                    scanf("%d", &datos.fracB[1]);
                }

                write(client_socket, &datos.fracA[0], sizeof(datos.fracA[0]));
                write(client_socket, &datos.fracA[0], sizeof(datos.fracA[1]));
                write(client_socket, &datos.fracB[0], sizeof(datos.fracB[0]));
                write(client_socket, &datos.fracB[0], sizeof(datos.fracB[1]));
                read(client_socket, &datos.res_frac[0], sizeof(datos.res_frac[0]));
                read(client_socket, &datos.res_frac[1], sizeof(datos.res_frac[1]));

                printf("Resultat es %d | %d \n", datos.res_frac[0], datos.res_frac[1]);
                break;
            case 16: // Multiplicación de Fracciones
                 printf("Has seleccionado MULTIPLACIONES DE FRACCIONES!\n");
                
                printf("Fraccion A\n");
                printf("Numerador: ");
                scanf("%d", &datos.fracA[0]);
                printf("\n");
                printf("Denominador: ");
                scanf("%d", &datos.fracA[1]);
                 while (datos.fracA[1] == 0) {
                    if (datos.fracA[1] == 0) {
                        printf("No se puede dividir entre 0 :)\n");
                    }
                    printf("\n");
                    printf("Denominador: ");
                    scanf("%d", &datos.fracA[1]);
                }


                printf("Fraccion B\n");
                printf("Numerador: ");
                scanf("%d", &datos.fracB[0]);
                printf("\n");
                printf("Denominador: ");
                scanf("%d", &datos.fracB[1]);
                 while (datos.fracB[1] == 0) {
                    if (datos.fracB[1] == 0) {
                        printf("No se puede dividir entre 0 :)\n");
                    }
                    printf("\n");
                    printf("Denominador: ");
                    scanf("%d", &datos.fracB[1]);
                }

                write(client_socket, &datos.fracA[0], sizeof(datos.fracA[0]));
                write(client_socket, &datos.fracA[0], sizeof(datos.fracA[1]));
                write(client_socket, &datos.fracB[0], sizeof(datos.fracB[0]));
                write(client_socket, &datos.fracB[0], sizeof(datos.fracB[1]));
                read(client_socket, &datos.res_frac[0], sizeof(datos.res_frac[0]));
                read(client_socket, &datos.res_frac[1], sizeof(datos.res_frac[1]));

                printf("Resultat es %d | %d \n", datos.res_frac[0], datos.res_frac[1]);
                break;
            case 17: // División de Fracciones
                 printf("Has seleccionado DIVISION DE FRACCIONES!\n");
                
                printf("Fraccion A\n");
                printf("Numerador: ");
                scanf("%d", &datos.fracA[0]);
                printf("\n");
                printf("Denominador: ");
                scanf("%d", &datos.fracA[1]);
                 while (datos.fracA[1] == 0) {
                    if (datos.fracA[1] == 0) {
                        printf("No se puede dividir entre 0 :)\n");
                    }
                    printf("\n");
                    printf("Denominador: ");
                    scanf("%d", &datos.fracA[1]);
                }


                printf("Fraccion B\n");
                printf("Numerador: ");
                scanf("%d", &datos.fracB[0]);
                printf("\n");
                printf("Denominador: ");
                scanf("%d", &datos.fracB[1]);
                 while (datos.fracB[1] == 0) {
                    if (datos.fracB[1] == 0) {
                        printf("No se puede dividir entre 0 :)\n");
                    }
                    printf("\n");
                    printf("Denominador: ");
                    scanf("%d", &datos.fracB[1]);
                }

                write(client_socket, &datos.fracA[0], sizeof(datos.fracA[0]));
                write(client_socket, &datos.fracA[0], sizeof(datos.fracA[1]));
                write(client_socket, &datos.fracB[0], sizeof(datos.fracB[0]));
                write(client_socket, &datos.fracB[0], sizeof(datos.fracB[1]));
                read(client_socket, &datos.res_frac[0], sizeof(datos.res_frac[0]));
                read(client_socket, &datos.res_frac[1], sizeof(datos.res_frac[1]));

                printf("Resultat es %d | %d \n", datos.res_frac[0], datos.res_frac[1]);
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
    return 0;
}