// Problem Title     : Polygon Lattice Points
// Problem Statement : https://cses.fi/problemset/result/18213112/
// Solution          : https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Theorem/Shoelace%20Formula/Polygon%20Lattice%20Points.cpp

#include <bits/stdc++.h>
using namespace std;

long long twiceArea(vector<int>&x,vector<int>&y){
    int n{x.size()};
    long long xy{};
    
    for(int i{};i<n;++i)
        xy+=(long long)x[i]*y[(i+1)%n]-(long long)y[i]*x[(i+1)%n];
    
    return abs(xy);
}

long long boundary(vector<int>&x,vector<int>&y){
    int n{x.size()};
    long long B{},dx,dy;    
    
    for(int i{};i<n;++i)
        dx=abs(x[(i+1)%n]-x[i]),
        dy=abs(y[(i+1)%n]-y[i]),
        B+=gcd(dx,dy);

    return B;
}

long long interior(long long tA,long long B){
    return (tA-B+2)/2;
}

main(){
    int n;
    cin>>n;
    vector<int>x(n),y(n);
    
    for(int i{};i<n;++i)
        cin>>x[i]>>y[i];

    long long
    tA{twiceArea(x,y)},
    B{boundary(x,y)},
    I{interior(tA,B)};

    cout<<I<<' '<<B;
}
