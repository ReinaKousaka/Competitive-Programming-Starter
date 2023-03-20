#include <vector>
#include <algorithm>


// Discretize array, starting from 0, modifying the input array
template<typename T>
void Discretization(std::vector<T>& arr) {
    std::vector<T> t = arr;
    std::sort(t.begin(), t.end());
    t.erase(std::unique(t.begin(), t.end()), t.end());
    for (int i = 0; i < arr.size(); i++)
        arr[i] = std::lower_bound(t.begin(), t.end(), arr[i]) - t.begin();
}
