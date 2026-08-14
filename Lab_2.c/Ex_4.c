
//The continue statement breaks one iteration(in the loop), if a specified condition occurs, and continues with the next iteration in the loop.
#include<stdio.h>
int main(){
    for(int i=1 ; i<=5 ; i++){
        if(i==4){
            continue;
        }
        printf("%d", i);
    }
}