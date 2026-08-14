
//Suppose that we have two different objects or points in a cartesian coordinate system in two dimensions. And we want to measure the distance between these two points. We can use a number of different metrics to measure the distance. But in this question , you will use "Manhattan Distance".

//One of the points is x=(a,b), and other point is y =(c,d).Manhattan distance between x and y points is :                Distance = |a-c| + |b-d|                                          For example;                                                        x=(-1,7)                                                            y =(4,3)                                                       Distance = |-1-4| + |7-3| = 5+4 = 9 

//Task:Take 4 integer value from user (a,b,c,d). Write a program that asks the user to enter 4 integer value. And prints the result after calculating the manhattan distance.

//SOLUTIN1:
#include<stdio.h>
int main(){
    int a, b, c, d ;
    printf("Enter the coordinates of the first point (a,b) : ");
    scanf("%d %d " , &a, &b);
    printf("Enter the coordinates of the second point (c,d) : ");
    scanf("%d %d " , &c ,&d );

    //Manually calculate. the absolute values for the differences
    int diff1 = a-c;
    if(diff1<0){
        diff1=-diff1;   //Make it positive
    }
    int diff2 =b-d ;
    if(diff2<0){
        diff2= - diff2;    //Make it positive
    }

    //Calculate the manhattan distance

    int distance = diff1 + diff2 ;
    printf("Manhattan Distance : %d \n ", distance);

    return 0;
}
