#include <iostream>
 
int main() {
    int n = 10;
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                count++;
            }
        }
    }
    std::cout << count << std::endl;
    return 0;
}