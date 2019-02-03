/*
* Created by barbeaut on 23/01/19.
*   Ce programme permet la construction d'un réseau en anneau à l'aide des fonctions TCP écrites précedemment
*/

#include "anneauTCP.h"

#define TAIL_BUF 64
#define NB_BOUCLE 10



int main(int argc, char** argv) {

    int nPort, nextNPort, idProg, sock, sockComm, sockClient, sizeAddr, err, nb, c = 0;

    struct sockaddr_in addNextClient;

    char *machName;

    char str[TAIL_BUF];



    if(argc != 5){
        perror("usage : ./BIN/anneauTCP nPort nextMachName nextNPortMach idProg\n");
        exit(1);
    }

    nPort = atoi(argv[1]);
    nextNPort = atoi(argv[3]);

    if(nPort <= 0 || nextNPort <=0){
        perror("Problème les ports doivent être des entiers.\n");
        exit(2);
    }

    idProg = atoi(argv[4]);
    if(idProg <= 0){
        perror("Problème l'identifiant du programme doit être un entier supérieur à 0.\n");
        exit(2);

    }

    machName = argv[2];



    sock = socketServeur(nPort);

    if(sock < 0){
        printf("Erreur lors de la création de la socket.\n");
        exit(3);
    }

    sizeAddr = sizeof(struct sockaddr_in);

    if(idProg == 1){

        sprintf(str, "%d", 10);

        sockClient = socketClient(machName, nextNPort);
        if(sockClient < 0){
            shutdown(sock, SHUT_RDWR); close(sock);
            perror("Problème lors de la création de la socket client.\n");
            exit(4);
        }

        sockComm = accept(sock,(struct sockaddr *)&addNextClient, (socklen_t *)&sizeAddr);
        if (sockComm < 0) {
            shutdown(sock, SHUT_RDWR); close(sock);
            shutdown(sockClient, SHUT_RDWR); close(sockClient);
            perror("(serveurTCP) erreur sur accept");
            exit(5);
        }

        while(c < NB_BOUCLE) {
            err = send(sockClient, str, strlen(str) + 1, 0);
            if (err <= 0) {
                perror("Erreur sur le send");
                shutdown(sock, SHUT_RDWR);
                close(sock);
                shutdown(sockClient, SHUT_RDWR);
                close(sockClient);
                shutdown(sockComm, SHUT_RDWR);
                close(sockComm);
                exit(6);
            }
            printf("(Envoi de %s realise\n", str);


            err = recv(sockComm, str, TAIL_BUF, 0);
            if (err <= 0) {
                perror("(serveurTCP) erreur dans la reception");
                shutdown(sock, SHUT_RDWR);
                close(sock);
                shutdown(sockClient, SHUT_RDWR);
                close(sockClient);
                shutdown(sockComm, SHUT_RDWR);
                close(sockComm);
                exit(7);
            }
            printf("Voila le message recu : %s\n", str);

            nb = atoi(str) + 10;
            sprintf(str, "%d", nb);
            c++;
        }
    }else{

        sockComm = accept(sock,(struct sockaddr *)&addNextClient, (socklen_t *)&sizeAddr);
        if (sockComm < 0) {
            shutdown(sock, SHUT_RDWR); close(sock);
            perror("(serveurTCP) erreur sur accept");
            exit(4);
        }

        sockClient = socketClient(machName, nextNPort);
        if(sockClient < 0){
            shutdown(sock, SHUT_RDWR); close(sock);
            shutdown(sockComm, SHUT_RDWR); close(sockComm);
            perror("Problème lors de la création de la socket client.\n");
            exit(5);
        }


        while ( c < NB_BOUCLE ) {
            err = recv(sockComm, str, TAIL_BUF, 0);
            if (err <= 0) {
                perror("(serveurTCP) erreur dans la reception");
                shutdown(sock, SHUT_RDWR);
                close(sock);
                shutdown(sockClient, SHUT_RDWR);
                close(sockClient);
                shutdown(sockComm, SHUT_RDWR);
                close(sockComm);
                exit(6);
            }
            printf("Voila le message recu : %s\n", str);

            nb = atoi(str) + 10;
            sprintf(str, "%d", nb);


            err = send(sockClient, str, strlen(str) + 1, 0);
            if (err <= 0) {
                perror("Erreur sur le send");
                shutdown(sock, SHUT_RDWR);
                close(sock);
                shutdown(sockClient, SHUT_RDWR);
                close(sockClient);
                shutdown(sockComm, SHUT_RDWR);
                close(sockComm);
                exit(7);
            }
            printf("(Envoi de %s realise\n", str);
            c++;
        }


    }





    shutdown(sock, SHUT_RDWR); close(sock);
    shutdown(sockClient, SHUT_RDWR); close(sockClient);
    shutdown(sockComm, SHUT_RDWR); close(sockComm);
}