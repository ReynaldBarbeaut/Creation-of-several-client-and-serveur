//
// Created by barbeaut on 18/01/19.
//

#include "emetteur.h"

#define TAIL_BUF 100
#define T_NOM 20


int main(int argc, char** argv) {
    int sock,               /* descripteur de la socket locale */
            port,               /* variables de lecture */
            sizeAddr, 	  /* taille de l'adresse d'une socket */
            err;                /* code d'erreur */
    char chaine[TAIL_BUF];

    char ipMachDest[T_NOM];   /* ip de la machine dest */

    struct sockaddr_in adrDest;     /* adresse de la socket distante */
    struct sockaddr_in adrLocal;	  /* adresse de la socket locale */


    if (argc != 2) {
        printf("usage : %s port\n", argv[0]);
        return -1;
    }

    /* creation de la socket, protocole UDP */
    sock = socketUDP(port);
    if(sock < 0){
        perror("(emetteur) erreur sur socketUDP");
        return -5;
    }

    /*
     * saisie et initialisation de l'adresse du destinataire
     */
    printf("(emetteur) donner la machine dest (@ip en notation decimale a point) : ");
    scanf("%s", ipMachDest);
    printf("(emetteur) donner le port dest : ");
    scanf("%d", &port);
    printf("(emetteur) initaddr pour %s, %d\n",  ipMachDest, port);

    /* initialisation de l'adresse de la socket */
    err = adresseUDP(ipMachDest, port, &adrDest);

    /*
     * saisie et envoi de la chaine
     */
    printf("(emetteur) donner la chaine : ");
    scanf("%s", chaine);
    printf("(emetteur) envoi de - %s - \n", chaine);

    err = sendto(sock, chaine, strlen(chaine)+1, 0,
                 (struct sockaddr*)&adrDest, sizeof(struct sockaddr_in));
    if (err != strlen(chaine)+1) {
        perror("(emetteur) erreur sur sendto");
        return -5;
    }

    printf("(emetteur) chaine envoyee\n");

    /* fermeture de la socket */
    close(sock);

    return 0;
}