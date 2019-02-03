//
// Created by barbeaut on 30/01/19.
//

#ifndef TP1_BARBEAUT_COMMON_H
#define TP1_BARBEAUT_COMMON_H

#define BUFF_SIZE 64
#define PORT 2607


typedef enum{
    ERR_OK,
    ERR_DIV_0,
    ERR_SHUT,
}TypeErr;

typedef enum {
    MULT,
    ADD,
    SOUS,
    DIV,
    QUIT,
}Oprt;


typedef struct{
    int oprd1;
    Oprt oprt;
    int oprd2;
}TOper;


typedef struct{
    TypeErr error;
    int val;
}RetVal;

int calcul(TOper oper);

#endif //TP1_BARBEAUT_COMMON_H
