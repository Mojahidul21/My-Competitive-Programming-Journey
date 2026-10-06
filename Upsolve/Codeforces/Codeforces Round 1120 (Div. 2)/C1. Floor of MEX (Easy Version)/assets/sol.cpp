#include<bits/stdc++.h>
using namespace std;
main(){
  int t;
  cin>>t;
  while(t--){
    int n;
    cin>>n;
    vector<int>a(n),ans(n,1);
    for(auto&ai:a)cin>>ai;

    vector<vector<int>>range;
    for(int i{1},l,r;i<=n;++i){
      l=i*a[i-1],r=l+i-1;  
      
      if(0<=l&&l<n)range.emplace_back(vector<int>{l,min(r,n-1)});
    }
     
    if(range.size()){
      sort(range.begin(),range.end());
      int l{range[0][0]},r{range[0][1]};
      for(int i{1},ll,rr;i<(int)range.size();++i){
        ll=range[i][0],rr=range[i][1];
        
        if(ll>r){
          for(int j{l};j<=r;++j)ans[j]=0;
     
          l=ll,r=rr;
        }
        else r=max(r,rr);
      }
     
      for(int j{l};j<=r;++j)ans[j]=0;
    }
     
    cout<<count(ans.begin(),ans.end(),1)<<'\n';
    for(int i{};i<n;++i)
      if(ans[i])cout<<i<<' ';

    cout<<'\n';
  }
}