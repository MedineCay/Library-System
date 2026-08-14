
//Write a program that asks the user to enter a TL amount and then shows how to pay that amount using smallest number of 20tl,10tl,5tl and 1tl bills.
//Hint:Divide the amount by 20 to determine the number of 20 tl bills needed , and then reduce the amount by the total value of the 20 tl bills. Repeat for other bill sizes.

//Input format : Single integer ,n
//Contraints: The number n must be greater than or equal to 20.
//Output format: If n<20 , print "n must be greater than or equal to 20 ". Otherwise, print how many times each banknote is used.
//Sample input :93
//Sample output: 20 tl bills : 4        10 tl bills:1        5 tl bills:0       1 tl bills:3

#include <stdio.h>
int main(){
    int amount;
    printf("Enter a TL amount : ");
    scanf("%d" , &amount);

    if(amount<20){
        printf("n must be greater than or equal to 20 \n");
    }else {
        //Calculate the number of 20 tl bills
        int bills20 = amount/20 ;
        amount -= bills20*20;

        //Calculate the number of 10 TL bills
        int bills10 = amount / 10 ;
        amount -= bills10*10;

        //Calculate the number of 5 TL bills
        int bills5 = amount / 5;
        amount -= bills5 * 5;

        //The remaining amount will be in 1 TL bills
        int bills1 = amount ;

        //Output the results
        printf("20 tl bills : %d\n", bills20);
        printf("10 tl bills : %d\n", bills10);
        printf("5 tl bills : %d\n" , bills5);
        printf("1 tl bills : %d\n ", bills1);

    }
}