1. Inquire a substring is present in a sting
```cpp
#include<bits/stdc++.h>
using namespace std;

bool contains(const string&s, const string&pattern){
    return s.find(pattern)!=string::npos;
}

int main(){
    string s,pattern{"..."};
    cin>>s;

    if(contains(s,pattern))
        cout<<"YES";
    else
        cout<<"NO";

    return 0;
}
```
