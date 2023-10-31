/* SERVIDOR (ESQUELET) */

/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MIDA_BUFFER 1024

int main(int argc, char **argv)
{

    if (argc == 2)
    {
        /* Definim variables */
        /* Fem la feina */

        int s; /* Per treballar amb el socket */
        /* Tanquem el socket */
        close(s);
    }

    else
    {
        printf("El nombre de paràmetres no és el correcte!\n");
    }
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

float arrelQuadrada(float n1, int radicant){
    return pow(n1, 1/radicant);
}

int  modul(float n1, float n2){
    return n1 % n2;
}

/*

Potenciación (^): Elevar un número a una potencia.
Raíz cuadrada (√): Calcular la raíz cuadrada de un número.
Módulo (%): Calcular el residuo de una división.
Operaciones trigonométricas: Seno, Coseno, Tangente, etc.
Logaritmos: Logaritmo natural (ln), logaritmo en base 10, etc.
Conversión de unidades: Conversión entre unidades de longitud, masa, temperatura, etc.
Factorización: Descomposición de números en factores primos.
Ecuaciones cuadráticas: Resolver ecuaciones cuadráticas de la forma ax^2 + bx + c = 0.
Cálculos de interés: Cálculos de interés simple y compuesto.
Conversión de bases numéricas: Convertir entre decimal, binario, octal y hexadecimal.
Conversión de unidades de tiempo: Conversión entre segundos, minutos, horas, días, etc.
Constantes matemáticas: Incluir constantes como π (pi) y e (número de Euler).
Operaciones de fracciones: Sumar, restar, multiplicar y dividir fracciones.

*/


float funcionesTrigonometricas()