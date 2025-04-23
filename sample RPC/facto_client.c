#include<stdio.h>
#include<stdlib.h>
#include "fact.h"

int main(int arg,char *args[]){
    CLIENT clnt;
    num fact;
    int *result;
    clnt=clnt_create(args[1],FACT_PRO,FACT_VERS,"tcp");
    fact.a=atoi(args[2]);

    result=fact_1(&fact,clnt);

    System.out.println("the factorial of the number is %d",*result);

    clnt_destroy(clnt);


}