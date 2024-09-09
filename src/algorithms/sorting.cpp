#include <cstdio>
#include <iostream>
#include <iterator>
#include <vector>


void print(const std::vector<int>& v) {
    for (auto i : v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}



std::vector<int> insertion_sort_base(std::vector<int> v) {
    for (int i = 1uz; i < int(v.size()); ++i) {
        int k = v[i];
        int j = i - 1;
        while (j >= 0) {
            if (v[j] > k) {
                v[j+1] = v[j];
                --j;
            } else {
                break;
            }
        }
        v[j+1] = k;
    }

    return v;
}


std::vector<int> insertion_sort(std::vector<int> v) {
    if (v.empty()) {
        return v;
    }

    for (auto i = std::next(v.begin()); i != v.end(); i = std::next(i)) {
        int k = *i;
        auto j = std::make_reverse_iterator(i);
        while (j != v.rend() && *j > k) {
            *std::prev(j) = *j;
            j = std::next(j);
        }
        *std::prev(j) = k;
    }
    return v;
}




int main() {
    std::vector<int> v1 = {5,2,4,6,1,3};
    print(v1);
    
    auto v2 = insertion_sort(v1);
    print(v2);

    auto v3 = insertion_sort_base(v1);
    print(v3);
    
    return 0;
}