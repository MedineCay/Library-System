
//Program to calculate the sum of number , if the user enters a negative number , the loop terminates

#include<stdio.h>
int main(){
    int number;
    int sum =0;
    for(int i =1; i<=10; i++){
        printf("%d. sayiyi giriniz: ", i);
        scanf("%d",&number);
        if(number<0){
            break;
        }
        sum+= number;
    }
    printf("Sum : %d",sum);
    return 0;
}