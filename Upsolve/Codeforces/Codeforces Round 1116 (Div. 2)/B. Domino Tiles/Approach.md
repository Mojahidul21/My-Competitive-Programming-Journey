# B. Domino Tiles

**Problem:** [Codeforces 2256B](https://codeforces.com/contest/2256/problem/B) | **AC submission:** [386425561](https://codeforces.com/contest/2256/submission/386425561)

<img src="tile-box-story.svg" width="800" alt="A row of tiles on a wooden table under moonlight, two of them faded to a question mark, with a small fairy pointing a wand at them"/>

A box of old tiles, a table, and a few marks too faded to read — that's the whole setup. Each tile becomes `0` or `1`; the only rule is that no two neighboring dominoes may share a weight. The question is simply: in how many ways can the fairy fill in the blanks and still keep the row valid?

## The problem, briefly

Given a string `s` of length `n` over `{0, 1, ?}`, replace every `?` with `0` or `1`. For each `i` from `1` to `n-1`, domino `i` has weight `s_i + s_{i+1}`. The completion is valid if every two *consecutive* dominoes have different weights. Count the number of valid completions, mod `998244353`.

## Key observation: the constraint collapses

Domino `i` has weight `s_i + s_{i+1}`. Domino `i+1` has weight `s_{i+1} + s_{i+2}`. Requiring these two weights to differ:

```
s_i + s_{i+1}  ≠  s_{i+1} + s_{i+2}
```

`s_{i+1}` sits on both sides — it cancels, leaving:

```
s_i ≠ s_{i+2}
```

That's the entire problem, distilled to one line. What looked like a rule linking every tile to its immediate neighbor turns out to never involve adjacent tiles at all — it only ever compares a tile to the one **two steps away**.

## Why this splits the row in two

Since the surviving constraint only ever compares `s_i` to `s_{i+2}`, the even-indexed tiles form one chain and the odd-indexed tiles form another, and the two chains never reference each other:

```mermaid
flowchart LR
    s0((s0)) -- "≠" --> s2((s2)) -- "≠" --> s4((s4)) -- "≠" --> s6((s6))
    s1((s1)) -- "≠" --> s3((s3)) -- "≠" --> s5((s5)) -- "≠" --> s7((s7))

    classDef even fill:#ffe0b2,stroke:#e65100,color:#3a2415
    classDef odd fill:#bbdefb,stroke:#0d47a1,color:#0d1b2a
    class s0,s2,s4,s6 even
    class s1,s3,s5,s7 odd
```

This is a direct instance of the [Parity Chain](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Miscellaneous/CP%20Vocabulary/Programming%20%26%20Problem-Solving%20Vocabulary.md#parity-chain) pattern: a constraint on `i` vs `i+1` simplifies, after algebra, into a constraint on `i` vs `i+2`. Once that happens, a size-`n` problem is really two independent, smaller problems, and the final answer is just the product of their individual counts.

## Counting one chain

Inside a single chain, `s_i ≠ s_{i+2}` for every consecutive pair forces the chain to strictly alternate — `0,1,0,1,...` or `1,0,1,0,...`. Three outcomes per chain:

- **Entirely `?`** — both alternations are possible → **2** ways.
- **At least one fixed character, no conflicts** — the alternation is pinned by that character and propagates outward in both directions → **1** way.
- **Fixed characters that break the alternation somewhere** → **0** ways for the whole answer.

## Deciding the answer

The even and odd chains are checked the same way, independently, and the results are combined at the end:

```mermaid
flowchart TD
    A0[Scan even-indexed tiles for a fixed digit] --> B0{Fixed digit found?}
    B0 -- No --> EF[evenfree = true]
    B0 -- Yes --> P0[Propagate the alternation outward]
    P0 --> C0{Conflict with another fixed digit?}
    C0 -- Yes --> V0[valid = false]
    C0 -- No --> EN[evenfree = false]

    A1[Scan odd-indexed tiles for a fixed digit] --> B1{Fixed digit found?}
    B1 -- No --> OF[oddfree = true]
    B1 -- Yes --> P1[Propagate the alternation outward]
    P1 --> C1{Conflict with another fixed digit?}
    C1 -- Yes --> V1[valid = false]
    C1 -- No --> ON[oddfree = false]

    EF --> D{valid?}
    EN --> D
    V0 --> D
    OF --> D
    ON --> D
    V1 --> D

    D -- No --> R0[Answer = 0]
    D -- Yes --> E{evenfree and oddfree?}
    E -- both true --> R4[Answer = 4]
    E -- exactly one true --> R2[Answer = 2]
    E -- neither true --> R1[Answer = 1]
```

`evenfree`/`oddfree` stay `true` only while that chain hasn't hit a fixed digit yet — each still-free chain doubles the answer. `valid` turns `false` the moment any chain's alternation is broken, which zeroes out the whole answer regardless of the other chain.

## Solution

Find the first fixed character in a chain, then scan outward from it in both directions, checking the alternation holds:

```cpp
for(int i{};valid&&efree&&i<n;i+=2)
    if(s[i]!='?')
        efree=false,eid=i;

for(int i{eid-2},j{eid!=-1&&s[eid]=='1'};valid&&!efree&&i>-1;i-=2,j=!j)
    if(s[i]==flip[j])
        valid=false;

for(int i{eid+2},j{eid!=-1&&s[eid]=='1'};valid&&!efree&&i<n;i+=2,j=!j)
    if(s[i]==flip[j])
        valid=false;
```

The odd chain (starting at index `1`) is checked the same way. Once both chains are scanned, the answer follows directly from `valid`, `efree`, and `ofree`:

```cpp
cout<<(!valid?0:efree&&ofree?4:efree||ofree?2:1)<<endl;
```

Each test case is a single `O(n)` pass, well within the `Σn ≤ 2·10^5` limit.
