#include <vector>
#include <iostream>

void cubicTime(std::vector<int>& A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
            }
        }
    }
}

int main() {
    std::vector<int> arr = {
    2, 8, 9, 12, 13, 15, 17, 21, 22, 26,
    28, 31, 34, 37, 38, 39, 43, 45, 47, 49,
    54, 56, 58, 59, 61, 63, 66, 67, 68, 71,
    74, 76, 80, 82, 84, 88, 91, 93, 95, 97
    };
    cubicTime(arr, arr.size()-1);
    std::cout << "ran";
}