#include<bits/stdc++.h>
#define mod 1000000007
#define int long long int
using namespace std;
const int N =1e5+10;
vector<int>a(N);

vector<int>merge(auto l,auto r){
     vector<int>a;
     int i=0,j=0;
     while(i<l.size() && j<r.size()){
         if(l[i]<r[j]){
            a.push_back(l[i]);
            i++;
         }else{
            a.push_back(r[j]);
            j++;
         }
     }

     while(i<l.size()){
         a.push_back(l[i]);
         i++;
     }
     while(j<r.size()){
        a.push_back(r[j]);
        j++;
     }
     
     return a;
}

vector<int>merge_sort(int l,int r){
     if(l==r){
        return vector<int>({a[l]});
     }
     int mid=(l+r)/2;

     auto L=merge_sort(l,mid);
     auto R=merge_sort(mid+1,r);

     return merge(L,R);
}

void solve(){
     int n;
     cin>>n;
     for(int i=0;i<n;i++)cin>>a[i];

     auto ans=merge_sort(0,n-1);
     for(int it:ans){
        cout<< it <<" ";
     }
     cout<<endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    
    return 0;
}