#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
size_t partition(std::vector<T>& array, size_t l, size_t r) {
    size_t k = (l + r) / 2;
    T comp = array[k];
    size_t i = l, j = r;
    while (i <= j) {
        while (array[i] < comp)
            ++i;
        while (array[j] > comp)
            --j;
        if (i >= j)
            break;
        if (array[i] != array[j]) {
            std::swap(array[i], array[j]);
        } else {
            i += 1;
            j -= 1;
        }
    }
    return j;
}

template<typename T>
void partial_sort(std::vector<T>& array, size_t down, size_t up) {
    if (up > down) {
        size_t m = partition(array, down, up);
        partial_sort(array, down, m);
        partial_sort(array, m + 1, up);
    }
}

template<typename T>
void quick_sort(std::vector<T>& array, bool ascending=true) {
    partial_sort(array, 0, array.size() - 1);

    if (!ascending)
        std::reverse(array.begin(), array.end());
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
    quick_sort(a1);
    std::cout << a1 << "\n";

    std::vector<double> a2 = {6.5, 4.1, 2.71, 3.14, 10};
    quick_sort(a2, false);
    std::cout << a2 << "\n";
}

// Output:
//{ 1, 2, 4, 5, 7, 8 }
//{ 10, 6.5, 4.1, 3.14, 2.71 }
