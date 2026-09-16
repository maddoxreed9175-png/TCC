#include <vector>
#include <iostream>

int exponentialTime(int n){
    if(n <= 1) return n;
    return exponentialTime(n-1) + exponentialTime(n-2);
}

int main(){
    int n = 10;
    exponentialTime(n);
    std::cout << "ran";
}