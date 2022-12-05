#include <algorithm>
using namespace std;

// Lazy Dynamic Segment Tree Template
class Node {
public:
    int start, end, value, lazy;
    Node *left, *right;

    Node (int start, int end)
    :start(start), end(end), value(0), lazy(0), left(nullptr), right(nullptr) {}

    int size() {
        return end - start + 1;
    }

    int mid(){
        return (start + end) >> 1;
    }

    Node* get_left() {
        if (!left) { left = new Node(start, mid()); }
        return left;
    }

    Node* get_right() {
        if (!right) { right = new Node(mid() + 1, end); }
        return right;
    }
};

class SegmentTree {
public:
    const int MAX = 1e9 + 1;
    Node* root;

    SegmentTree() {
        root = new Node(1, MAX);
    }

    // ql, qr: query left, right
    // change *to* new_val
    void change_range_query(int ql, int qr, int new_val, Node* node=nullptr) {
        if (!node) { node = root; }
        // pushdown
        if (node->lazy != 0) {
            // adjusted to sum, max, ..
            node->value = node->lazy * node->size();
            if (node->start != node->end) {
                // push down for non-leaf
                node->get_left()->lazy = node->lazy;
                node->get_right()->lazy = node->lazy;
            }
            node->lazy = 0;
        }
        if (node->end < node->start || node->start > qr || node->end < ql) {
            return;
        }

        if (ql <= node->start && node->end <= qr) {
            node->value = new_val * node->size();
            if (node->start != node->end) {
                node->get_left()->lazy = new_val;
                node->get_right()->lazy = new_val;
            }
            return;
        }

        change_range_query(ql, qr, new_val, node->get_left());
        change_range_query(ql, qr, new_val, node->get_right());
        node->value = node->left->value + node->right->value;
    }
};

class CountIntervals {
public:
    SegmentTree st;

    CountIntervals() {}
    
    void add(int left, int right) {
        st.change_range_query(left, right, 1);
    }
    
    int count() {
        return st.root->value;
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */
