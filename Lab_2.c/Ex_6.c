#include<stdio.h>
int main(){
    int sum=0;
    for(int i ; i<=6 ; i++){
        if(i%2==0){
            continue;
        }
        sum+=i;
    }
    printf("%d",sum);
    return 0;
}