#include <iostream>
 
int main() {
    int n = 20;
    long long total = 1LL << n;
    long long count = 0;
    for (long long i = 0; i < total; i++) {
        count++;
    }
    std::cout << count << std::endl;
    return 0;
}