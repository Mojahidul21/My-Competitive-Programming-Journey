
Slide `k` from `0` to `n`, updating the running total in O(1) per step, and take the minimum. This is your loop:

```cpp
int ones{}, zeros{(int)count(all(s), '0')}, ans{zeros};
for (int i{}; i < n; ++i)
    s[i] != '0' ? ++ones : --zeros,
    ans = min(ans, ones + zeros);
```

## Why feasibility doesn't need special-casing

> [!IMPORTANT]
> Not every split point `k` is actually *achievable* by a valid operation order — a suffix `0` needs some `1` earlier in the string to OR against, and that `1` must trace back to an original `1`, not a manufactured one. Let `p` = index of the first original `1`. Split points `k < p` are infeasible: the suffix would contain original `0`s at positions `< p` with no `1` anywhere before them to source from.
>
> The reassuring part: **you never have to filter these out.** For `k < p`, `cost(k) = (total zeros) - k`, which is strictly decreasing as `k → p`. So every infeasible split point costs *at least* as much as the feasible split `k = p`. The unconstrained sliding-window minimum lands on a feasible answer automatically — the infeasible region is provably never optimal, so it's harmless to include in the scan.

This is the kind of "the greedy formula silently self-corrects" argument worth remembering — it's why the code has no explicit feasibility check and is still correct.

## ❌ / ✅ Same idea, the slow vs. fast version

**❌ Naive: recompute `cost(k)` from scratch for every `k`**
```cpp
int ans = INT_MAX;
for (int k = 0; k <= n; ++k) {
    int ones = count(s.begin(), s.begin() + k, '1');
    int zeros = count(s.begin() + k, s.end(), '0');
    ans = min(ans, ones + zeros);
}
// O(n) per k → O(n^2) total — too slow for n up to 2·10^5
```

**✅ Optimal: maintain the running cost while sliding `k`**
```cpp
int ones = 0, zeros = count(s.begin(), s.end(), '0');
int ans = zeros; // cost(0)
for (int i = 0; i < n; ++i) {
    if (s[i] != '0') ++ones;  // s[i] enters the "must become 0" prefix
    else --zeros;             // s[i] leaves the "must become 1" suffix
    ans = min(ans, ones + zeros);
}
// O(n) total
```

The only change is turning a recomputation into an incremental update — a very common Div. 3/4 pattern once a problem reduces to "minimize prefix-cost + suffix-cost over a single split point."

## Complexity

O(n) per test case, O(∑n) overall — well inside the 2·10⁵ sum-of-n limit.

## Practice problems

| Problem | Pattern | Notes |
|---|---|---|
| CF 2266C | Sliding split-point argmin | this writeup |
| TBD | — | fill with another prefix-cost/suffix-cost split-point problem when solved |

## Related

> [!TIP]
> This "prefix cost + suffix cost, slide the boundary, O(1) update" shape is common enough that it might deserve its own vocabulary entry (something like *Sliding Split-Point*) if it recurs. Flagging rather than adding pre-emptively — let me know if you want it drafted, and where it should slot alphabetically.
