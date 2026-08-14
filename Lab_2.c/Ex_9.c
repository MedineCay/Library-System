
//MIDTERM 2024:What is the program's output
#include<stdio.h>
#include<stdbool.h>

bool func(int n){
    if(n%2==0){
        return false;
    }else{
        return true;
    }
}
int main(){
    bool a = true, b= false;
    for(int i =0 ; i<2 ; i++){
        if(a&& func(i)){
            printf("Midterm");
        }
        if((a||b) && func(i)){
            printf("Exam");
            continue;
        }
        printf("%d",i);
        printf("%d",func(i));
        
        
    }
    return 0;
}
