#include<bits/stdc++.h>
#define int long long
using namespace std;

vector<vector<int>> st;
vector<int> log_table;
int N, K;

int merge_op(int a, int b) {
    return min(a, b);    
}

void build_sparse_table(const vector<int>& arr) {
    N = arr.size();
    if (N == 0) return;

    K = floor(log2(N));
    st.assign(N, vector<int>(K + 1));

    for (int i = 0; i < N; ++i) {
        st[i][0] = arr[i];
    }

    for (int j = 1; j <= K; ++j) {
        for (int i = 0; i + (1 << j) <= N; ++i) {
            st[i][j] = merge_op(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }

    log_table.assign(N + 1, 0);
    for (int i = 2; i <= N; ++i) {
        log_table[i] = log_table[i / 2] + 1;
    }
}

int query_rmq(int L, int R) {
    if (L < 0 || R >= N || L > R) {
        return LLONG_MAX;  
    }

    int len = R - L + 1;
    int p = log_table[len];

    int v1 = st[L][p];
    int v2 = st[R - (1 << p) + 1][p];

    return merge_op(v1, v2);
}

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    build_sparse_table(arr);

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        //l--, r--;
        cout << query_rmq(l, r) << "\n";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}
