//Write a program that determşnes whether an imteger taken from the user is a prime number

#include<stdio.h>
#include<stdbool.h>

int main(){
    int number;
    bool result = true ; //Suppose the number entered is initially a prime number

    printf("Please enter a number : \n");
    scanf("%d",&number);

    if(number==0 || number==1){
        result =false;
    }
    for(int i=2 ; i<number ; i++){
        if(number % i == 0){
            result=false;
            break;
        }
    }
    if (result==true){
        printf("%d is a prime number. ",number);
    }else{
        printf("%d is not a prime number.", number);
    }
    return 0;
}