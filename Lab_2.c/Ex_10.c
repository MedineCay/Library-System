
//Nested Loops:Outer loop and Inner loop can be a for loop,while loop or do-while loop

#include<stdio.h>
int main(){
    int i, j;
    for(i=0 ; i<3 ;i++ ){
        for(j=0 ; j<3 ;j++){
            printf("i= %d - j = %d \n",i,j);
        }
    }
    return 0;
}