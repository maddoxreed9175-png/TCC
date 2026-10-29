#include <iostream>
 
int main() {
    int n = 16;
    int count = 0;
    for (int j = 1; j < n; j *= 2) {
        count++;
    }
    std::cout << count << std::endl;
    return 0;
}