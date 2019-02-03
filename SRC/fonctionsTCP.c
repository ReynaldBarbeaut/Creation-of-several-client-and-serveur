//
// Created by barbeaut on 16/01/19.
//

#include "fonctionsTCP.h"


int socketServeur(ushort nPort){
    int socketConnexion, sizeAddr, err, enable;
    struct sockaddr_in addServ;


    socketConnexion = socket(AF_INET, SOCK_STREAM, 0);
    if(socketConnexion < 0){
        perror("(serveurTCP) erreur lors de la création de la socket");
        return -2;
    }


    addServ.sin_family = AF_INET;
    addServ.sin_port = htons(nPort); // conversion en format réseau (big endian)
    addServ.sin_addr.s_addr = INADDR_ANY;
    bzero(addServ.sin_zero, 8);

    sizeAddr = sizeof(struct sockaddr_in);


    enable = 1;
    if(setsockopt(socketConnexion, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
        perror("(serveurTCP) erreur sur le setsockopt");
        return -3;
    }

    err = bind(socketConnexion, (struct sockaddr *)&addServ, sizeAddr);
    if (err < 0) {
        perror("(serveurTCP) erreur sur le bind");
        close(socketConnexion);
        return -4;
    }

    err = listen(socketConnexion, 1);
    if (err < 0) {
        perror("(serveurTCP) erreur dans listen");
        close(socketConnexion);
        return -5;
    }

    return socketConnexion;
}


int socketClient(char* nomMachine, ushort nPort){

    int socketConnexion, err;
    struct sockaddr_in addSockServ;

    socklen_t sizeAdd;

    socketConnexion = socket(AF_INET, SOCK_STREAM, 0);
    if (socketConnexion < 0) {
        perror("(client) erreur sur la creation de socket");
        return -2;
    }

    addSockServ.sin_family = AF_INET;
    err = inet_aton(nomMachine, &addSockServ.sin_addr);
    if (err == 0) {
        perror("(client) erreur obtention IP serveur");
        close(socketConnexion);
        return -3;
    }


    addSockServ.sin_port = htons(nPort);
    bzero(addSockServ.sin_zero, 8);

    sizeAdd = sizeof(struct sockaddr_in);

    err = connect(socketConnexion, (struct sockaddr *)&addSockServ, sizeAdd);

    if (err < 0) {
        perror("(client) erreur a la connection de socket");
        close(socketConnexion);
        return -4;
    }

    return socketConnexion;
}