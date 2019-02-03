//
// Created by barbeaut on 30/01/19.
//

#include "common.h"


int calcul(TOper oper){

    switch (oper.oprt) {

        case MULT:
            return oper.oprd1 * oper.oprd2;

        case DIV:
            return oper.oprd1 / oper.oprd2;

        case SOUS:
            return oper.oprd1 - oper.oprd2;

        default:
            return oper.oprd1 + oper.oprd2;
    }

}
