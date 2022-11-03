#include <vector>
using namespace std;

// Dynamic Segment Tree Template
class Node {
 public:
    int start, end, value;
    Node *left, *right;

    Node (int start, int end)
    :start(start), end(end), value(0), left(nullptr), right(nullptr) {}

    Node (int start, int end, int value)
    :start(start), end(end), value(value), left(nullptr), right(nullptr) {}

    Node (int start, int end, int value, Node* left, Node* right)
    :start(start), end(end), value(value), left(left), right(right) {}

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
    const int MAX = 3e4 + 1;
    Node* root;

    SegmentTree(vector<int>& data) {
        root = _build_tree(data, 0, data.size() - 1);
    }

    Node* _build_tree(vector<int>& data, int ql, int qr) {
        if (ql == qr) {
            return new Node(ql, qr, data[ql]);
        }

        int mid = (ql + qr) >> 1;
        Node* left = _build_tree(data, ql, mid);
        Node* right = _build_tree(data, mid + 1, qr);
        return new Node(ql, qr, left->value + right->value, left, right);
    }

    void update_single(int index, int new_val, Node* node=nullptr) {
        if (!node) { node = root; }
        if (node->end < node->start || node->start > index || node->end < index) {
            return;
        }

        if (index == node->start && node->end == index) {
            node->value = new_val;
            return;
        }

        update_single(index, new_val, node->get_left());
        update_single(index, new_val, node->get_right());
        node->value = node->left->value + node->right->value;
    }

    int query_range(int ql, int qr, Node*node=nullptr) {
        if (!node) { node = root; }
        if (node->end < node->start || node->start > qr || node->end < ql) {
            return 0;
        }

        if (ql <= node->start && node->end <= qr) {
            return node->value;
        }

        return query_range(ql, qr, node->get_left()) 
            + query_range(ql, qr, node->get_right());
    }
};


class NumArray {
public:
    SegmentTree st;
    
    NumArray(vector<int>& nums)
    :st(nums) {}

    void update(int index, int val) {
        st.update_single(index, val);
    }
    
    int sumRange(int left, int right) {
        return st.query_range(left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */