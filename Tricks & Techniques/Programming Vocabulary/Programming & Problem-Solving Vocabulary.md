# Programming & Problem-Solving Vocabulary

A living reference of terms used in competitive programming, debugging, and algorithmic thinking. Each entry includes a definition, real-world analogy (where helpful), and C++ code illustration. New entries will be added as those are encountered further.

---

## Table of Contents

- [Short-Circuit Evaluation](#short-circuit-evaluation)
- [Fragile Code](#fragile-code)
- [Robust Code](#robust-code)
- [Reduction](#reduction)
- [Undefined Behavior (UB)](#undefined-behavior-ub)
- [Edge Case](#edge-case)
- [Invariant](#invariant)
- [Contiguous / Contiguous Block](#contiguous--contiguous-block)
- [Anchor](#anchor)
- [Latent Bug](#latent-bug)
- [Guard / Guard Clause](#guard--guard-clause)
- [Overhead](#overhead)

---

## Short-Circuit Evaluation

**Definition:**
In a logical expression (`&&` or `||`), if the result is already determined by the left operand, the right operand is never evaluated — not even executed.

- `A && B` → if `A` is false, `B` is skipped (result is already false)
- `A || B` → if `A` is true, `B` is skipped (result is already true)

**Why it matters in CP:**
The right operand may cause UB, a crash, or expensive computation. Short-circuiting lets you guard against it in a single expression.

**Example from practice:**
```cpp
// If indices is empty, .back() and .front() are never called — no UB
indices.size() && indices.back() - indices.front() - (int)indices.size() + 1
```

```cpp
// Standard guard pattern with short-circuit
if (!v.empty() && v[0] == target) { ... }
// If v is empty, v[0] is never accessed
```

```cpp
// OR short-circuit: if first condition is true, second is skipped
if (n == 0 || arr[0] == -1) return;
```

**Analogy:**
A security check at a gate — if the first guard says "no entry", the second guard is never even consulted.

---

## Fragile Code

**Definition:**
Code that produces the correct output for current inputs but breaks under slightly different conditions — correct by accident, not by design. There is no clear reason it should work; it just happens to.

**Signs of fragility:**
- Works on given test cases but has no proof of correctness
- Relies on constraints that aren't explicitly guaranteed
- A small change in input breaks it

**Example:**
```cpp
// Fragile: assumes the vector is always non-empty
cout << v.back();

// What happens if v is empty? UB / crash
```

```cpp
// Fragile: assumes sorted input, but sort wasn't called
int mn = a[0]; // wrong if the first element is not really the minimum
```

**Contrast with robust code:** Fragile code passes; robust code passes *and* you can prove why.

**In contest context:**
A solution is fragile if it passes the given examples and even the judge, but you cannot explain *why* it's correct. It may fail on a future problem with similar structure but slightly different constraints.

---

## Robust Code

**Definition:**
Code that is correct for all valid inputs, including edge cases, because it is built on a clear, provable reason — not coincidence.

**Example:**
```cpp
// Robust: guarded before access
if (!v.empty()) cout << v.back();
```

```cpp
// Robust: works regardless of whether indices is empty
if (indices.empty()) { cout << "YES\n"; }
else {
    bool contiguous = indices.back() - indices.front() == (int)indices.size() - 1;
    cout << (contiguous ? "YES" : "NO") << '\n';
}
```

**Goal in CP:** Even under contest time pressure, prefer robust over fragile whenever the proof of correctness is simple.

---

## Reduction

**Definition:**
Transforming a complex or unfamiliar problem into a simpler or already-solved one, so that solving the simpler problem solves the original.

**Why it's powerful:**
Instead of solving a hard problem directly, you recognize it as a disguised version of something you already know.

**Example from practice:**
There are exactly two alternating strings over `{a, b}`. Instead of checking both, anchor on `s[0]` to reduce to one check:
```cpp
// Reduction: 2 pattern checks → 1, by anchoring on s[0]
string sss{s[0] != 'a' ? "ba" : "ab"};
```
`s[0]` is guaranteed to match `sss[0]`, so no mismatch at index 0 — and only one pattern needs checking.

**Classic CP reductions:**
- "Can we make all elements equal?" → prefix sum / parity check
- "Minimum swaps to sort" → cycle detection in permutation graph
- "Longest common substring" → suffix array / LCP array

---

## Undefined Behavior (UB)

**Definition:**
Code for which the C++ standard makes *no guarantees*. The program may crash, give wrong output, appear to work, corrupt memory, or do anything else — the compiler is allowed to assume UB never happens and may optimize accordingly in dangerous ways.

**Common sources in CP:**
```cpp
vector<int> v;
v.back();              // UB — empty vector
v[5];                  // UB — out of bounds (no bounds check with [])

int x = INT_MAX;
x + 1;                 // UB — signed integer overflow (use long long)

int a[5];
a[5] = 0;              // UB — one past the end

int* p = nullptr;
*p = 1;                // UB — null pointer dereference
```

**Dangerous property:**
UB may not crash or give wrong answers on your machine or on valid test cases — it can be a latent bug that surfaces only in specific conditions (different OS, compiler version, or input).

**Rule of thumb:** If you're not 100% sure an access is in bounds, guard it.

---

## Edge Case

**Definition:**
An input at the extreme boundary of the constraints where typical logic behaves differently or breaks entirely.

**Common edge cases in CP:**

| Scenario | Example |
|---|---|
| Empty container | `n = 0`, empty string |
| Single element | `n = 1` |
| All elements equal | `[5, 5, 5, 5]` |
| Maximum constraints | `n = 2 * 10^5` |
| Already sorted | `[1, 2, 3, 4]` |
| Reverse sorted | `[4, 3, 2, 1]` |
| All same character | `"aaaa"` |
| Answer is zero or negative | Result = 0, -1 |

**Example from practice:**
```cpp
// Edge case: indices is empty means s is already alternating
if (indices.empty()) { cout<<"yes"; }
else { indices.back() - indices.front() - (int)indices.size() + 1 ? cout<<"no" : cout<<"yes"; }
```

**Habit to build:** Before submitting, mentally run through: what if `n = 1`? What if all elements are the same? What if the answer is 0?

---

## Invariant

**Definition:**
A condition that is guaranteed to remain true throughout an algorithm's execution. You reason about the algorithm by identifying and relying on invariants at each step.

**Why it matters:**
Invariants are the backbone of correctness proofs. If you can state an invariant clearly, you can trust the code.

**Example:**
```cpp
// Invariant: indices is always in increasing order
// because we insert left-to-right (i = 0, 1, 2, ...)
for (int i{}; i < n; ++i)
    if (s[i] != ss[i])
        indices.emplace_back(i);

// Because of this invariant, front() = min, back() = max — always.
```

**Classic invariants in CP:**
- Binary search: `lo <= ans <= hi` at every step
- Two pointers: left pointer never passes right pointer
- Segment tree: each node stores the correct aggregate for its range

---

## Contiguous / Contiguous Block

**Definition:**
A sequence of elements occupying consecutive positions with no gaps between them.

**In the context of indices:**
A set of indices `{i1, i2, ..., ik}` (sorted) is contiguous if and only if:
```
i_k - i_1 == k - 1
```
Equivalently: `back - front == size - 1`, or `back - front - size + 1 == 0`.

**Example from practice:**
```cpp
// Check if mismatch indices form a contiguous block
// If yes: one substring operation covers all of them → YES
// If no: gaps exist between mismatches → NO single operation suffices
indices.back() - indices.front() - (int)indices.size() + 1
// == 0 → contiguous (YES)
// > 0 → gaps exist (NO)
```

**Analogy:**
A row of broken tiles on a floor — if all broken tiles are side by side, one repair strip covers them all. If they're scattered, you need multiple strips.

---

## Anchor

**Definition:**
A fixed reference point around which the rest of the logic is built. Choosing an anchor eliminates degrees of freedom and simplifies the problem.

**Example from practice:**
```cpp
// s[0] is the anchor: we fix the target pattern to agree with s[0]
// This eliminates the need to check both "ab..." and "ba..." patterns
string sss{s[0] != 'a' ? "ba" : "ab"};
```
Because `sss[0] == s[0]` always, index 0 is never a mismatch — the anchor holds the pattern in place.

**Other examples of anchoring in CP:**
- Fix the first element and determine the rest (greedy)
- Fix the root in tree DP
- Fix one endpoint of a range and binary search the other

---

## Latent Bug

**Definition:**
A bug that exists in the code but does not trigger on current test cases. It is hidden until a specific input or environment exposes it.

**Why it's dangerous:**
It gets AC on the judge, passes code review, and is committed — then fails silently in a different context (stress test, different OS, compiler with different padding behavior).

**Example from practice:**
Reading one element past a heap-allocated vector's end:
```cpp
vector<int> v(n);
cout << v[n]; // UB — but may silently return 0 due to OS page padding
```
This passes all valid test cases because the OS fills that memory region with zeros. The bug is latent — real, but invisible.

**How to find latent bugs:**
- Stress testing against a brute force
- Running with sanitizers: `-fsanitize=address,undefined`
- Manually testing edge cases

---

## Guard / Guard Clause

**Definition:**
A check placed before potentially unsafe or incorrect code to ensure preconditions are met before execution proceeds.

**Purpose:** Prevent UB, wrong answers, or crashes caused by operating on invalid state.

**Patterns:**
```cpp
// Guard with early return
if (v.empty()) return;
cout << v.back(); // safe now

// Guard with short-circuit in expression
v.size() && v.back() == target

// Guard with early output (CP style)
if (indices.empty()) { pye }
else { /* safe to use front/back */ }
```

**Analogy:**
A safety lock — you check the condition before pulling the trigger. The gun (code) is fine; the guard ensures you don't fire when you shouldn't.

---

## Overhead

**Definition:**
Extra time, memory, or code complexity beyond the minimum required to solve the problem.

**In CP:** Overhead matters when you're close to the time or memory limit.

**Examples:**
```cpp
// O(log n) overhead per insertion — set maintains sorted order
set<int> s;
s.insert(x);

// O(1) amortized — no overhead from sorting/balancing
vector<int> v;
v.push_back(x);
```

```cpp
// Overhead from unnecessary copy
void f(vector<int> v) { ... }   // copies entire vector

// No overhead — pass by const reference
void f(const vector<int>& v) { ... }
```

**Types of overhead:**
- **Time overhead:** Extra operations that increase runtime (e.g., unnecessary sorting, repeated computation)
- **Memory overhead:** Extra space used beyond what's needed (e.g., storing full strings when only lengths are needed)
- **Code overhead:** Unnecessary complexity that makes code harder to read and debug

---
