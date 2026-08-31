# Miscellaneous Syntaxes That Make Your Job Easier

A running collection of small C++ syntax idioms and standard-library
utilities that are too minor to warrant their own file, but useful
enough to be worth remembering. For deep dives on a single feature
(e.g. lambdas), see standalone articles in this folder instead.

Each entry follows the usual format: Syntax, What it does, Use cases,
Notes, and Related.

---

<details>
<summary>▶ <code>assert</code></summary>

**Syntax:**
```cpp
#include <cassert>
assert(condition);
```

**What it does:**
Terminates the program immediately with an error message if `condition` evaluates to false. Used to enforce invariants during development and stress testing — not left in for correctness of the final logic itself.

**Use cases:**
- Sanity-checking assumptions while stress-testing brute force vs. optimized solutions
- Catching invalid states early (e.g., `assert(index >= 0 && index < n);` before an array access)
- Verifying loop invariants or preconditions while debugging a tricky implementation

**Notes:**
- Disabled entirely if `NDEBUG` is defined (some judges compile with optimizations that strip asserts — don't rely on it as runtime validation for submitted logic)
- Cheap during local testing, effectively free once compiled out
- Different from throwing exceptions — `assert` is a debugging tool, not a control-flow mechanism

**Related:** Invariant, Stress Testing

</details>

<details>
<summary>▶ <code>fill</code></summary>

**Syntax:**
```cpp
fill(arr, arr + n, value);
fill(v.begin(), v.end(), value);
fill(grid[0], grid[0] + rows * cols, value); // flattened 2D array
```

**What it does:**
Sets every element in a range to a given value in one call, replacing manual loops like `for (int i = 0; i < n; i++) arr[i] = value;`.

**Use cases:**
- Resetting a visited/marked array between test cases
- Initializing a DP array to a sentinel value (e.g., `fill(dp, dp + n, -1);` before memoization)
- Clearing adjacency/frequency arrays without reallocating

**Notes:**
- Header: `<algorithm>`
- For 2D arrays, `memset` is often faster but only safe for `0`, `-1`, or byte-repeatable values; `fill` works correctly for any value type.
- `fill_n(arr, count, value)` is the variant when you know a count rather than an end iterator.

**Related:** Memset, Vector Initialization

</details>
