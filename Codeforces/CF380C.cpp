#include <bits/stdc++.h>
using namespace std;

typedef pair<pair<int, int>, int> piii;

// Segment Tree Template
struct Node {
    int start, end, value;
    Node *left, *right;

    // # open closed brackets
    int open = 0, close = 0;

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


struct SegmentTree {
    Node* root;

    SegmentTree(string& data) {
        root = _build_tree(data, 1, data.size());
    }

    Node* _build_tree(string& data, int ql, int qr) {
        if (ql == qr) {
            Node* p = new Node(ql, qr, 0);
            if (data[ql - 1] == '(')
                p->open = 1;
            else
                p->close = 1;
            return p;
        }

        int mid = (ql + qr) >> 1;
        Node* left = _build_tree(data, ql, mid);
        Node* right = _build_tree(data, mid + 1, qr);

        Node* p = new Node(ql, qr, 0, left, right);
        int t = min(left->open, right->close);
        p->value = left->value + right->value + 2 * t;
        p->open = left->open + right->open - t;
        p->close = left->close + right->close - t;
        return p;
    }

    piii query_range(int ql, int qr, Node*node=nullptr) {
        if (!node) { node = root; }
        if (node->end < node->start || node->start > qr || node->end < ql) {
            return {{0, 0}, 0};
        }

        if (ql <= node->start && node->end <= qr) {
            return {{node->open, node->close}, node->value};
        }

        auto left = query_range(ql, qr, node->get_left());
        auto right = query_range(ql, qr, node->get_right());
        int t = min(left.first.first, right.first.second);
        return {{
                left.first.first + right.first.first - t, 
                left.first.second + right.first.second - t},
                left.second + right.second + 2 * t};
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    SegmentTree st(s);

    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << st.query_range(l, r).second << "\n";
    }
    return 0;
}
