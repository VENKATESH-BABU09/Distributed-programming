#include<stdio.h>
#include<stdlib.h>
#include "oddeven.h"

int main(int arg,char *args[]){
    CLIENT *clnt;
    rpc var;
    int *result;
    clnt=clnt_create(args[1],ODD_EVEN_PR,ODD_EVEN_V,"tcp");
    printf("enter 10 numbes\n");
    for(int i=0;i<10;i++){
        printf("enter the number of %d",i+1);
        scanf("%d",&var.arr[i]);

    }
    result=oddeven_1(&var,clnt);
    printf("the no. of even numbers is %d",*result);
    printf("the no. of even numbers is %d",10-*result);
    clnt_destroy(clnt);


    return 1;

    
    
}