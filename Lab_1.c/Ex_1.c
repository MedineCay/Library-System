#include <stdio.h>
#include<stdbool.h>

int main() {
    int myNum = 5 ;
    float myFloatNum= 5.99;
    char myLetter ='D';
    bool myBool = true ;
    
    printf ("%d\n" , myNum);
    printf("%f\n", myFloatNum);
    printf("%c\n" , myLetter);
    //printf ("%s\n", myBool);  =>Incorrect :bool values cannot be printed as a strings directly
    printf("%d\n" , myBool);  //Correct: Prints the bool values as an integer(1 for true , 0 for false)
    

    return 0;
}

