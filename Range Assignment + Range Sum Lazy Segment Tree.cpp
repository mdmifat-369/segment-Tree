#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;

long long tree[N];
long long lazyAssign[N];
bool assignFlag[N];
int n;

// Build function (initially all zeros)
void build(int node, int start, int end) {
    lazyAssign[node] = 0;
    assignFlag[node] = false;

    if(start == end) {
        tree[node] = 0;
        return;
    }

    int mid = (start + end) / 2;
    build(2*node, start, mid);
    build(2*node+1, mid+1, end);

    tree[node] = tree[2*node] + tree[2*node+1];
}

// Push pending assignment
void push(int node, int start, int end) {
    if(assignFlag[node]) {
        tree[node] = (end - start + 1) * lazyAssign[node];

        if(start != end) {
            lazyAssign[2*node] = lazyAssign[node];
            lazyAssign[2*node+1] = lazyAssign[node];
            assignFlag[2*node] = assignFlag[2*node+1] = true;
        }

        lazyAssign[node] = 0;
        assignFlag[node] = false;
    }
}

// Range assignment
void rangeAssign(int node, int start, int end, int l, int r, long long val) {
    push(node, start, end);

    if(r < start || end < l) return;

    if(l <= start && end <= r) {
        lazyAssign[node] = val;
        assignFlag[node] = true;
        push(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    rangeAssign(2*node, start, mid, l, r, val);
    rangeAssign(2*node+1, mid+1, end, l, r, val);

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
            long long val;
            cin >> l >> r >> val;
            rangeAssign(1, 0, n-1, l, r-1, val); // r is exclusive
        }
        else if(type == 2) {
            int l, r;
            cin >> l >> r;
            cout << rangeSum(1, 0, n-1, l, r-1) << "\n"; // r exclusive
        }
    }
}