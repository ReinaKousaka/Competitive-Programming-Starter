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
        root = new Node(0, MAX);
    }

    void update(int ql, int qr, int delta, Node* node=nullptr) {
        if (!node) { node = root; }
        if (node->lazy != 0) {
            node->value += node->lazy;
            if (node->start != node->end) {
                // push down for non-leaf
                node->get_left()->lazy += node->lazy;
                node->get_right()->lazy += node->lazy;
            }
            node->lazy = 0;
        }
        if (node->end < node->start || node->start > qr || node->end < ql) {
            return;
        }

        if (ql <= node->start && node->end <= qr) {
            node->value += delta;
            if (node->start != node->end) {
                node->get_left()->lazy += delta;
                node->get_right()->lazy += delta;
            }
            return;
        }

        update(ql, qr, delta, node->get_left());
        update(ql, qr, delta, node->get_right());
        node->value = max(node->left->value, node->right->value);
    }

    int query(int ql, int qr, Node*node=nullptr) {
        if (!node) { node = root; }
        if (node->end < node->start || node->start > qr || node->end < ql) {
            return 0;
        }
        if (node->lazy != 0) {
            node->value += node->lazy;
            if (node->start != node->end) {
                // push down for non-leaf
                node->get_left()->lazy += node->lazy;
                node->get_right()->lazy += node->lazy;
            }
            node->lazy = 0;
        }

        if (ql <= node->start && node->end <= qr) {
            return node->value;
        }

        return max(
            query(ql, qr, node->get_left()),
            query(ql, qr, node->get_right())
        );
    }
};

class MyCalendarThree {
public:
    SegmentTree st;
    MyCalendarThree() {
        
    }
    
    int book(int startTime, int endTime) {
        st.update(startTime, endTime - 1, 1);
        return st.query(0, 1e9);
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */
