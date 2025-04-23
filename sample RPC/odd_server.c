#include<stdio.h>
#include<stdlib.h>
#include "oddeven.h"

int * oddeven_1_svc(rpc *var, struct svc_req *b){

    static int result=0;
    for(int i=0;i<10;i++){
        if(var->arr[i]%2==0){
            result++;
        }
    }
    return &result;

}