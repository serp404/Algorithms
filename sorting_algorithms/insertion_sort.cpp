#include <iostream>
#include <vector>

template<typename T>
void insertion_sort(std::vector<T>& array, bool ascending=true) {
    if (!array.empty()) {
        for (size_t i = 1; i != array.size(); ++i) {
            auto temp = array[i];
            int j = i - 1;
            if (ascending) {
                while (j >= 0 && array[j] > temp) {
                    array[j + 1] = array[j];
                    --j;
                }
                array[j + 1] = temp;
            } else {
                while (j >= 0 && array[j] < temp) {
                    array[j + 1] = array[j];
                    --j;
                }
                array[j + 1] = temp;
            }
        }
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
    insertion_sort(a1);
    std::cout << a1 << "\n";

    std::vector<double> a2 = {6.5, 4.1, 2.71, 3.14, 10};
    insertion_sort(a2, false);
    std::cout << a2 << "\n";
}

// Output:
//{ 1, 2, 4, 5, 7, 8 }
//{ 10, 6.5, 4.1, 3.14, 2.71 }
