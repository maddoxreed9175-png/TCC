#include <iostream>
 
int main() {
    int n = 8;
    long long total = 1;
    for (int i = 2; i <= n; i++) {
        total *= i;
    }
    long long count = 0;
    for (long long i = 0; i < total; i++) {
        count++;
    }
    std::cout << count << std::endl;
    return 0;
}