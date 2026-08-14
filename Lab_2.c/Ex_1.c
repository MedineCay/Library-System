
//Break and Continue statements:                                  The break statement is a loop control statement which is used to terminate the loop immediately.The program exists the loop, and code blocks after the loop are executed.

#include<stdio.h>
int main(){
    for(int i =1 ;i<=5 ; i++){
        if(i==4){
            break;
        }
        printf("%d" ,i );
    }
    return 0;
}