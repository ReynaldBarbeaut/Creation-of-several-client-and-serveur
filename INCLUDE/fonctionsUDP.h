//
// Created by barbeaut on 18/01/19.
//

#ifndef TP1_BARBEAUT_FONCTIONSUDP_H
#define TP1_BARBEAUT_FONCTIONSUDP_H

/* inclusions standards */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

/* inclusions socket */
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>



//Permet la création d'une socket en mode non connecté
int socketUDP(ushort nPort);

//Permet d'initialiser une adresse de socket
int adresseUDP(char* nomMachine, ushort nPort, struct sockaddr_in* add);

#endif //TP1_BARBEAUT_FONCTIONSUDP_H
