
//Write a progarm that reads three integer parameters( side lenghs of the triangle) from the user . And check whether triangle the triangle is valid or not. Finally, parameters must be greater than zero. Otherwise,the program must print a warning message.

#include<stdio.h>
int main(){
    int a,b,c ;
    printf("Enter the side lengths ");
    scanf("%d%d%d", &a,&b,&c);
    if(a<=0 || b<=0 || c<=0){
        printf("Side lengths must be a positive number ");
    }else{
        if(a+b>c && a+c>b && b+c>a){
            printf("Valid triangle ");
        }else{
            printf("Invalid triangle ");
        }
    }
}