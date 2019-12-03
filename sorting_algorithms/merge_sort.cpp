#include <iostream>
#include <vector>
#include <algorithm>

template<typename  T>
std::vector<T> merge(const std::vector<T>& a1, const std::vector<T>& a2) {
    size_t n1 = a1.size();
    size_t n2 = a2.size();
    size_t total = n1 + n2;
    size_t i1 = 0, i2 = 0;
    std::vector<T> ans;
    ans.reserve(total);
    while (total != 0) {
        if (i1 == n1) {
            for (size_t i = i2; i != n2; ++i)
                ans.push_back(a2[i]);
            return ans;
        } else if (i2 == n2) {
            for (size_t i = i1; i != n1; ++i)
                ans.push_back(a1[i]);
            return ans;
        } else if (a1[i1] <= a2[i2]) {
            ans.push_back(a1[i1]);
            ++i1;
        } else {
            ans.push_back(a2[i2]);
            ++i2;
        }
        --total;
    }
    return ans;
}

template<typename T>
std::vector<T> recursive_merge_sort(const std::vector<T>& array) {
    if (array.size() < 2) {
        return array;
    } else {
        size_t centre = array.size() / 2;
        std::vector<T> a1(array.begin(), array.begin() + centre);
        std::vector<T> a2(array.begin() + centre, array.end());

        return merge(recursive_merge_sort(a1), recursive_merge_sort(a2));
    }
}

template<typename T>
void merge_sort(std::vector<T>& array, bool ascending=true) {
    array = recursive_merge_sort(array);
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
    merge_sort(a1);
    std::cout << a1 << "\n";

    std::vector<double> a2 = {6.5, 4.1, 2.71, 3.14, 10};
    merge_sort(a2, false);
    std::cout << a2 << "\n";
}

// Output:
//{ 1, 2, 4, 5, 7, 8 }
//{ 10, 6.5, 4.1, 3.14, 2.71 }
