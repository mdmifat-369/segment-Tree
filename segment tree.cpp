#include<bits/stdc++.h>
#define int long long int
using namespace std;

const int maxN = 1e5 + 9;
int a[maxN], t[4 * maxN];


void build(int node, int b, int e) {
    if(b == e) {
        t[node] = a[b];
        return;
    }
    int mid = (b + e) / 2;
    build(2*node, b, mid);
    build(2*node+1, mid+1, e);
    t[node] = t[2*node] + t[2*node+1];
}

void update(int node, int b, int e, int i, int v) {
    if(b == e) {
        t[node] = v;
        return;
    }
    int mid = (b + e) / 2;
    if(i <= mid)
        update(2*node, b, mid, i, v);
    else
        update(2*node+1, mid+1, e, i, v);
        
    t[node] = t[2*node] + t[2*node+1];
}


int query(int node, int b, int e, int i, int j) {
    if(j < b || i > e) return 0;       
    if(b >= i && e <= j) return t[node]; 
    int mid = (b + e) / 2;
    return query(2*node, b, mid, i, j) + query(2*node+1, mid+1, e, i, j);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);

    while(q--) {
        int type;
        cin >> type;
        if(type == 2) {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l + 1, r) <<endl;
        } else {
            int i, v;
            cin >> i >> v;
            update(1, 1, n, i + 1, v);
        }
    }

    return 0;
}
