
//MIDTERM 2024:What is the program's output

#include<stdio.h>
void func(int arr[] , int n){
    for(int i =0 ; i<n-1 ; i++){
        for(int j =i+1 ; j<n ;j++){
            if(arr[i]<arr[j]){
                printf("%d%d",arr[i],arr[j]);
                break;
            }
        }
        
    }
}
int main(){
    int numbers[5]={6,3,7,5,7};
    func(numbers,5);
    return 0;
}