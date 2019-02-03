//
// Created by barbeaut on 18/01/19.
//

/* include standards */
#include "recepteur.h"

/* taille du buffeur de reception */
#define TAIL_BUF 100


int main(int argc, char** argv) {
    int     sock,	        /* descripteur de socket locale */
            err;	        /* code d'erreur */

    struct sockaddr_in adrEmet;         /* adresse emetteur */

    char buffer[TAIL_BUF];       	/* buffer de reception */

    int sizeAddr;	                /* taille de l'adresse d'une socket */


    if (argc != 2) {
        printf("usage : %s port\n", argv[0]);
        return -1;
    }

    /* creation de la socket, protocole UDP */
    int port = atoi(argv[1]);
    sock = socketUDP(port);
    if(sock < 0){
        perror("(emetteur) erreur sur socketUDP");
        return -5;
    }

    /*
     * reception et affichage du message en provenance de l'emetteur
     */
    sizeAddr = sizeof(struct sockaddr_in);
    err = recvfrom(sock, buffer, TAIL_BUF, 0, (struct sockaddr*)&adrEmet,
                   (socklen_t *)&sizeAddr);
    if (err <= 0) {
        perror("(recepteur) erreur dans la reception");
        close(sock);
        return -4;
    }
    printf("(recepteur) Le message recu : %s\n", buffer);

    /* fermeture de la socket */
    close(sock);

    return 0;
}