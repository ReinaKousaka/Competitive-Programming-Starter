#include <string>
#include <vector>
using namespace std;


int KMP(const string& s, const string& p) {
    if (s.size() < p.size()) return -1;

    // next[i] := the max length of suffix starting at i backwards in p which matches some prefix of p
    vector<int> next = {0};
    int i = 1, now = 0;
    while (i < p.size()) {
        if (p[now] == p[i]) { // expands right
            now++;
            i++;
            next.push_back(now);
        } else if (now) {       // shrink
            now = next[now - 1];
        } else {
            next.push_back(0);
            i++;
        }
    }

    // search
    i = 0;
    int j = 0;
    while (j < s.size()) {
        if (s[j] == p[i]) {
            i++; 
            j++;
        } else if (i) {     // not a match, move according to next
            i = next[i - 1];
        } else {        // can not match p[0]
            j++;
        }
        if (i == p.size()) {
            return j - i;
            // to return all match indices, add:
            // i = next[i - 1];
        }
    }
    return -1;
}

class Solution {
public:
    int strStr(string haystack, string needle) {
        return KMP(haystack, needle);
    }
};
