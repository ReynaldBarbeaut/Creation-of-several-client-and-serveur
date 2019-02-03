//
// Created by barbeaut on 16/01/19.
//

#include "client.h"
#define TAIL_BUF 20


int main(int argc, char** argv) {

    char chaine[TAIL_BUF];
    int sock, port, err;
    char* nomMachServ;


    if (argc != 3) {
        printf("usage : %s nom/IPServ port\n", argv[0]);
        exit(1);
    }

    nomMachServ = argv[1];
    port = atoi(argv[2]);

    sock = socketClient(nomMachServ,port);
    if(sock < 0){
        printf("Erreur lors de la création de la socket.\n");
        exit(2);
    }


    /*
     * saisie de la chaine
     */
    printf("(client) donner une chaine : ");
    scanf("%s", chaine);
    printf("(client) envoi de - %s - \n", chaine);

    /*
     * envoi de la chaine
     */
    err = send(sock, chaine, strlen(chaine) + 1, 0);
    if (err <= 0) { // if (err != strlen(chaine)+1) {
        perror("(client) erreur sur le send");
        shutdown(sock, SHUT_RDWR); close(sock);
        exit(3);
    }
    printf("(client) envoi de %s realise\n", chaine);

    /*
     * fermeture de la connexion et de la socket
     */
    shutdown(sock, SHUT_RDWR);
    close(sock);

    return 0;
}