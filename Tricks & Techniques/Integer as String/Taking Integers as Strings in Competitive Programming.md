# Taking Integers as Strings in Competitive Programming

> **Author:** Ace_Azimuth_Aviator  
> **Tags:** `strings` `implementation` `digit-manipulation` `big-numbers` `tricks`  
> **Difficulty scope:** Beginner → Intermediate

---

## Table of Contents

1. [Why This Trick Exists](#1-why-this-trick-exists)
2. [When You Must Use It](#2-when-you-must-use-it)
3. [When It Simply Makes Life Easier](#3-when-it-simply-makes-life-easier)
4. [Core Operations on a Digit String](#4-core-operations-on-a-digit-string)
5. [Conversion Cheatsheet](#5-conversion-cheatsheet)
6. [Patterns and Code Templates](#6-patterns-and-code-templates)
   - 6.1 [Arbitrarily Large Numbers](#61-arbitrarily-large-numbers)
   - 6.2 [Leading Zeros](#62-leading-zeros)
   - 6.3 [Digit-by-Digit Traversal](#63-digit-by-digit-traversal)
   - 6.4 [Comparing Two Huge Numbers](#64-comparing-two-huge-numbers)
   - 6.5 [Palindrome Check on a Number](#65-palindrome-check-on-a-number)
   - 6.6 [Digit Sum and Digit Product](#66-digit-sum-and-digit-product)
   - 6.7 [Inserting / Deleting / Replacing Digits](#67-inserting--deleting--replacing-digits)
   - 6.8 [Next Permutation of Digits](#68-next-permutation-of-digits)
7. [Gotchas to Avoid](#7-gotchas-to-avoid)
8. [Practice Problems](#8-practice-problems)

---

## 1. Why This Trick Exists

C++ integer types have hard ceilings:

| Type | Max value |
|------|-----------|
| `int` | ~2 × 10⁹ |
| `long long` | ~9.2 × 10¹⁸ |
| `unsigned long long` | ~1.8 × 10¹⁹ |
| `__int128` | ~1.7 × 10³⁸ |

The moment a problem says *"N can be up to 10^100"* or asks you to work on the **digits themselves** — their order, count, identity — a numeric type is either impossible or inconvenient. A `string` sidesteps the overflow ceiling entirely and gives you O(1) index access to every digit.

---

## 2. When You Must Use It

These situations leave **no alternative** — a numeric type simply cannot represent the input:

**2.1 Numbers larger than `__int128`**

Any number with more than ~39 digits. Problems sometimes give numbers with 10⁵ digits.

```
Input: 99999999999999999999999999999999999999999999999999
```

Reading this as `long long` silently wraps around. Reading it as `string s` is trivial.

**2.2 Numbers with significant leading zeros**

`007`, `000123`, `0` itself. If read as an integer, leading zeros vanish. As a string they are preserved — and the problem may depend on them entirely (e.g., *"count how many leading zeros the number has"*).

```cpp
string s;
cin >> s;
int leading = 0;
for (char c : s) {
    if (c == '0') leading++;
    else break;
}
```

**2.3 The number itself is the sequence of digits**

Problems that ask: *"rearrange the digits to form the largest/smallest number"*, *"remove exactly one digit to minimise the result"*, *"is this number a palindrome"* — these operate on the digit sequence, not the arithmetic value.

---

## 3. When It Simply Makes Life Easier

Even when `long long` fits, strings can be more ergonomic:

- Checking if a number has a specific digit pattern.
- Iterating from the most significant to least significant digit without reversing.
- Counting occurrences of a particular digit.
- Simulating addition/multiplication column-by-column (big integer arithmetic).
- Lexicographic comparison that coincides with numeric comparison (same-length, no leading zeros).

---

## 4. Core Operations on a Digit String

```cpp
string s;
cin >> s;

int n = s.size();           // number of digits

// Access digit i as a character
char c = s[i];

// Access digit i as an integer  (subtract '0')
int d = s[i] - '0';

// Convert the entire string to long long  (only if it fits)
long long val = stoll(s);

// Convert long long back to string
string t = to_string(val);

// Reverse the digit string  (useful for least-significant-first processing)
reverse(s.begin(), s.end());

// Lexicographic compare  ==  numeric compare  when lengths are equal and no leading zeros
bool bigger = (s > t);  // true if s represents a larger number than t
```

---

## 5. Conversion Cheatsheet

| Goal | Code |
|------|------|
| `string` → `int` | `stoi(s)` |
| `string` → `long long` | `stoll(s)` |
| `string` → `double` | `stod(s)` |
| `int` / `long long` → `string` | `to_string(x)` |
| Single char digit → `int` | `c - '0'` |
| Single `int` digit → `char` | `'0' + d` |
| Single `int` digit → `string` | `string(1, '0' + d)` |

---

## 6. Patterns and Code Templates

### 6.1 Arbitrarily Large Numbers

Read two huge numbers, print them back, compute digit sum.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string a, b;
        cin >> a >> b;

        int sum = 0;
        for (char c : a) sum += c - '0';

        cout << a << ' ' << b << ' ' << sum << '\n';
    }
    return 0;
}
```

### 6.2 Leading Zeros

Count leading zeros; strip them safely.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;

        int lz = 0;
        for (char c : s) {
            if (c == '0') lz++;
            else break;
        }

        // strip leading zeros (keep at least "0")
        int i = 0;
        while (i < (int)s.size() - 1 && s[i] == '0') i++;
        string stripped = s.substr(i);

        cout << lz << ' ' << stripped << '\n';
    }
    return 0;
}
```

### 6.3 Digit-by-Digit Traversal

Process most-significant digit first — natural with a string, awkward with an integer.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string s;
        int m;
        cin >> s >> m;

        // running numeric value modulo m as we read left to right
        long long cur = 0;
        for (char c : s)
            cur = (cur * 10 + (c - '0')) % m;

        cout << cur << '\n';
    }
    return 0;
}
```

> This is the canonical way to compute `N mod m` when N doesn't fit in any integer type.

### 6.4 Comparing Two Huge Numbers

When both numbers may exceed `long long`, numeric comparison is impossible. String comparison works if we handle length first.

```cpp
// returns  1 if a > b
// returns -1 if a < b
// returns  0 if equal
// assumes no leading zeros
int cmpBig(const string& a, const string& b) {
    if (a.size() != b.size())
        return a.size() > b.size() ? 1 : -1;
    if (a == b) return 0;
    return a > b ? 1 : -1;
}
```

### 6.5 Palindrome Check on a Number

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        string r = s;
        reverse(r.begin(), r.end());
        cout << (s == r ? "YES" : "NO") << '\n';
    }
    return 0;
}
```

### 6.6 Digit Sum and Digit Product

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;

        long long dsum = 0, dprod = 1;
        for (char c : s) {
            int d = c - '0';
            dsum += d;
            dprod *= d;
        }
        cout << dsum << ' ' << dprod << '\n';
    }
    return 0;
}
```

### 6.7 Inserting / Deleting / Replacing Digits

```cpp
string s = "12345";

// delete digit at position i
s.erase(i, 1);

// insert digit d at position i
s.insert(i, 1, '0' + d);

// replace digit at position i
s[i] = '0' + d;

// append a digit
s += ('0' + d);
```

**Classic problem pattern** — *"Remove exactly one digit to make the number as small as possible"*:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();

        int pos = n - 1;                               // default: remove last digit
        for (int i = 0; i < n - 1; i++) {
            if (s[i] > s[i + 1]) { pos = i; break; }  // first descent
        }
        s.erase(pos, 1);

        // strip leading zeros
        int i = 0;
        while (i < (int)s.size() - 1 && s[i] == '0') i++;
        cout << s.substr(i) << '\n';
    }
    return 0;
}
```

### 6.8 Next Permutation of Digits

Gives the next larger number using the same digits. STL works directly on strings.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        if (next_permutation(s.begin(), s.end()))
            cout << s << '\n';
        else
            cout << -1 << '\n';   // already the largest permutation
    }
    return 0;
}
```

---

## 7. Gotchas to Avoid

| Mistake | Problem | Fix |
|---------|---------|-----|
| `stoi` / `stoll` on a 50-digit string | Runtime exception / overflow | Only convert if `s.size() <= 18` and no leading zeros |
| Comparing strings of different lengths directly | `"9" > "12"` is true lexicographically but false numerically | Compare lengths first, then lexicographically |
| Forgetting `s[i] - '0'` | `s[i]` is a `char`, arithmetic on it gives ASCII values | Always subtract `'0'` to get the digit value |
| Not handling the `"0"` edge case when stripping leading zeros | `"000"` becomes `""` | Stop stripping at `size - 1` |
| Assuming `cin >> s` skips non-digit characters | It just reads until whitespace | Validate the string if the input may contain noise |

---

## 8. Practice Problems

| Problem | What it teaches |
|---------|----------------|
| [Codeforces 281A — Word Capitalization](https://codeforces.com/problemset/problem/281/A) | Basic char manipulation |
| [Codeforces 768B — Code For 1](https://codeforces.com/problemset/problem/768/B) | Recursion on digit string of huge number |
| [Codeforces 791B — Bear and Prime 100](https://codeforces.com/problemset/problem/791/B) | Digit-level number reasoning |
| [Codeforces 1202C — You Are Given a WASD String...](https://codeforces.com/problemset/problem/1202/C) | String + logic, no numeric conversion needed |
| [SPOJ VFMUL](https://www.spoj.com/problems/VFMUL/) | Big integer arithmetic via strings |

---

## Summary

```
Use string input for a number when:
  ├── it exceeds long long (> ~9.2 × 10¹⁸)
  ├── leading zeros are meaningful
  ├── you need to operate on individual digits
  ├── you need to rearrange / insert / delete digits
  └── comparison is positional or lexicographic
```

The core insight is simple: **a number is just a string of digit characters**, and once you internalize that, an entire class of problems that look numeric become string problems — often far easier to implement correctly.

---

*Happy Coding — Ace_Azimuth_Aviator*
