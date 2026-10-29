#include <vector>
#include <iostream>
#include <algorithm>

void linearithmicTime(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    linearithmicTime(arr, left, mid);
    linearithmicTime(arr, mid + 1, right);
    std::inplace_merge(arr.begin() + left, arr.begin() + mid + 1, arr.begin() + right + 1);
}

int main() {
    std::vector<int> arr = {
    2, 8, 9, 12, 13, 15, 17, 21, 22, 26,
    28, 31, 34, 37, 38, 39, 43, 45, 47, 49,
    54, 56, 58, 59, 61, 63, 66, 67, 68, 71,
    74, 76, 80, 82, 84, 88, 91, 93, 95, 97
    };
    linearithmicTime(arr, 0, arr.size() - 1);
    std::cout << "ran";
}