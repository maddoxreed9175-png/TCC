#include <vector>
#include <iostream>

void factorialTime(std::string str, int l, int r) {
    for (int i = l; i <= r; i++) {
        std::swap(str[l], str[i]);
        factorialTime(str, l + 1, r);
        std::swap(str[l], str[i]);
    }
}

int main(){
    std::string n = "abcdefghijklmnopqrstuvwxyz";
    factorialTime(n, 0, n.size() - 1);
    std::cout << "ran";
}