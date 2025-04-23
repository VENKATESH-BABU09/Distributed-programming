#include<stdio.h>
#include<stdlib.h>
#include "fact.h"

int facto(int num){
    if(num==0 || num==1){
        return 1;
    }

    return num*facto(num-1);
}

int * fact_1_svc(num *fact, struct svc_req *b){
    static int result;

    result=facto(fact->a);
    return &result;

}