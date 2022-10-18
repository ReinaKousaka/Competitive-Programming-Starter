#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int nextGreaterElement(int n) {
        const int max_int = 2147483647;
        vector<int> digits;
        while (n) {
            digits.push_back(n % 10);
            n = n / 10;
        }
        for (int i = 1; i < digits.size(); i++) {
            if (digits[i] < digits[i - 1]) {
                for (int j = 0; j < i; j++) {
                    if (digits[j] > digits[i]) {
                        std::swap(digits[i], digits[j]);
                        break;
                    }
                }
                std::reverse(digits.begin(), std::next(digits.begin(), i));
                long long res = 0;
                for (int j = digits.size() - 1; j >= 0; j--) {
                    res = res * 10 + digits[j];
                }
                return (res > max_int) ? -1 : res;
            }
        }
        return -1;
    }
};