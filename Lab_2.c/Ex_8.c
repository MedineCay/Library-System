
//Write a C program that calculates the average of only positive number in an array of integers whose number of elements is taken from the user.

#include<stdio.h>
int main(){
    int size;
    int sum = 0 ;
    int count = 0;
    double average;

    printf("Please enter the size of the array : \n");
    scanf("%d",&size);
    int numbers[size];

    for (int i=0; i<size ;i++){
        printf("Enter the %d. element : ", i+1);
        scanf("%d",&numbers[i]);
        if(numbers[i]<=0){
            continue;
        }
        sum+=numbers[i];
        count++;
    }
    average = (double)sum/count;
    printf("Sum of positives : %d , Count of positives : %d ,average of positives : %f",sum,count,average);
    return 0 ;
}