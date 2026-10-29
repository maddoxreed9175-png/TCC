#include <vector>
#include <iostream>

int logarithmicTime(std::vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main() {
    std::vector<int> arr = {
    2, 8, 9, 12, 13, 15, 17, 21, 22, 26,
    28, 31, 34, 37, 38, 39, 43, 45, 47, 49,
    54, 56, 58, 59, 61, 63, 66, 67, 68, 71,
    74, 76, 80, 82, 84, 88, 91, 93, 95, 97
    };
    logarithmicTime(arr, 56);
    std::cout << "ran";
}