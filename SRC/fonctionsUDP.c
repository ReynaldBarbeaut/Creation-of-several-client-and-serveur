//
// Created by barbeaut on 18/01/19.
//

#include "fonctionsUDP.h"


//Permet la création d'une socket en mode non connecté
int socketUDP(ushort nPort){
    int sock, err, sizeAddr;

    struct sockaddr_in adrRecep;

    /*
     * création de la socket en UDP
     */
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("(recepteur) erreur de socket");
        return -2;
    }

    /*
     * initialisation de l'adresse de la socket
     */
    adrRecep.sin_family = AF_INET;
    adrRecep.sin_port = htons(nPort);
    adrRecep.sin_addr.s_addr = INADDR_ANY;
    bzero(adrRecep.sin_zero, 8);

    sizeAddr = sizeof(struct sockaddr_in);


    /*
     * attribution de l'adresse a la socket
     */
    err = bind(sock, (struct sockaddr *)&adrRecep, sizeAddr);
    if (err < 0) {
        perror("(recepteur) erreur sur le bind");
        close(sock);
        return -3;
    }

    /*
     * retour de la socket créée
     */
    return sock;
}



//Permet d'initialiser une adresse de socket
int adresseUDP(char* nomMachine, ushort nPort, struct sockaddr_in* add){
    int err;

    add->sin_family = AF_INET;
    err = inet_aton(nomMachine, &add->sin_addr);
    if (err == 0) {
        perror("(emetteur) erreur obtention IP recepteur");
        return -2;
    }
    add->sin_port = htons(nPort);
    bzero(add->sin_zero, 8);
    return 1;
}

