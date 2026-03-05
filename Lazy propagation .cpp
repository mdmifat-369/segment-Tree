#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
long long tree[4*N], lazy[4*N];
bool assignFlag[4*N]; 
int n;

void build(vector<int>& a, int node, int start, int end) {
    if(start == end) {
        tree[node] = a[start];
    } else {
        int mid = (start + end) / 2;
        build(a, 2*node, start, mid);
        build(a, 2*node+1, mid+1, end);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

void push(int node, int start, int end) {
    if(assignFlag[node]) {
        tree[node] = (end - start + 1) * lazy[node];
        if(start != end) {
            lazy[2*node] = lazy[node];
            lazy[2*node+1] = lazy[node];
            assignFlag[2*node] = assignFlag[2*node+1] = true;
        }
        assignFlag[node] = false;
    }
}


void update(int node, int start, int end, int l, int r, long long val) {
    push(node, start, end);
    if(r < start || end < l) return;
    if(l <= start && end <= r) {
        lazy[node] = val;
        assignFlag[node] = true;
        push(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    update(2*node, start, mid, l, r, val);
    update(2*node+1, mid+1, end, l, r, val);
    tree[node] = tree[2*node] + tree[2*node+1];
}

long long query(int node, int start, int end, int l, int r) {
    push(node, start, end);
    if(r < start || end < l) return 0;
    if(l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    return query(2*node, start, mid, l, r) + query(2*node+1, mid+1, end, l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    build(a, 1, 0, n-1);

    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int i, x;
            cin >> i >> x;
            i--; 
            update(1, 0, n-1, i, i, x);
        } else if(type == 2) {
            int x;
            cin >> x;
            update(1, 0, n-1, 0, n-1, x);
        }
        cout << query(1, 0, n-1, 0, n-1) << "\n";
    }
}