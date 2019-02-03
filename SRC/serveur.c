//
// Created by barbeaut on 16/01/19.
//

#include "client.h"
#define TAIL_BUF 20



int main(int argc, char** argv) {

    int port, socketConnexion, socketComm, sizeAddr, err;
    char buffer[TAIL_BUF];
    struct sockaddr_in addClient;

    if (argc != 2) {
        printf ("usage : %s port\n", argv[0]);
        return -1;
    }

    port  = atoi(argv[1]);

    socketConnexion = socketServeur(port);

    if(socketConnexion < -1){
        printf("Erreur lors de la création de la socket.\n");
        exit(2);
    }

    sizeAddr = sizeof(struct sockaddr_in);
    socketComm = accept(socketConnexion,(struct sockaddr *)&addClient, (socklen_t *)&sizeAddr);

    if (socketComm < 0) {
        perror("(serveurTCP) erreur sur accept");
        exit(3);
    }

    /*
     * reception et affichage du message en provenance du client
     */
    err = recv(socketComm, buffer, TAIL_BUF, 0);
    if (err <= 0) {
        perror("(serveurTCP) erreur dans la reception");
        shutdown(socketComm, SHUT_RDWR); close(socketComm);
        exit(4);
    }
    printf("(serveurTCP) voila le message recu : %s\n", buffer);


    /*
     * arret de la connexion et fermeture
     */
    shutdown(socketComm, SHUT_RDWR); close(socketComm);
    close(socketConnexion);

    return 0;

}