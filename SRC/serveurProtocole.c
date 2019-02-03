//
// Created by barbeaut on 30/01/19.
//

#include "serveurProtocole.h"

int main(int argc, char** argv) {

    int port, socketConnexion, socketComm, sizeAddr, err;
    TOper oper;
    RetVal ret;
    bool finish = false;

    struct sockaddr_in addClient;


    socketConnexion = socketServeur(PORT);

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

    while(!finish) {
        err = recv(socketComm, &oper, sizeof(TOper), 0);
        if (err <= 0) {
            perror("(serveurTCP) erreur dans la reception");
            shutdown(socketComm, SHUT_RDWR);
            close(socketComm);
            close(socketConnexion);
            exit(4);
        }
        printf("(serveurTCP) opération bien reçu \n");

        if (oper.oprt == DIV && oper.oprd2 == 0) {
            ret.val = 0;
            ret.error = ERR_DIV_0;
        } else if (oper.oprt == QUIT) {
            finish = true;
            ret.val = 0;
            ret.error = ERR_SHUT;

        } else {
            ret.val = calcul(oper);
            ret.error = ERR_OK;
        }


        err = send(socketComm, &ret, sizeof(RetVal), 0);
        if (err <= 0) {
            perror("(serveur) erreur sur le send");
            shutdown(socketComm, SHUT_RDWR);
            close(socketComm);
            close(socketConnexion);
            exit(3);
        }
        printf("(serveur) envoi du résultat realisé\n");
    }


    /*
     * arret de la connexion et fermeture
     */
    shutdown(socketComm, SHUT_RDWR); close(socketComm);
    close(socketConnexion);

    return 0;

}