# Codeforces Round 1121 (Div. 2) — B. Knife's Pill Farm
> **Problem:** [B. Knife's Pill Farm](https://codeforces.com/contest/2264/problem/B)  
> **Tags:** data structures, greedy  
> **Difficulty:** Div. 2 B  
> **AC Submissions:** [`Priority Queue`](https://codeforces.com/contest/2264/submission/390669108) [`Multi Set`](https://codeforces.com/contest/2264/submission/390668217) 

## 📌 Problem Summary

Choose a length-`m` subsequence `b` of `a` (order preserved) to maximize
`Σ i·(b_i − b_{i−1})` for `i = 1..m`, with `b_0 = 0`. Values in `a` can be negative.

## 💡 Core Insight — Telescoping via Summation by Parts

Expand and re-group the sum:

`Σ i·(b_i − b_{i−1}) = m·b_m − Σ b_i` (for `i = 1` to `m−1`)

This is the same family as [Telescoping Sum](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Miscellaneous/CP%20Vocabulary/Programming%20&%20Problem-Solving%20Vocabulary.md#telescoping-sum) / [The Corner-Anchor Pattern](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/General%20Tricks%20&%20Techniques/Telescoping%20Sums/The%20Corner-Anchor%20Pattern.md) — a coefficient-weighted sum collapses to "last term, scaled" minus "sum of everything before it." Once collapsed, the problem splits cleanly: fix `b_m = a[i]` for each candidate position `i`, then minimize `Σ b_1..b_{m−1}` — the sum of the other `m−1` chosen elements, all required to sit before index `i`.

Since summation doesn't care about order, minimizing that sum is just: **pick the `m−1` smallest values from `a[0..i−1]`.**

## 🔀 Approach

Scan `i` left to right. Maintain a [Bounded Max-Heap (Keep-k-Smallest)](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Miscellaneous/CP%20Vocabulary/Programming%20&%20Problem-Solving%20Vocabulary.md#bounded-max-heap-keep-k-smallest) of size `m−1` holding the smallest `m−1` values seen so far, plus their running sum. At each `i ≥ m−1`, compute the candidate score `m*a[i] - sum`, take the max across all `i`, then push `a[i]` into the heap and evict the new maximum to keep the window at size `m−1`.

```cpp
long long sum{};
priority_queue<long long> b;
for (long long i{}; i < m - 1; ++i)
    sum += a[i],
    b.push(a[i]);

long long mx{m * a[m - 1] - sum};
for (long long i{m - 1}; i < n; ++i)
    b.push(a[i]),
    mx = max(mx, m * a[i] - sum),
    sum += a[i] - b.top(),
    b.pop();

cout << mx << '\n';
```

`O(n log n)` per test case — one heap insert/evict per index.

## ❌ / ✅ The Bug That Cost Two Submissions

Both early attempts ([`390638302`](https://codeforces.com/contest/2264/submission/390638302) [`390642913`](https://codeforces.com/contest/2264/submission/390642913)) initialized `mx{}` → `0`. Since `a_i` can be negative, `0` is not a value any real candidate is guaranteed to reach — it's an **unearned floor** (see [False Floor (Unearned Zero-Init)](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Miscellaneous/CP%20Vocabulary/Programming%20&%20Problem-Solving%20Vocabulary.md#false-floor-unearned-zero-init)). Fix: seed `mx` with the first legitimate candidate (`m*a[m-1] - sum`, computed before the loop) rather than a placeholder.

```cpp
// ❌ WA — silently returns 0 if every real candidate is negative
long long mx{};

// ✅ AC — starts inside the real candidate space
long long mx{m * a[m - 1] - sum};
```

## 🧪 Practice Problems

| Problem | Link | Status |
|---|---|---|
| CF 2264B — Knife's Pill Farm | [Link](https://codeforces.com/contest/2264/problem/B) | ✅ Solved |
| TBD | TBD | TBD |

## 🔗 Related

* [Telescoping Sum](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Miscellaneous/CP%20Vocabulary/Programming%20&%20Problem-Solving%20Vocabulary.md#telescoping-sum) — the algebraic reduction that makes this problem tractable.
* [Bounded Max-Heap (Keep-k-Smallest)](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Miscellaneous/CP%20Vocabulary/Programming%20&%20Problem-Solving%20Vocabulary.md#bounded-max-heap-keep-k-smallest) — the data-structure pattern used to maintain the running minimal-sum window.
* [False Floor (Unearned Zero-Init)](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Miscellaneous/CP%20Vocabulary/Programming%20&%20Problem-Solving%20Vocabulary.md#false-floor-unearned-zero-init) — the accumulator-initialization bug both WA submissions hit.
