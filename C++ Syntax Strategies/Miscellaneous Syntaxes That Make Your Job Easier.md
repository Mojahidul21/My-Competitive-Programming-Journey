# Miscellaneous Syntaxes That Make Your Job Easier

A running collection of small C++ syntax idioms and standard-library
utilities that are too minor to warrant their own file, but useful
enough to be worth remembering. For deep dives on a single feature
(e.g. lambdas), see standalone articles in this folder instead.

Each entry follows the usual format: Syntax, What it does, Use cases
(each with a worked example), and Notes.

---

<details>
<summary><code>assert</code></summary>

**Syntax:**
```cpp
#include <cassert>
assert(condition);
```

**What it does:**
Terminates the program immediately with an error message if `condition` evaluates to false. Used to enforce invariants during development and stress testing — not left in for correctness of the final logic itself.

**Use case 1 — Sanity-checking stress-test comparisons:**
```cpp
int bruteForceAns = solveBrute(n);
int fastAns = solveFast(n);
assert(bruteForceAns == fastAns);
cout << "Match for n = " << n << ": " << fastAns << endl;
// Output (if they match): Match for n = 7: 42
// If they don't match, program aborts before this line prints —
// telling you immediately which n breaks your fast solution.
```

**Use case 2 — Catching invalid array access early:**
```cpp
int arr[5] = {10, 20, 30, 40, 50};
int index = 7;
assert(index >= 0 && index < 5);
cout << arr[index] << endl;
// Program aborts on the assert line, since index = 7 is out of bounds.
// Terminal shows something like:
// Assertion failed: index >= 0 && index < 5, file main.cpp, line 3
```

**Use case 3 — Verifying a loop invariant while debugging:**
```cpp
int sum = 0;
for (int i = 1; i <= 5; i++) {
    sum += i;
    assert(sum > 0); // invariant: running sum should never go negative here
}
cout << "Final sum: " << sum << endl;
// Output: Final sum: 15
```

**Notes:**
- Disabled entirely if `NDEBUG` is defined (some judges compile with optimizations that strip asserts — don't rely on it as runtime validation for submitted logic)
- Cheap during local testing, effectively free once compiled out
- Different from throwing exceptions — `assert` is a debugging tool, not a control-flow mechanism

**Related:** Invariant, Stress Testing

</details>

<details>
<summary><code>fill</code></summary>

**What it does:**
Sets every element in a range to a given value in one call, replacing manual loops like `for (int i = 0; i < n; i++) arr[i] = value;`.

**Variant 1 — Plain array:**
```cpp
int arr[5] = {1, 2, 3, 4, 5};
fill(arr, arr + 5, 0);

for (int i = 0; i < 5; i++) cout << arr[i] << " ";
// Output: 0 0 0 0 0
```

**Variant 2 — `vector`:**
```cpp
vector<int> v = {1, 2, 3, 4, 5};
fill(v.begin(), v.end(), -1);

for (int x : v) cout << x << " ";
// Output: -1 -1 -1 -1 -1
```

**Variant 3 — Flattened 2D array:**
```cpp
int grid[2][3] = {{1, 2, 3}, {4, 5, 6}};
fill(grid[0], grid[0] + 2 * 3, 9);

for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) cout << grid[i][j] << " ";

    cout<<endl;
}

/*

Output:
9 9 9
9 9 9

*/
```

**Use case — Resetting a visited array between test cases:**
```cpp
bool visited[5];
fill(visited, visited + 5, false);
// visited is now {false, false, false, false, false},
// ready to reuse in the next test case without re-declaring the array.
```

**Use case — Initializing a DP array to a sentinel value:**
```cpp
int dp[6];
fill(dp, dp + 6, -1); // -1 marks "not computed yet"
cout << dp[3] << endl;
// Output: -1  (signals memoization should compute this state)
```

**Notes:**
- Header: `<algorithm>`
- For 2D arrays, `memset` is often faster but only safe for `0`, `-1`, or byte-repeatable values; `fill` works correctly for any value type.
- `fill_n(arr, count, value)` is the variant when you know a count rather than an end iterator.

**Related:** Memset, Vector Initialization

</details>
