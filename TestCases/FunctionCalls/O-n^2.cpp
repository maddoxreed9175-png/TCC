#include <vector>
#include <iostream>

void quadraticTime(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
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
    quadraticTime(arr);
    std::cout << "ran";
}