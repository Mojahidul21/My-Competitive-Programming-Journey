# When an Operation Smears Left — Scan Right

## The Core Idea

Some problems give you an operation that affects not just one element, but an entire prefix. After you apply it at position $i$, every element $a_1, a_2, \ldots, a_i$ changes. This "smear" makes left-to-right greedy treacherous: every decision you make retroactively changes the ground beneath earlier decisions.

The fix is a direction flip in your thinking:

> **If an operation smears its effect leftward, commit to decisions from right to left.**

When you stand at position $i$ scanning right to left, every decision you've made so far sits strictly to the right of $i$. Each of those decisions affects $i$ too — but in a uniform, computable way. You don't need to re-examine anything. A single running value encodes the cumulative effect.

---

## What "Smear" Looks Like

The canonical signature:

- Operation selects index $i$ under some condition on $a_i$.
- Effect applies to all $j \leq i$ — the entire prefix.
- You want to greedily choose which indices to operate on.

Left-to-right greedy fails here because choosing $i$ mutates the state of everything before $i$, making future operations at $j < i$ operate on a different array than you planned.

Right-to-left greedy works because:

- When you reach $i$, all future operations (those at positions $> i$) are already decided.
- Their collective effect on $a_i$ is a pure function of how many you've picked — call it $k$.
- That effect is **independent of where exactly those operations were**, because each one includes $i$ in its prefix.

So you need only track $k$ (or some aggregate of it), not the full array state.

---

## The Parity Trick

When the operation is "negate the prefix," every operation in the decided set flips $a_i$ once. The net effect is:

$$\text{effective } a_i = (-1)^k \cdot a_i$$

where $k$ = number of operations decided so far (all to the right of $i$).

Only the **parity** of $k$ matters. That's a single bit of state.

**Decision rule (minimise sum):** apply an operation at $i$ if the effective value of $a_i$ is currently positive — i.e., if $(-1)^k \cdot a_i > 0$. Applying it makes that element's contribution negative and increments $k$.

```cpp
int k{};
vector<int> ops;
for (int i{n-1}; i >= 0; --i)
    if ((k%2 ? -1 : 1) * a[i] > 0)
        ++k, ops.push_back(i+1);   // collect 1-indexed
```

That's the entire algorithm. $O(n)$, no array mutation, no re-scanning.

---

## Why Left-to-Right Fails Here

The instinct is: scan left to right, and whenever $a_i$ is positive, flip at $i$ to make it negative.

The problem is that flipping at $i$ changes the sign of everything before $i$ as well. So the moment you act at position $i$, every position you already passed is now different. The state you built while scanning is invalidated.

This creates a chain reaction. To know the right decision at position $i$, you would need to know the true current sign of $a_i$ — but that depends on how many previous flips included $i$ in their prefix, which depends on decisions at positions $> i$, which you haven't reached yet. The information flows in the wrong direction for a left-to-right pass.

You can try to patch this by tracking sign-change boundaries or segment transitions in the array — but those boundaries themselves shift after every flip. Any structure you observe at step $k$ is stale by step $k+1$. The result is that you end up trying to operate on indices that are currently negative, which violates the operation's precondition ($a_i > 0$ is required to flip at $i$).

---

## Thinking Transition to Recognise

| Signal in the problem | What to think |
|---|---|
| Operation at $i$ affects all $j \leq i$ | Prefix smear — consider right-to-left |
| After operating at $i$, condition at earlier positions changes | Don't commit left-to-right |
| Effect of each operation on position $i$ is the same regardless of which position it was at | Running aggregate (parity, sum, XOR, etc.) suffices |
| You need to output a sequence of valid operations | Collect right-to-left; validity is guaranteed by construction |

The last point deserves emphasis. When you collect operations right-to-left, the output sequence (decreasing indices) is exactly a valid execution order — because each operation's precondition holds at the time it would execute. You don't need to separately verify this; the greedy construction guarantees it.

---

## The Running Aggregate Generalises

The parity trick (`k % 2`) is the instance for negation operations. The general principle:

- If the operation **negates**: track parity of $k$.
- If the operation **adds a constant $c$**: track $k \cdot c$ as a running offset.
- If the operation **XORs with $v$**: track XOR of all chosen $v$'s.
- If the operation **multiplies by $m$**: track $m^k \bmod p$.

In each case, the cumulative effect on position $i$ is determined by one running value, not the full history.

---

## Reference Problem

**[We Be Flipping (Hard Version)](https://codeforces.com/contest/2229/problem/C2)**  
*Spectral::Cup 2026 Round 2 (Codeforces Round 1100, Div. 1 + Div. 2) _ C2*

Operation: pick $i$ where $a_i > 0$, then negate $a_1 \ldots a_i$. Minimise final sum.

The right-to-left greedy with parity tracking solves it in $O(n)$.

Clean implementation:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& x : a) cin >> x;

        int k = 0;
        vector<int> flip;
        for (int i = n-1; i >= 0; --i)
            if ((k%2 ? -1 : 1) * a[i] > 0)
                ++k, flip.push_back(i+1);

        cout << k << '\n';
        for (int f : flip) cout << f << ' ';
        cout << '\n';
    }
}
```

**Dry run** — array `[-1, -2, 3, -5, 4]`:

| $i$ | $a[i]$ | $k$ | effective | action |
|---|---|---|---|---|
| 4 | 4 | 0 | +4 | flip at 5, $k=1$ |
| 3 | -5 | 1 | +5 | flip at 4, $k=2$ |
| 2 | 3 | 2 | +3 | flip at 3, $k=3$ |
| 1 | -2 | 3 | +2 | flip at 2, $k=4$ |
| 0 | -1 | 4 | -1 | skip |

Output: `4` ops, indices `5 4 3 2`. Final array: `[-1,-2,-3,-5,-4]`, sum = `-15`.

---

## Practice Problems

| Problem | What to look for |
|---|---|
| [We Be Flipping (Hard Version)](https://codeforces.com/contest/2229/problem/C2) *Spectral::Cup 2026 Round 2 (Codeforces Round 1100, Div. 1 + Div. 2) _ C2*| Same prefix-negate operation, maximise sum instead — identical directional insight |
| [Flip the Bits](https://codeforces.com/problemset/problem/1504/B) *Codeforces Round 712 (Div. 2) _ B*|  Prefix invert with a balance constraint; right-to-left processing fixes each position permanently with a running parity state |

---
