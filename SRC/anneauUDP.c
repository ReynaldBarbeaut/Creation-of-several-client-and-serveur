//
// Created by barbeaut on 29/01/19.
//

#include "anneauUDP.h"

#define TAIL_BUF 64
#define NB_BOUCLE 10



int main(int argc, char** argv) {
    int nPort, nextNPort, idProg, sock, err, nb, c = 0, sizeAddr;

    struct sockaddr_in addNext;

    char *machName;

    char str[TAIL_BUF];



    if(argc != 5){
        perror("usage : ./BIN/anneauUDP nPort nextMachName nextNPortMach idProg\n");
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

    sock = socketUDP(nPort);

    if(sock < 0){
        perror("Erreur sur socketUDP");
        return -5;
    }


    if(idProg == 1){

        sprintf(str, "%d", 10);

        err = adresseUDP(machName, nextNPort, &addNext);

        while(c < NB_BOUCLE) {

            err = sendto(sock, str, strlen(str) + 1, 0, (struct sockaddr *) &addNext, sizeof(struct sockaddr_in));

            if (err != strlen(str) + 1) {
                close(sock);
                perror("(Erreur sur sendto");
                return -5;
            }

            sizeAddr = sizeof(struct sockaddr_in);

            err = recvfrom(sock, str, TAIL_BUF, 0, NULL, (socklen_t * ) & sizeAddr);

            if (err <= 0) {
                perror("Erreur dans la reception");
                close(sock);
                return -4;
            }

            printf("Le message recu : %s\n", str);

            nb = atoi(str) + 10;

            sprintf(str, "%d", nb);
            c++;
        }



    }else{

        sizeAddr = sizeof(struct sockaddr_in);

        while(c < NB_BOUCLE) {

            err = recvfrom(sock, str, TAIL_BUF, 0, NULL, (socklen_t * ) & sizeAddr);

            if (err <= 0) {
                perror("Erreur dans la reception");
                close(sock);
                return -4;
            }
            printf("Le message recu : %s\n", str);


            nb = atoi(str) + 10;

            sprintf(str, "%d", nb);

            err = adresseUDP(machName, nextNPort, &addNext);

            err = sendto(sock, str, strlen(str) + 1, 0, (struct sockaddr *) &addNext, sizeof(struct sockaddr_in));

            if (err != strlen(str) + 1) {
                close(sock);
                perror("(Erreur sur sendto");
                return -5;
            }

            c++;

        }
    }

    close(sock);

}