// Title: B. Domino Tiles
// Problem: https://codeforces.com/contest/2256/problem/B
// Solution: https://codeforces.com/contest/2256/submission/386425561

#include<bits/stdc++.h> 
using namespace std;
main(){
    int t;
    cin>>t;
    
    while(t--){
        bool valid{true},efree{true},ofree{true};
        int n,eid{-1},oid{-1};
        string s,flip{"01"};

        cin>>n>>s;

        for(int i{};valid&&efree&&i<n;i+=2)
            if(s[i]!='?')
                efree=false,eid=i;

        for(int i{eid-2},j{eid!=-1&&s[eid]=='1'};valid&&!efree&&i>-1;i-=2,j=!j)
            if(s[i]==flip[j])
                valid=false;

        for(int i{eid+2},j{eid!=-1&&s[eid]=='1'};valid&&!efree&&i<n;i+=2,j=!j)
            if(s[i]==flip[j])
                valid=false;

        for(int i{1};valid&&ofree&&i<n;i+=2)
            if(s[i]!='?')
                ofree=false,oid=i;

        for(int i{oid-2},j{oid!=-1&&s[oid]=='1'};valid&&!ofree&&i>0;i-=2,j=!j)
            if(s[i]==flip[j])
                valid=false;

        for(int i{oid+2},j{oid!=-1&&s[oid]=='1'};valid&&!ofree&&i<n;i+=2,j=!j)
            if(s[i]==flip[j])
                valid=false;

        cout<<(!valid?0:efree&&ofree?4:efree||ofree?2:1)<<endl;
    }
}
