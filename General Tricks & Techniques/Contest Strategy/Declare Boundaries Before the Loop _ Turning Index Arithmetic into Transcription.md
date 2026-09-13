# Declare Boundaries Before the Loop: Turning Index Arithmetic into Transcription

![Boundary chain diagram: diagonal, vertical, and horizontal segments for n=5, k=7](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Supporting%20Images/13.%20Boundary%20Chains.svg)

I noticed this comparing two of my own submissions to the same problem — [Codeforces Round 1120 (Div. 2) B. Min Matrices](https://codeforces.com/contest/2263/problem/B). Same algorithm, same construction, both Accepted. One took me too long in-contest. The other, written during upsolve with no new insight, took a fraction of the time. Nothing about the *idea* changed between the two. Only the way I wrote it did.

## The construction, briefly

Given `n` and `k`, build an `n×n` grid with `1..n²` placed so the row/column minimums have exactly `k` distinct values. The idea: build a chain of `k` cells holding `1..k` — a diagonal segment, then a vertical segment continuing down one column, then a horizontal segment continuing along one row — and fill the rest of the grid with the remaining values. The figure above shows this chain for `n=5, k=7`: the six boundary variables (`diaStart`, `diaEnd`, `verStart`, `verEnd`, `horStart`, `horEnd`) are exactly the numbers labeling where each colored segment begins and ends. Both submissions build this same shape.

## What actually differed

**1. Boundaries computed once, named, and chained.**

In-contest, I recomputed the same expression inline, in three different loops:

```cpp
// contest version — same value, derived three separate times
for (int stop = 2*n - k, i = 0, j = 0; i < stop; ++i, ++j) ...
for (int i = 2*n - k, j = 2*n - k - 1, val = 2*n - k + 1; i < n; ++i, ++val) ...
for (int i = 2*n - k - 1, j = 2*n - k; j < n; ++j, ++val) ...
```

Every recomputation is a fresh chance to get it wrong, and each loop forces me to re-derive "where does the diagonal end" from scratch. On upsolve, I named each boundary once and built every later one *from* the one before it:

```cpp
// upsolve version — six named boundaries, declared before any loop runs
int diaStart = 1,
    diaEnd   = 2*n - k,
    verStart = diaEnd + 1,
    verEnd   = n,
    horStart = verEnd + 1,
    horEnd   = k;
```

Read top to bottom, this is the whole construction as a paragraph. Writing the loops afterward became transcription, not re-derivation. The rule: if you're going to reference "where segment X ends" more than once, it gets a name, and it gets that name *before* you touch a loop.

**2. Indexing matched to the problem, not to habit.**

The contest version was 0-indexed out of reflex, so a diagonal that's conceptually "positions `1` to `2n-k`" turned into `i < stop` with `i` starting at `0` while the *value* written there started at `1` — two different starting points for the same diagonal position, tracked separately in my head on every iteration. The upsolve version sized the grid `(n+1)×(n+1)` and indexed from `1`, so position and value lined up directly: `a[i][i] = runner` where `runner` starts at `1`. The problem is already 1-indexed — rows, columns, and values all run `1..n` or `1..n²`. Indexing the array the same way removed a constant stream of `+1`/`-1` translation that wasn't free; it was where the actual time went.

## The general rule

Before writing a single loop for a constructive problem:

- Write out every segment boundary as a named variable, each defined in terms of the previous one, so the whole layout is readable as one block before any code executes.
- Choose the array's indexing to match the problem's own indexing, not whatever's fastest to type. If the problem is 1-indexed, size arrays `n+1` and index from `1`.

Neither step is an algorithmic idea — it's a transcription discipline. The gap it closes isn't "can I find the construction," it's "how much translation do I do between having the idea and having working code."

## Related

- [Anchor-and-Derive](../Contest%20Strategy/Anchor%20and%20Derive.md) — same family one level up: fix something concrete before reasoning proceeds, rather than deriving it on the fly. Here that "something concrete" is a segment boundary, fixed by name before any loop runs.
- [Comfortable with Your Matrices — Fix an Axis, Drop a Loop](../Decide%20Traverse%20Direction/Comfortable%20with%20Your%20Matrices%20—%20Fix%20an%20Axis%2C%20Drop%20a%20Loop.md) — same discipline applied to a different decision: choosing loop/axis structure deliberately instead of by reflex, the way this article chooses indexing deliberately instead of by reflex.

*(Add reciprocal links from both articles back to this one.)*
