// Title: C. Hot Potatoes at the Fairy Warehouse
// Problem: https://codeforces.com/contest/2256/problem/C
// Solution: https://codeforces.com/contest/2256/submission/386578511

#include<bits/stdc++.h> 
using namespace std;
main(){
    int t;
    cin>>t;

    while(t--){
        int n,rscore{},bscore{};;
        string s;
        cin>>n>>s>>s;

        string ss(n*=2,'0');

        for(int i{},j{(i+1)%n};i<n;j=(++i+1)%n)
            if(s[i]!='0')
                ss[s[j]!='0'?i:j]='1';

        for(int i{1};i<n;i+=2)
            rscore+=ss[i]!='0',bscore+=ss[i-1]!='0';

        cout<<rscore<<' '<<bscore<<endl;
    }
}
