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

#define MIDA_BUFFER 1024

int main(int argc, char **argv)
{

    if (argc == 3)
    {

        int s; /* Per treballar amb el socket */
        struct sockaddr_in adr;
        char buffer[MIDA_BUFFER];
        int i;

        /* Definim variables */
        /* Fem la feina */


        /* Tanquem el socket */
        close(s);
    }

    else
    {
        printf("El nombre de paràmetres no és el correcte!\n");
    }

    return 0;
}