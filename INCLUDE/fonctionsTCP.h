//
// Created by barbeaut on 16/01/19.
//

#ifndef TP1_BARBEAUT_FONCTIONSTCP_H
#define TP1_BARBEAUT_FONCTIONSTCP_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>


    int socketServeur(ushort nPort);

    int socketClient(char* nomMachine, ushort nPort);
#endif //TP1_BARBEAUT_FONCTIONSTCP_H
