# Codeforces Round 1121 (Div. 2) — A. Rumb Needs a Hand
> - **Problem:** [A. Rumb Needs a Hand](https://codeforces.com/contest/2264/problem/A)
> **Submission:** [AC solution](https://codeforces.com/contest/2264/submission/390663340)
> **Tags:** implementation, sorting, two pointers
> **Difficulty:** Div. 2 A

## 📌 Problem Summary

Given a permutation `p` of length `n`, choose indices `i1 < i2 < … < im` (any `m` from `1` to `n`) and reverse the elements sitting at those indices — exactly once. Determine whether this can sort `p`.

## 💡 Core Insight

A fixed point (`p[i] = i`) should never be selected — including it in the reversal can only break it, never help. So strip fixed points and collect the misplaced *values*, in position order: `v1, v2, …, vm`.

The operation itself is an **involution**: it maps `i_j → i_{m-j+1}`, a mirror pairing, not an arbitrary permutation. So the only way to fix everything in one shot is if `reverse(v)` is already sorted. This works because the set of misplaced values is exactly the set of misplaced positions (fixed points already consumed their matching numbers) — so checking `reverse(v)` is sorted is equivalent to checking the reversal lands every value where it belongs.

> [!NOTE]
> The achievable operation isn't "any involution on the misplaced elements" — it's specifically the *mirror* involution. A reader might assume any pairing works; it doesn't. That's the one subtlety worth stating explicitly.

## 🔀 Mermaid Flowchart

```mermaid
flowchart TD
    A[Read n, permutation p] --> B{For each index i}
    B -->|p[i] == i| C[Skip — fixed point]
    B -->|p[i] != i| D[Append p[i] to misplaced list]
    C --> B
    D --> B
    B -->|done| E[Reverse misplaced list]
    E --> F{Is reversed list sorted?}
    F -->|Yes| G[Output YES]
    F -->|No| H[Output NO]
```

## ❌ / ✅ Approach Comparison

**❌ Brute-force / simulate:** trying subsets of indices or explicitly generating reversal candidates — unnecessary and the wrong shape entirely; the involution structure makes this a single deterministic check, not a search.

**✅ Filter → reverse → check sorted:**

```cpp
vector<int> a;
for (int i = 1, j; i <= n; ++i)
    cin >> j, i != j && (a.emplace_back(j), true);

reverse(a.begin(), a.end());
cout << (is_sorted(a.begin(), a.end()) ? "YES" : "NO") << '\n';
```

`O(n)` per test case — read once, filter once, reverse once, check once.

## 🧪 Practice Problems

| Problem | Link | Status |
|---|---|---|
| CF 2264A — Rumb Needs a Hand | [Link](https://codeforces.com/contest/2264/problem/A) | ✅ Solved |
| TBD | TBD | TBD |

## 🔗 Related

* [Reduction](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Miscellaneous/CP%20Vocabulary/Programming%20&%20Problem-Solving%20Vocabulary.md#reduction) — this problem reduces "does one exotic reversal sort the array" to "is reverse(misplaced) sorted."
* Not a [Chain Decomposition](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Miscellaneous/CP%20Vocabulary/Programming%20&%20Problem-Solving%20Vocabulary.md#chain-decomposition-independent-component-grouping) instance, despite the pairing structure — "sorted" is a single global property of the whole reversed sequence, not something checkable per-pair in isolation.
