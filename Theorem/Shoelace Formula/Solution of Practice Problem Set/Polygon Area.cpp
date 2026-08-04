// Problem Title     : Polygon Area
// Problem Statement : https://cses.fi/problemset/task/2191/
// Solution          : https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Theorem/Shoelace%20Formula/Polygon%20Area.cpp

#include <bits/stdc++.h>
using namespace std;
main() {
    int n;
    cin>>n;
    vector<int>x(n),y(n);
    for(int i{};i<n;++i)
        cin>>x[i]>>y[i];

    long long xy{};
    for(int i{};i<n;++i)
        xy+=(long long)x[i]*y[(i+1)%n]-(long long)y[i]*x[(i+1)%n];
    
    cout<<abs(xy);
}
