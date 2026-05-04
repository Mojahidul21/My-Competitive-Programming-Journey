# C. Mental Monumental (Easy Version)

**Contest:** Codeforces Round 1095 (Div. 2)  
**Problem:** https://codeforces.com/contest/2226/problem/C  
**Solution:** https://codeforces.com/contest/2226/submission/373463633  
**Tags:** binary searchdata structuresgreedymathtwo pointers
**Verdict:** Accepted

---

## Problem Summary

Given an array `a` of `n` non-negative integers, apply `ci := ci mod bi` (each `bi >= 1`) to every element exactly once. Maximize the MEX of the resulting array.

---

## Key Observation

First ask: **what can a single element `x` become?**

Choose `b = x - i` for any target `i < x`. Then:

```
x mod (x - i) = i
```

This works only when `b > i`, i.e., `x - i > i`, i.e., **`x > 2*i`**.

Also, choosing `b > x` leaves `x` unchanged.

So the single rule that governs everything:

> **Element `x` can be transformed into value `i` if and only if `x > 2*i` (or `x == i`).**

---

## Greedy Strategy

To maximize MEX, greedily try to cover `i = 0, 1, 2, ...` in order. For each `i`, two straightforward cases arise:

- `i` already exists in the array → keep it as-is, move on.
- Some `x > 2*i` exists → transform `x` into `i`, move on.

But there is a subtlety. When we pull element `x` out of the pool to produce `i`, we create a future obligation: **`x` itself now needs to be covered when `i = x` arrives.** To resolve this, we look for a replacement `k > 2*i` that can produce `i` just as well, freeing `x` to cover itself. But `k` then carries the same obligation, and so the chain continues.

As long as a suitable replacement always exists, the chain keeps extending and MEX keeps growing. The moment no replacement can be found, the chain breaks and the answer is that `i`.

---

## Algorithm

Two containers drive the solution:

- `multiset<int> a` — pool of available elements.
- `multimap<int,int> b` — commitments. Entry `(x, i)` means element `x` was pulled from `a` to eventually produce `i`, and `x` itself still needs a replacement by the time `i = x` comes around.

`multimap` is used over `map` because the same key value can carry multiple independent commitments.

For `i = 0, 1, 2, ..., n`:

**Case 1 — `i` is in `a`:**  
Direct cover. Erase one copy of `i` from `a`.

**Case 2 — `i` is a key in `b`:**  
Element `i` was previously committed to produce `j = b[i]`. To free `i`, find replacement `k > 2*j` in `a` using `upper_bound(2*j)`. If found: erase `(i, j)` from `b`, insert `(k, j)` into `b`, erase `k` from `a`. Element `i` is now free to cover itself.  
If not found → MEX is `i`. Print and stop.

**Case 3 — `i` is in neither `a` nor `b`:**  
Find `l > 2*i` in `a` using `upper_bound(2*i)`. If found: erase `l` from `a`, insert `(l, i)` into `b`.  
If not found → MEX is `i`. Print and stop.

---

## Simulation on Example 4

Input: `9 9 8 2 4 4 3 5 3` → sorted `a = {2,3,3,4,4,5,8,9,9}`, `b = {}`

| i | case | action | a | b |
|---|---|---|---|---|
| 0 | 3 | l=2, erase 2, b←(2,0) | {3,3,4,4,5,8,9,9} | {(2,0)} |
| 1 | 3 | l=3, erase 3, b←(3,1) | {3,4,4,5,8,9,9} | {(2,0),(3,1)} |
| 2 | 2 | j=0, k=3>0, erase (2,0), b←(3,0), erase 3 | {4,4,5,8,9,9} | {(3,0),(3,1)} |
| 3 | 2 | j=0, k=4>0, erase (3,0), b←(4,0), erase 4 | {4,5,8,9,9} | {(3,1),(4,0)} |
| 4 | 2 | j=0, k=4>0, erase (4,0), b←(4,0), erase 4 | {5,8,9,9} | {(3,1),(4,0)} |
| 5 | 1 | 5 in a, erase 5 | {8,9,9} | {(3,1),(4,0)} |
| 6 | 3 | upper_bound(12) → end() | — | — |

No element greater than 12 exists. **Print 6.** ✓

---

## Complexity

Each iteration does at most one `find`, one `upper_bound`, one `erase`, and one `insert` on balanced BST containers — all `O(log n)`. The loop runs at most `n + 1` times.

**Total: `O(n log n)` per test case.**

---

## Code

```cpp
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

tourist
tcl

int n;
cin>>n;
multiset<int>a;
for(int i{},ai;i<n;++i){
	cin>>ai;
	a.insert(ai);
}

multimap<int,int>b;
for(int i{};i<=n;++i){
    auto iita=a.find(i);
    if(iita!=a.end()){                              // i in a → erase it
        a.erase(iita);
    }else{
        auto iitb=b.find(i);
        if(iitb!=b.end()){                          // i is a key in b
            int j=iitb->second;
            auto kita=a.upper_bound(2*j);
            if(kita!=a.end()){                      // k > 2*j exists in a
                int k=*kita;
                a.erase(kita);
                b.erase(iitb);
                b.insert({k,j});
            }else{
            	cout<<i;
            	break;
            }
        }else{                                      // i not in a, not in b
            auto lita=a.upper_bound(2*i);
            if(lita!=a.end()){                      // l > 2*i exists in a
                int l=*lita;
                a.erase(lita);
                b.insert({l,i});
            }else{
            	cout<<i;
            	break;
            }
        }
    }
}

tnl
Ace_Azimuth_Aviator
```
