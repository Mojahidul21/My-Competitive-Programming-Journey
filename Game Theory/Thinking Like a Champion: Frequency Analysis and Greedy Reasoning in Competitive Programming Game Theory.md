# Thinking Like a Champion: Frequency Analysis and Greedy Reasoning in Competitive Programming Game Theory

*A study guide for competitive programmers — with practice problems and a reusable mental framework*

---

## Introduction

Among the most elegant problems in competitive programming are those that combine **game theory** with **greedy observation**. At first glance, these problems look like they demand deep dynamic programming or exhaustive search. But with the right lens — specifically, looking at *how often* values appear and *what that parity implies* — you can often crack them in O(n log n) or even O(n).

This article builds that lens from scratch. By the end, you will have:

- A reusable framework for analyzing two-player removal games
- A clear mental checklist for frequency-based greedy reasoning
- Practice problems at several difficulty levels

---

## Part 1 — The Core Idea: Frequency Parity in Removal Games

### The Setup

Many competitive programming game problems share this skeleton:

> Two players alternate turns. On each turn, a player picks an element from a multiset according to some rule. The player who cannot move loses.

The key insight that unlocks a large class of these problems:

> **If you can force your opponent to always face the same situation you faced, you win.**

This is the essence of *strategy stealing* and *pairing arguments*. The most powerful version of this is:

**If a value appears an even number of times, it can be "paired up." Whoever takes one instance will eventually face a situation where the other player takes the matching instance — the net effect cancels, and the game on those elements is neutral.**

Conversely, **an odd-frequency value is "unbalanced." Someone will be stuck holding the unpaired instance.**

This is not always the whole story — but it is almost always where the analysis begins.

---

## Part 2 — The Mental Checklist

When you see a two-player removal game with some constraint on which element can be picked next, run through this checklist mentally:

```
Step 1: Can I identify the "dominant" elements?
        → Sort or group by value. Start from the largest (or most constrained).

Step 2: What does the frequency (count) of each group tell me?
        → Even count: this group is self-balancing. 
          A first-mover advantage here is neutral.
        → Odd count: this group has one "leftover" — 
          it will affect whose turn it is after this group is exhausted.

Step 3: If the dominant group is odd-frequency, can the current player 
        "offload" the leftover to the next group?
        → This depends on the transition rule:
          Can you legally move from this group to the next?
          Is the gap between group values within the allowed range?

Step 4: If the transition is allowed, treat the two groups as merged 
        and re-analyze. If not, the current group's parity is final.

Step 5: Repeat until all groups are processed or an answer is determined.
```

This checklist converts the game into a sequence of local decisions, each checkable in O(1) once the data is organized.

---

## Part 3 — Building the Framework: From Observation to Algorithm

### 3.1 Sorting by Value (Descending)

In most games with a "next element must be close to the previous" rule, you want to process elements from **largest to smallest** (or vice versa, depending on the rule). This is because:

- The largest value is the "bottleneck": no element can follow it unless the gap is small enough.
- Whoever deals with the largest-value group first sets the tone for the rest of the game.

**Practical step:** Compute a frequency map, then extract `(value, frequency)` pairs sorted by value descending.

### 3.2 Identifying the "Exit Condition"

For each group `(v, freq)` in sorted order, ask:

**Can this group be exited?**

An "exit" means: after exhausting or partially exhausting this group, can play continue to the next group?

This depends on two things:
1. **Parity of `freq`**: If `freq` is even, the group is self-contained — both players take equal turns from it. The last pick in this group returns the "initiative" to whoever entered it. If `freq` is odd, one extra pick happens, and initiative flips.
2. **Transition constraint**: Even if initiative would let us move to the next group, can we? Only if the gap between this group's value and the next group's value is within the allowed range `k`.

### 3.3 The Decision at Each Group

At each group, you face one of three situations:

| Frequency | Transition possible? | Result |
|-----------|---------------------|--------|
| Even | Doesn't matter | This group is neutral. The player who entered it also "exits" it. Move on. |
| Odd | Yes | This group passes initiative to the next group. Merge analysis with next group. |
| Odd | No | This group is the final determinant. The player who entered it takes the last pick. |

### 3.4 Putting It Together

Now the full algorithm:

```
Sort groups by value descending.
For each group i:
    If freq[i] is even:
        → Group is neutral. Continue to group i+1.
    If freq[i] is odd:
        If i+1 exists AND value[i] - value[i+1] <= k:
            → Initiative passes to group i+1. Continue.
        Else:
            → This group decides the game. 
              The player who is "to move" when entering this group
              takes the last element and wins.
              Answer depends on who that is.
```

The "who is to move" tracking is implicit: since we start from the largest group and process downward, the first "deciding" group we hit determines the answer.

---

## Part 4 — Why This Works: The Pairing Argument

Here is the deeper reason this greedy approach is correct.

**Claim:** In a removal game where elements are taken in non-increasing order (each pick must be within `k` of the previous), optimal play within a group of equal values is to always pick from that group until forced to transition.

**Intuition:** Picking from a different group early breaks the pairing of the current group. If your opponent then "completes" your pairing by picking the matching element from your original group, they've gained nothing and lost a move. So the dominant strategy is to exhaust a group before moving on, respecting the pairing structure.

**Formal sketch:** Consider a group `G` of `m` equal values. If `m` is even, player A picks one, player B picks one, ..., player B picks the last. The net result: zero advantage, zero disadvantage, B takes the last pick. If `m` is odd: A picks the last one. So odd frequency = the "entrant" to this group takes the last pick.

This is why even frequency → neutral, odd frequency → initiative-shifting.

---

## Part 5 — Common Variants and Extensions

### Variant A: The "First Move is Special"

Sometimes a third party (or you as the solver) makes the very first move, and you must determine if there *exists* a first move that guarantees a win for the second player.

Key insight: The first move removes one element. This changes the frequency of exactly one group by 1. So:

- If a group has **even** frequency, removing one element makes it **odd** — now it controls initiative.
- If a group has **odd** frequency, removing one element makes it **even** — making it neutral.

You need to find a first-move element such that the resulting frequency configuration leads to a win for the second player. Iterate over possible "first moves" greedily: check the highest-priority group first, try removing one element from it, and check if the resulting game is a second-player win.

### Variant B: The Gap Constraint is Asymmetric

Some problems allow `y - x` to be in range `[0, k]` (non-decreasing picks) or `[-k, 0]` (non-increasing picks). The analysis is similar but you must be careful about the direction of sorting.

### Variant C: Multiple Winning Conditions

Some games end not when no move can be made, but when a certain score threshold is reached. Frequency analysis still applies, but the "terminal condition" changes how you interpret parity.

---

## Part 6 — Practice Problems

Work through these in order. Each builds on the previous.

**Level 1 — Pure Parity**
- A multiset of integers. Two players alternately remove any element. The player who takes the last element wins. Given the multiset, who wins with optimal play?
- *(Hint: total count parity determines everything.)*

**Level 2 — Restricted Removal**
- Same as above, but each removal must be of a value ≥ the previous removal. Who wins?
- *(Hint: sort descending, apply the frequency checklist.)*

**Level 3 — Gap Constraint**
- Each removal must satisfy `0 ≤ y − x ≤ k` where `x` was the previous pick. Who wins?
- *(Hint: now groups of equal values can "merge" if their gap ≤ k. Apply the transition check.)*

**Level 4 — First Move by a Third Party**
- Same as Level 3, but a third party makes the very first move (choosing any element). The third party wants the second player (of the remaining two) to win. Does such a first move exist?
- *(Hint: iterate over possible first-move groups greedily from largest value down. Check parity and transition at each step.)*
- *Reference problem: [Codeforces Round 1103 | Div. 3 | Problem D](https://codeforces.com/contest/2236/problem/D)*
- *Reference solution: [Ace_Azimuth_Aviator](https://codeforces.com/contest/2236/submission/378613568)*

**Level 5 — Harder Extensions**
- Codeforces: search for problems tagged `[games] [greedy]` or `[games] [constructive algorithms]` at difficulty 1700–2100.
- AtCoder: ABC game theory problems, especially those involving Grundy numbers combined with frequency constraints.

---

## Part 7 — Coding It Up

Here is a clean template in C++ for the Level 3/4 family of problems:

```cpp
// Given: array a[], integers n and k
// Returns: true if there exists a first move s.t. second player wins

bool solve(vector<int>& a, int n, int k) {
    // Step 1: frequency map
    map<int, int, greater<int>> freq;
    for (int x : a) freq[x]++;

    // Step 2: extract sorted (value, count) pairs, descending by value
    vector<pair<int,int>> groups(freq.begin(), freq.end());
    // groups[0] has the largest value

    // Step 3: greedy scan
    for (int i = 0; i < (int)groups.size(); i++) {
        auto [val, cnt] = groups[i];
        
        // Try: what if we remove one element from this group as "first move"?
        // That makes its count (cnt - 1).
        int adjusted = cnt - 1;
        
        // If adjusted is even: this group is now neutral.
        // The "decider" will be determined by a later group.
        // But we need the overall game (after our first move) to be 
        // a second-player win — meaning the first real player (Dabir) loses.
        
        // Check: does removing one from this group create a winning config?
        // A config is "second-player wins" if all groups are either:
        //   - even (neutral), OR
        //   - odd but can transition to the next group within gap k
        // AND the final "deciding" group favors the second player.
        
        // Simplified check for this variant:
        // After removing one from group i, if group i becomes even → good start.
        // Then check remaining groups normally.
        
        // (Full implementation depends on exact problem variant)
        
        if (adjusted % 2 == 0) {
            // Group i is now neutral after our removal.
            // Check if rest of groups are all resolvable.
            bool ok = true;
            for (int j = i + 1; j < (int)groups.size(); j++) {
                auto [vj, cj] = groups[j];
                auto [vprev, cprev] = groups[j-1];
                if (cj % 2 == 1) {
                    // Odd group — can it transition?
                    if (j + 1 < (int)groups.size() && 
                        vj - groups[j+1].first <= k) {
                        continue; // will merge with next
                    } else {
                        ok = false; break;
                    }
                }
            }
            if (ok) return true;
        }
    }
    return false;
}
```

> **Note:** This is a structural template. The exact inner loop logic adapts to your specific problem constraints. Always test against the problem's examples before submitting.

---

## Part 8 — Debugging Tips

When your greedy solution fails on some test cases, check these first:

1. **Off-by-one on transition:** The gap check should be `value[i] - value[i+1] <= k`, not `< k`. Verify with a hand-traced example.
2. **Edge case: single-element groups.** A group of size 1 is always odd. Does it have a neighbor to transition to?
3. **Edge case: the first-move element itself.** If you remove one element as the "first move," make sure you're adjusting the correct group's count, not working on a stale copy.
4. **The last group:** If the last group (smallest value) is odd with no successor, that group is always a decider. Make sure your code handles the loop's end correctly.

---

## Summary

The core mental model:

> **Sort by value. Scan greedily. At each group, even = neutral, odd = check transition. The first "stuck" odd group decides the game.**

The first-move variant adds one layer:

> **Try removing from each group in turn. Check if the result is a second-player win. Return true on the first success.**

This framework is clean, fast, and surprisingly general. Once internalized, you will recognize it in many game theory problems disguised with different surface stories — from card games to board games to string manipulations.

Master the checklist. Trust the parity. Let the greedy structure do the work.

---

## References and Further Reading

- Codeforces Round 1103 (Div. 3), Problem D — a concrete instance of the Level 4 variant
- Sprague–Grundy theorem — the theoretical foundation for combinatorial game analysis
- "Competitive Programmer's Handbook" by Antti Laaksonen, Chapter on Game Theory
- Codeforces EDU section: Game Theory tracks

---

*Written for competitive programmers looking to sharpen their game theory intuition. Good luck in your next contest!*
