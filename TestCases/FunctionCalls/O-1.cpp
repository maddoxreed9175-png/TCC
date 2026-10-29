#include <vector>
#include <iostream>

int constantTime(std::vector<int>& arr) {
    return arr[0];
}

int main() {
    std::vector<int> arr = {
    2, 8, 9, 12, 13, 15, 17, 21, 22, 26,
    28, 31, 34, 37, 38, 39, 43, 45, 47, 49,
    54, 56, 58, 59, 61, 63, 66, 67, 68, 71,
    74, 76, 80, 82, 84, 88, 91, 93, 95, 97
    };
    constantTime(arr);
    std::cout << "ran";
}