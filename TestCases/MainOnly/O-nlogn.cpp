#include <iostream>
 
int main() {
    int n = 16;
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j *= 2) {
            count++;
        }
    }
    std::cout << count << std::endl;
    return 0;
}