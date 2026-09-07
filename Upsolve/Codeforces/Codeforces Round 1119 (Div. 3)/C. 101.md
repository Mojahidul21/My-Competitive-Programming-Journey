![](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Supporting%20Images/11.%20CF2259C_101_hook.svg)
# CF 2259C — "101" (Codeforces Round 1119, Div. 3)

**Problem:** [URL](https://codeforces.com/contest/2259/problem/C)  
**Accepted submission:** [URL](https://codeforces.com/contest/2259/submission/389707668)  
**Tags:** `constructive algorithms`, `greedy`  

---

## Problem

You get an array of length `n` with entries in `{-1, 0, 1}`. Define the *score*
of a fully-`0`/`1` array as the length of the widest window that starts and ends
with `1`, with only `0`s strictly in between (score `0` if no such window
exists). Replace every `-1` with `0` or `1` — any way you like — so that the
resulting array's score is as large as possible. You only need to output *a*
valid array achieving the max score, not the score itself.

Constraints: `n ≤ 2·10^5` per test case, sum of `n` over all test cases
`≤ 2·10^5`, up to `10^4` test cases. (Full statement, constraints, and the
official examples/notes are on the problem page linked above.)

### Sample (from the problem)

```
Input:                          Output:
6                                1 0 0 0 0 1
1 0 -1 0 0 1
7                                0 1 0 0 1 0 1
0 -1 0 0 1 0 1
5                                1 0 0 1 0
-1 0 0 -1 0
...                              ...
6                                1 0 0 0 0 1
-1 -1 -1 -1 -1 -1
```

The all-`-1` case (`n=6`) is exactly the one animated above: both anchors get
created from scratch, and the middle stays crumbs.

---

## Key Observation

The score depends *only* on where the two outermost `1`s end up. Existing `1`s
and `0`s are fixed; you can't touch them. So the whole problem collapses to a
decision about the `-1`s:

- The **leftmost** and **rightmost** nonzero-capable position (i.e. the first
  and last index that is currently `1`, or can become `1`) should be forced
  to `1`.
- Every `-1` strictly **between** them should be forced to `0`.

You never need to compute or compare candidate window lengths. The construction
*is* the answer.

---

## Why This Is Optimal

Let `l` = index of the first nonzero element after replacement, `r` = index of
the last nonzero element after replacement. The score is at most `r - l + 1`,
since no `1` exists outside `[l, r]`.

- Pushing `l` as far left as possible and `r` as far right as possible can only
  **increase** `r - l + 1` — it never removes an existing `1`, so it's always
  weakly better than leaving an outer `-1` as `0`.
- Once `l` and `r` are fixed, the score is *exactly* `r - l + 1` **only if** no
  interior `-1` is left as a `1`. Any interior `-1` promoted to `1` would only
  split the zero-run into two shorter candidate windows — it can never create a
  window longer than `r - l + 1`, and risks fragmenting it. So setting all
  interior `-1`s to `0` is always at least as good, and simplest.

Both anchors are free wins; nothing in between should ever move. No search, no
comparison of candidate lengths — direct construction from two anchors. This is
the **Anchor-and-Derive** pattern applied outside number theory: find the two
extremal values, derive everything in between deterministically, and don't
simulate the very metric you're trying to optimize.

---

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
main(){
    int t;
    cin>>t;
    
    while(t--){
        int n,l{200000},r{-1};;
        cin>>n;
        vector<int>a(n);

        for(auto&i:a)cin>>i;
        for(int i{};i<n;++i)if(a[i]){a[i]=1,l=i;break;}
        for(int i{n-1};i>-1;--i)if(a[i]){a[i]=1,r=i;break;}
        for(int i{l+1};i<r;++i)if(a[i]==-1)a[i]=0;
        for(const auto&i:a)cout<<i<<' ';

        cout<<'\n';
    }
}
```

**Edge case to double check:** if the whole array is `-1`s or has no nonzero
element at all, `l` stays `n` and `r` stays `-1`, so the interior loop never
runs — but the two anchor-scan loops still fire (any `-1` counts as truthy, so
the leftmost/rightmost `-1` becomes an anchor `1` regardless). No extra cleanup
pass is needed here.

---

## Flowchart

```mermaid
flowchart TD
    A[Read array a] --> B[Scan left to right:<br/>first nonzero -> set to 1, record l]
    B --> C[Scan right to left:<br/>last nonzero -> set to 1, record r]
    C --> D[For i in l+1 .. r-1:<br/>if a_i == -1, set to 0]
    D --> E[Output array]
```

---

## Sample Verification

Test case: `n=5`, `a = [-1, 0, 0, -1, 0]`

- Leftmost nonzero: index 0 (`-1` → `1`), so `l = 0`.
- Rightmost nonzero: index 3 (`-1` → `1`), so `r = 3`.
- No interior `-1`s remain between `l` and `r`.
- Result: `[1, 0, 0, 1, 0]` — matches the sample, score = 4.

Test case: `n=6`, `a = [-1, -1, -1, -1, -1, -1]` (the animated example)

- Leftmost nonzero: index 0 → `l = 0`, set to `1`.
- Rightmost nonzero: index 5 → `r = 5`, set to `1`.
- Interior indices 1–4 are `-1` → set to `0`.
- Result: `[1, 0, 0, 0, 0, 1]` — matches the sample, score = 6.

---

## Pitfall: The Simple Solution Went WA 3 Times!

I overthought it. I tracked extra state variables — chasing the score like it
needed to be computed and compared, window by window.

Bug: any `-1` outside my "found" window never got touched. Raw `-1`s leaked
into the output. Checker caught it instantly.

**Do not overthink like:** "let me track the best window and its score."
The problem never asked for the score — only a valid array.

**Always think simple like:** two anchors, everything else `0`. Done.

See **Boundary Ghost Values** — same lesson: if a solution only "resolves" a
found subregion, check what happens to everything outside it.

---

## Related

- [**Anchor and Derive**](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/General%20Tricks%20%26%20Techniques/Contest%20Strategy/Anchor%20and%20Derive.md) — general principle; this problem is a worked example outside number theory.
- [**Boundary Ghost Values**](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Miscellaneous/CP%20Vocabulary/Programming%20%26%20Problem-Solving%20Vocabulary.md#boundary-ghost-values) — auditing that every
  array cell has a deterministic fate, not just cells inside a discovered window.
- [**Trust the Predicate**](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/General%20Tricks%20%26%20Techniques/Contest%20Strategy/Trust%20the%20Predicate%3A%20Stop%20Simulating%20What%20You've%20Already%20Proven.md) — related instinct: once you've proven the optimal construction, act on it directly instead of verifying via simulation.
