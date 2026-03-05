#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;

long long tree[N];
long long lazy[N];
int n;

// Build function (initially all zeros)
void build(int node, int start, int end) {
    lazy[node] = 0;

    if(start == end) {
        tree[node] = 0;
        return;
    }

    int mid = (start + end) / 2;
    build(2*node, start, mid);
    build(2*node+1, mid+1, end);

    tree[node] = tree[2*node] + tree[2*node+1];
}

// Push pending lazy addition
void push(int node, int start, int end) {
    if(lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];

        if(start != end) {
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }

        lazy[node] = 0;
    }
}

// Range addition
void rangeAdd(int node, int start, int end, int l, int r, long long val) {
    push(node, start, end);

    if(r < start || end < l) return;

    if(l <= start && end <= r) {
        lazy[node] += val;
        push(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    rangeAdd(2*node, start, mid, l, r, val);
    rangeAdd(2*node+1, mid+1, end, l, r, val);

    tree[node] = tree[2*node] + tree[2*node+1];
}


// Range sum query
long long rangeSum(int node, int start, int end, int l, int r) {
    push(node, start, end);

    if(r < start || end < l) return 0;

    if(l <= start && end <= r) return tree[node];

    int mid = (start + end) / 2;
    return rangeSum(2*node, start, mid, l, r) +
           rangeSum(2*node+1, mid+1, end, l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> n >> m;

    build(1, 0, n-1);

    while(m--) {
        int type;
        cin >> type;

        if(type == 1) {
            int l, r;
            long long v;
            cin >> l >> r >> v;
            rangeAdd(1, 0, n-1, l, r-1, v); // r is exclusive
        }
        else if(type == 2) {
            int i;
            cin >> i;
            cout << rangeSum(1, 0, n-1, i) << "\n";
        }
    }
}
