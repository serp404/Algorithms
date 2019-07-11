#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void cocktail_sort(std::vector<T>& array, bool ascending=true) {
    if (!array.empty()) {
        size_t left = 0;
        size_t right = array.size() - 1;

        while (left <= right) {
            for (size_t i = left; i < right; ++i) {
                if (array[i] > array[i + 1])
                    std::swap(array[i], array[i + 1]);
            }
            --right;

            for (size_t i = right; i > left; --i) {
                if (array[i - 1] > array[i])
                    std::swap(array[i], array[i - 1]);
            }
            ++left;
        }
        if (!ascending)
            std::reverse(array.begin(), array.end());
    }
}

template<typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& array) {
    out << "{";
    for (size_t i = 0; i != array.size(); ++i) {
        if (i != array.size() - 1)
            out << " " << array[i] << ",";
        else
            out << " " << array[i] << " ";
    }
    out << "}";
    return out;
}

int main() {
    std::vector<size_t> a1 = {5, 1, 7, 8, 2, 4};
    cocktail_sort(a1);
    std::cout << a1 << "\n";

    std::vector<double> a2 = {6.5, 4.1, 2.71, 3.14, 10};
    cocktail_sort(a2, false);
    std::cout << a2 << "\n";
}

// Output:
//{ 1, 2, 4, 5, 7, 8 }
//{ 10, 6.5, 4.1, 3.14, 2.71 }
