# Miscellaneous Syntaxes That Make Your Job Easier

A running collection of small C++ syntax idioms and standard-library
utilities that are too minor to warrant their own file, but useful
enough to be worth remembering. For deep dives on a single feature
(e.g. lambdas), see standalone articles in this folder instead.

Each entry follows the usual format: Syntax, What it does, Use cases
(each with a worked example), and Notes.

---

<details>
<summary>Assert</summary>

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

___

<details>
<summary>Boolalpha</summary>

**Syntax:**
```cpp
#include <iostream>
cout << boolalpha;   // print bools as "true" / "false"
cout << noboolalpha; // back to 1 / 0 (the default)
```

**What it does:**
By default, `cout` prints a `bool` as `1` or `0`. `boolalpha` is a stream manipulator that switches the stream to print the words `true` and `false` instead. It also changes how `cin` reads: with `boolalpha` set, input must be the literal words `true` or `false`.

**Use case 1 — Printing the result of a comparison:**
```cpp
cout << (3 < 5) << endl;
// Output: 1

cout << boolalpha << (3 < 5) << endl;
// Output: true
```

**Use case 2 — Readable debug output for predicates:**
```cpp
bool isPrime(int n) {
    if (n < 2) return false;
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0) return false;
    return true;
}

int main() {
    cout << boolalpha;
    cout << "isPrime(1)  = " << isPrime(1) << endl;
    cout << "isPrime(7)  = " << isPrime(7) << endl;
    cout << "isPrime(12) = " << isPrime(12) << endl;
}
// Output:
// isPrime(1)  = false
// isPrime(7)  = true
// isPrime(12) = false
```

**Use case 3 — It is sticky until you turn it off:**
```cpp
cout << boolalpha;
cout << true << " " << false << endl;
// Output: true false

cout << noboolalpha;
cout << true << " " << false << endl;
// Output: 1 0
```

**Use case 4 — Reading `true` / `false` from input:**
```cpp
bool a, b;
cin >> boolalpha >> a >> b;   // input: true false
cout << boolalpha << a << " " << b << endl;
// Output: true false
// With input "1 0" instead, extraction fails (failbit is set)
// because boolalpha input only accepts the words.
```

**Use case 5 — Only `bool` is affected, not `int`:**
```cpp
cout << boolalpha;
cout << 1 << " " << true << endl;
// Output: 1 true
// The int 1 is still printed as a number;
// only values of type bool are printed as words.
```

**Notes:**
- Header: `<iostream>` (the flag itself lives in `<ios>`, which it includes)
- The setting is **sticky**: it stays on for that stream until you apply `noboolalpha`
- Equivalent flag form: `cout.setf(ios::boolalpha);` and `cout.unsetf(ios::boolalpha);`
- Prints lowercase `true` / `false`. If a problem wants `YES` / `NO` or `Yes` / `No`, use a ternary instead: `cout << (ok ? "YES" : "NO");`
- Mostly a debugging and readability aid. Judges almost never expect `true` / `false` in the output, so check the statement before leaving it in a submission
- Applies to `cin` as well, and once it is set, `1` / `0` are no longer accepted as bool input

**Related:** Assert, Ternary Operator

</details>

___

<details>
<summary>Comma Operator as Conditional</summary>

**What it does:** Chains two expressions with `,`, evaluating left-to-right and discarding the left result. Combined with short-circuit `&&`, it fakes an `if` statement inside a single expression.

```cpp
cin >> j, i != j && (a.emplace_back(j), true);
```

Equivalent to:

```cpp
cin >> j;
if (i != j) {
    a.emplace_back(j);
}
```

**How it works:** `i != j && (a.emplace_back(j), true)` short-circuits — if `i != j` is false, the right side never evaluates, so `emplace_back` never runs. The trailing `, true` exists only so the parenthesized expression has a `bool`-compatible result for `&&` to operate on; `emplace_back`'s own return value (a reference) isn't usable there directly.

**`true` vs `false`:** the trailing value is cosmetic when the whole statement is discarded (as above) — `(a.emplace_back(j), false)` runs `emplace_back` identically, since the comma operator always evaluates the left side regardless of what the right side is. `true` is just the conventional choice, signaling "this branch succeeded" for anyone skimming; it only matters functionally if the outer expression's *value* is itself used somewhere (e.g. nested in a larger condition).

**Output demonstration:**

```cpp
int i = 3, j = 5;
vector<int> a;
cin >> j, i != j && (a.emplace_back(j), true);
// a now contains {5}, since i != j

i = 5, j = 5;
cin >> j, i != j && (a.emplace_back(j), true);
// a unchanged — i == j, right side short-circuits away
```

> [!WARNING]
> This is a **code-golf idiom**, not a house-style recommendation. It buries a side effect (`emplace_back`) inside what looks like a boolean expression, which trades readability for terseness.

</details>

___

<details>
<summary>Fill</summary>

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

for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j)
        cout << grid[i][j] << " ";

    cout << endl;
}

/*
Output:
9 9 9
9 9 9
*/
```

**Variant 4 — `fill_n` (count instead of an end iterator):**
```cpp
int arr[5] = {1, 2, 3, 4, 5};
fill_n(arr, 3, 0); // fill the first 3 elements only

for (int i = 0; i < 5; i++) cout << arr[i] << " ";
// Output: 0 0 0 4 5
// Only the first 3 positions were overwritten — fill_n stops
// after `count` elements rather than needing an end iterator.
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
- See Variant 4 above for `fill_n`, useful when you know a count rather than an end iterator.

**Related:** Memset, Vector Initialization

</details>
