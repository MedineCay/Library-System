
//Program to calculate the sum of numbers, if the user enters a negative number, its not added to the result

#include<stdio.h>
int main(){
    int sum=0;
    int number ;

    for(int i =1 ; i<=5 ; i++){
        printf("%d. Enter a number : ", i);
        scanf("%d", &number);
        if(number<0){
            continue;
        }
        sum+=number;
    }
    printf("Sum : %d",sum);
}