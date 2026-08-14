//Suppose that we have two different objects or points in a cartesian coordinate system in two dimensions. And we want to measure the distance between these two points. We can use a number of different metrics to measure the distance. But in this question , you will use "Manhattan Distance".

//One of the points is x=(a,b), and other point is y =(c,d).Manhattan distance between x and y points is :                Distance = |a-c| + |b-d|                                          For example;                                                        x=(-1,7)                                                            y =(4,3)                                                       Distance = |-1-4| + |7-3| = 5+4 = 9 

//Task:Take 4 integer value from user (a,b,c,d). Write a program that asks the user to enter 4 integer value. And prints the result after calculating the manhattan distance.

//SOLUTIN2:
#include<stdio.h>
#include<stdlib.h> // For abs() function
int main(){
    int a, b, c, d ;
    printf("Enter the coordinates of the first point (a,b) : ");
    scanf("%d %d" , &a,&b);
    printf("Enter the coordinates of the second point (c,d) : ");
    scanf("%d %d" , &c,&d );

    //Calculate the manhattan distance

    int distance = abs(a-c) + abs(b-d);

    //Print the result
    printf("Manhattan distance : %d\n ", distance);

    return 0 ;

}