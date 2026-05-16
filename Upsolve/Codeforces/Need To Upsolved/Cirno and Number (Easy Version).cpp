//  Note that, this is my draft solution, still it has not been submitted.

// Problem: https://codeforces.com/contest/2228/problem/C1

// Solution: Below is my solution. Now it is just after contest.
// The system does not receive any solution just now.
// I have to submit it later.
// If it got Accepted, I need huge work on this. Such as -
// learn well the tricks of string to int/long long, string absDifference, etc.
// write some template for frequently faced problems 

#include<bits/stdc++.h>

using namespace std;

#define tourist int main(){ios::sync_with_stdio(0);cin.tie(0);  // tourist - fast input output
#define Ace_Azimuth_Aviator return 0;}                          // Ace_Azimuth_Aviator - return 0;

#define css <<' '                                               // css - continuous single space
#define cnl <<'\n'                                              // cnl - continuous new line
#define pnl cout<<'\n';                                         // pnl - print new line
#define tcl int t;cin>>t;while(t--){                            // tcl - test case loop
#define tnl if(t)pnl}                                           // tnl - testcase new line

#define pno cout<<"NO";                                         // pno - print NO
#define pye cout<<"YES";                                        // pye - print YES
#define pny ?cout<<"NO":cout<<"YES";                            // pny - print NO/YES
#define pyn ?cout<<"YES":cout<<"NO";                            // pyn - print YES/NO

#define pze cout<<0;                                            // pze - print 0
#define pon cout<<1;                                            // pon - print 1
#define pzo ?cout<<0:cout<<1;                                   // pzo - print 0/1
#define poz ?cout<<1:cout<<0;                                   // poz - print 1/0

#define pmo cout<<-1;                                           // pmo - print minus one

#define bat bool ans=true;                                      // bat - boolean answer true
#define baf bool ans=false;                                     // baf - boolean answer false
#define atb {ans=true;break;}                                   // atb - answer true break
#define afb {ans=false;break;}                                  // afb - answer false break

#define lli long long                                           // lli - long long
#define imx INT_MAX                                             // imx - INT_MAX
#define imn INT_MIN                                             // imn - INT_MIN
#define con const int c=1e9                                     // con - constant
#define mod 998244353                                           // mod - modular arithmetic

#define vin(a,n) vector<int>a(n);for(auto&x:a)cin>>x;           // vin - vector int input
#define vlo(a,n) vector<lli>a(n);for(auto&x:a)cin>>x;           // vlo - vector long long input

#define all(a) a.begin(),a.end()                                // all(a) - all elements of the container a
#define rall(a) a.rbegin(),a.rend()                             // rall(a) - all elements of the container a in reverse order
#define allc(a) a.cbegin(), a.cend()                            // allc(a) - all elements of the const container a
#define rallc(a) a.crbegin(), a.crend()                         // rallc(a) - all elements of the const container a in reverse order

#define pub(a,x) a.push_back(x)                                 // pub(a,x) - push back x in container a
#define emb(a,...) a.emplace_back(__VA_ARGS__)                  // emb(a,...) - emplace back argument(s) in the container a

#define lob lower_bound                                         // lob - lower_bound
#define upb upper_bound                                         // upb - upper_bound

#define l2c(x) (int)ceil(log2(x))                               // l2c(x) - log2(x) rounded up

string absDiff(const string&a,const string&b){
    lli x=stoll(a),y=stoll(b);
    return to_string(abs(x-y));
}

string smallerStr(const string&a,const string&b){
    return stoll(a)<stoll(b)?a:b;
}

tourist
tcl

string a,b,c,d,ans{"0"};
cin>>a>>b>>c>>d;

char e=a[0],f=c[0],g=d[0];

int sz=a.size(),n{-1};

for(int i{};i<sz;++i){
    if(a[i]!=f&&a[i]!=g){
        e=a[i];
        n=sz-i;
        break;
    }
}

if(n==-1){}
else if(e<f){
    string
    x(n,f),
    y(n-1,g),
    xx=absDiff(a,x),
    yy=absDiff(a,y);

    ans=smallerStr(xx,yy);

    //cout<<x;

}
else if(e>f&&e<g){
    string x{"f"},y{"g"},xx(n-1,g),yy(n-1,f);

    x+=xx,y+=yy;

    xx=absDiff(a,x),
    yy=absDiff(a,y);

    ans=smallerStr(xx,yy);
}
else{
    string x(n,f),xx=absDiff(a,x);
    ans=xx;
}

cout<<ans;

tnl
Ace_Azimuth_Aviator
