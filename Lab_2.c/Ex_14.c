
//MIDTERM 2024:What is the program's output

#include<stdio.h>
void nestedloop(int a, int b){
    for(int i=1 ; i<a ;i++){
        for(int j=0 ; j<b ;j++){
            if(i+j>=3){
                break;
            }
            printf("%d-%d ",i,j);
        }
    }
}
int main(){
    nestedloop(4,3);
    return 0 ;
}