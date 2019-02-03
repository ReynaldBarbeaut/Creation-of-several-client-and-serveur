//
// Created by barbeaut on 30/01/19.
//


#include "clientProtocole.h"



int main(int argc, char** argv) {

    char chaine[BUFF_SIZE];
    int sock, port, err;
    char* nomMachServ;
    bool finish = false;
    RetVal ret;

    int opert;

    TOper oper;


    if (argc != 2) {
        printf("usage : %s nom/IPServ \n", argv[0]);
        exit(1);
    }

    nomMachServ = argv[1];

    sock = socketClient(nomMachServ,PORT);
    if(sock < 0){
        printf("Erreur lors de la création de la socket.\n");
        exit(2);
    }



    while(!finish) {
        /*
         * saisie de la chaine
         */
        printf("(client) donner le premier opérande : ");
        scanf("%s", chaine);

        oper.oprd1 = atoi(chaine);

        printf("(client) donner le deuxième opérande : ");
        scanf("%s", chaine);

        oper.oprd2 = atoi(chaine);

        printf("(client) donner l'opérateur (entrez le nombre correspondant) 1 : +, 2 : -, 3 : /, 4 : *, 5 : quit programm : ");
        scanf("%s", chaine);

        opert = atoi(chaine);

        switch (opert) {

            case 1:
                oper.oprt = ADD;
                break;

            case 2:
                oper.oprt = SOUS;
                break;

            case 3:
                oper.oprt = DIV;
                break;

            case 4:
                oper.oprt = MULT;
                break;

            case 5 :
                oper.oprt = QUIT;
                break;

            default:
                printf("(client) Error the answer must be an int between 1 and 4. \n");
                shutdown(sock, SHUT_RDWR);
                close(sock);
                exit(3);
        }


        printf("(client) envoi de l'opération \n");

        /*
         * envoi de la chaine
         */
        err = send(sock, &oper, sizeof(TOper), 0);
        if (err <= 0) { // if (err != strlen(chaine)+1) {
            perror("(client) erreur sur le send");
            shutdown(sock, SHUT_RDWR);
            close(sock);
            exit(3);
        }
        printf("(client) envoi de l'opération realisé\n");


        err = recv(sock, &ret, sizeof(RetVal), 0);
        if (err <= 0) {
            perror("(serveurTCP) erreur dans la reception");
            shutdown(sock, SHUT_RDWR);
            close(sock);
            exit(4);
        } else if (ret.error == ERR_DIV_0) {
            printf("(client) erreur : impossible de divisé par zéro.\n Veuillez recommencer.\n");
        } else if (ret.error == ERR_SHUT) {
            printf("(client) arrêt du serveur et du client ...\n");
            finish = true;
        } else {
            printf("(client) résultat : %d \n", ret.val);

        }
    }
    /*
     * fermeture de la connexion et de la socket
     */
    shutdown(sock, SHUT_RDWR);
    close(sock);

    return 0;
}

