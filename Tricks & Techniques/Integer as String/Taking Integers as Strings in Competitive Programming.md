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
   - 6.3 [Digit-by-Digit Traversal & N mod m](#63-digit-by-digit-traversal--n-mod-m)
   - 6.4 [Comparing Two Huge Numbers](#64-comparing-two-huge-numbers)
   - 6.5 [Palindrome Check on a Number](#65-palindrome-check-on-a-number)
   - 6.6 [Digit Sum and Digit Product](#66-digit-sum-and-digit-product)
   - 6.7 [Digit Frequency Count](#67-digit-frequency-count)
   - 6.8 [Inserting / Deleting / Replacing Digits](#68-inserting--deleting--replacing-digits)
   - 6.9 [Next Permutation of Digits](#69-next-permutation-of-digits)
   - 6.10 [Sorting Digits — Smallest and Largest Number](#610-sorting-digits--smallest-and-largest-number)
   - 6.11 [Big Integer Addition](#611-big-integer-addition)
7. [Gotchas to Avoid](#7-gotchas-to-avoid)
8. [Practice Problems](#8-practice-problems)

---

## 1. Why This Trick Exists

C++ integer types have hard ceilings:

| Type | Max value | Max digits |
|------|-----------|------------|
| `int` | ~2 × 10⁹ | 10 |
| `long long` | ~9.2 × 10¹⁸ | 19 |
| `unsigned long long` | ~1.8 × 10¹⁹ | 20 |
| `__int128` | ~1.7 × 10³⁸ | 39 |

The moment a problem says *"N can be up to 10^100"* or asks you to work on the **digits themselves** — their order, count, or identity — a numeric type is either impossible or inconvenient. A `string` sidesteps the overflow ceiling entirely and gives you O(1) index access to every single digit.

---

## 2. When You Must Use It

These situations leave **no alternative** — a numeric type simply cannot represent the input:

**2.1 Numbers larger than `__int128`**

Any number exceeding ~39 digits. Problems sometimes give numbers with up to 10⁵ digits.

```
Input: 99999999999999999999999999999999999999999999999999
```

Reading this as `long long` silently wraps around and gives a completely wrong value. Reading it as `string s` is trivial and perfectly safe.

**2.2 Numbers with significant leading zeros**

`007`, `000123`, `0000` — if read as an integer, leading zeros vanish completely. As a string they are preserved, and the problem may depend on them entirely.

```
Input: 000732
As int   →  732      (leading zeros lost forever)
As string → "000732" (preserved exactly)
```

**2.3 The number is really a sequence of digits**

Problems that ask: *"rearrange the digits to form the largest number"*, *"remove exactly one digit to minimise the result"*, *"is this number a palindrome"* — these are fundamentally about the digit sequence, not the arithmetic value. Treating them as integers only creates unnecessary complexity.

---

## 3. When It Simply Makes Life Easier

Even when `long long` would fit, a string is often the cleaner choice:

- Iterating from the **most significant digit first** — natural with a string index, awkward with integer division.
- Counting occurrences of a specific digit in O(n).
- Checking digit patterns without any arithmetic.
- Computing `N mod m` for a huge N without storing N at all (see §6.3).
- Simulating big integer arithmetic column-by-column (see §6.11).

---

## 4. Core Operations on a Digit String

```cpp
string s;
cin >> s;

int n = s.size();                 // total number of digits

char c  = s[i];                   // digit i as a character  e.g. '7'
int  d  = s[i] - '0';             // digit i as an integer   e.g.  7

long long val = stoll(s);         // whole string → long long  (only if it fits!)
string    t   = to_string(val);   // long long → string

reverse(s.begin(), s.end());      // reverse digit order (LSB-first processing)

bool bigger = (s > t);            // lexicographic == numeric when same length, no leading zeros
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

---

### 6.1 Arbitrarily Large Numbers

Read a huge number and compute its digit sum — no overflow possible.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    long long digitSum = 0;
    for (char c : s)
        digitSum += c - '0';

    cout << "Number   : " << s << "\n";
    cout << "Digit sum: " << digitSum << "\n";

    return 0;
}
```

---

### 6.2 Leading Zeros

Count leading zeros and strip them safely.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    // count leading zeros
    int lz = 0;
    for (char c : s) {
        if (c == '0') lz++;
        else break;
    }

    // strip leading zeros — always keep at least one digit
    int i = 0;
    while (i < (int)s.size() - 1 && s[i] == '0') i++;
    string stripped = s.substr(i);

    cout << "Leading zeros : " << lz << "\n";
    cout << "Stripped      : " << stripped << "\n";

    return 0;
}
```

**Edge cases handled:**
- `"000"` → strips to `"0"`, not `""`
- `"007"` → strips to `"7"`, leading zeros = 2

---

### 6.3 Digit-by-Digit Traversal & N mod m

Process the most significant digit first — the natural direction for a string index.

The most powerful application: computing `N mod m` when N is too large for any integer type.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int m;
    cin >> s >> m;

    // Horner's method: read left to right, accumulate modulo
    long long result = 0;
    for (char c : s)
        result = (result * 10 + (c - '0')) % m;

    cout << s << " mod " << m << " = " << result << "\n";

    return 0;
}
```

**Why this works:**  
`N = d₀×10^(k) + d₁×10^(k-1) + ... + dₖ`  
Reading left to right: `result = result × 10 + dᵢ`  
Since `(a + b) mod m = ((a mod m) + b) mod m`, intermediate results never overflow `long long`.

---

### 6.4 Comparing Two Huge Numbers

Direct numeric comparison is impossible when numbers exceed `long long`. String comparison works correctly with one rule: **compare lengths first**.

```cpp
#include <bits/stdc++.h>
using namespace std;

// Returns  1 if a > b
// Returns -1 if a < b
// Returns  0 if equal
// Assumes no leading zeros in either string
int cmpBig(const string& a, const string& b) {
    if (a.size() != b.size())
        return a.size() > b.size() ? 1 : -1;
    if (a == b) return 0;
    return a > b ? 1 : -1;
}

int main() {
    string a, b;
    cin >> a >> b;

    int res = cmpBig(a, b);
    if      (res ==  1) cout << a << " is greater\n";
    else if (res == -1) cout << b << " is greater\n";
    else                cout << "Equal\n";

    return 0;
}
```

**Why length must come first:**  
Lexicographically `"9" > "12"` is true, but numerically 9 < 12. Length resolves this.

---

### 6.5 Palindrome Check on a Number

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    string r = s;
    reverse(r.begin(), r.end());

    cout << (s == r ? "Palindrome" : "Not a palindrome") << "\n";

    return 0;
}
```

Works correctly for numbers of any size, including those far beyond `long long`.

---

### 6.6 Digit Sum and Digit Product

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    long long dsum = 0, dprod = 1;
    for (char c : s) {
        int d = c - '0';
        dsum  += d;
        dprod *= d;
    }

    cout << "Digit sum    : " << dsum  << "\n";
    cout << "Digit product: " << dprod << "\n";

    return 0;
}
```

> **Note:** Digit product becomes 0 as soon as any digit is 0 — a useful early-exit condition in many problems.

---

### 6.7 Digit Frequency Count

Count how many times each digit 0–9 appears.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int freq[10] = {};           // freq[d] = count of digit d
    for (char c : s)
        freq[c - '0']++;

    for (int d = 0; d <= 9; d++)
        if (freq[d])
            cout << "Digit " << d << " appears " << freq[d] << " time(s)\n";

    return 0;
}
```

**Common uses:**
- Check if a number is a permutation of another number.
- Find the most/least frequent digit.
- Anagram-style digit problems.

---

### 6.8 Inserting / Deleting / Replacing Digits

```cpp
string s = "12345";

s.erase(i, 1);              // delete digit at position i
s.insert(i, 1, '0' + d);    // insert digit d at position i
s[i] = '0' + d;             // replace digit at position i
s += ('0' + d);             // append digit d at the end
s = string(1, '0'+d) + s;   // prepend digit d at the front
```

**Classic pattern — remove exactly one digit to get the smallest possible number:**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    // Find the first position where a digit is greater than the next
    int pos = n - 1;                               // default: remove last digit
    for (int i = 0; i < n - 1; i++) {
        if (s[i] > s[i + 1]) { pos = i; break; }  // first descent point
    }
    s.erase(pos, 1);

    // Strip any newly created leading zeros
    int i = 0;
    while (i < (int)s.size() - 1 && s[i] == '0') i++;

    cout << s.substr(i) << "\n";

    return 0;
}
```

---

### 6.9 Next Permutation of Digits

Gives the next larger number that uses the exact same digits. STL's `next_permutation` works directly on strings.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    if (next_permutation(s.begin(), s.end()))
        cout << "Next: " << s << "\n";
    else
        cout << "-1\n";    // already the largest permutation of these digits

    return 0;
}
```

Similarly, `prev_permutation` gives the previous smaller number.

---

### 6.10 Sorting Digits — Smallest and Largest Number

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    string sorted_s = s;

    // Largest number → digits in descending order
    sort(sorted_s.begin(), sorted_s.end(), greater<char>());
    cout << "Largest : " << sorted_s << "\n";

    // Smallest number → digits in ascending order
    sort(sorted_s.begin(), sorted_s.end());

    // Fix leading zero: swap first non-zero digit to front
    if (sorted_s[0] == '0') {
        int i = 1;
        while (i < (int)sorted_s.size() && sorted_s[i] == '0') i++;
        if (i < (int)sorted_s.size())       // at least one non-zero digit exists
            swap(sorted_s[0], sorted_s[i]);
    }

    cout << "Smallest: " << sorted_s << "\n";

    return 0;
}
```

> **Note:** The leading-zero fix only triggers when the smallest arrangement
> starts with `'0'` (e.g. `"302"` → sorted `"023"` → fixed `"203"`).
> If all digits are zero (e.g. `"000"`), the fix is safely skipped.

### 6.11 Big Integer Addition

Adding two numbers that each have up to 10⁵ digits — the textbook column-by-column simulation.

```cpp
#include <bits/stdc++.h>
using namespace std;

string addBig(string a, string b) {
    // Align from the right
    int i = a.size() - 1;
    int j = b.size() - 1;
    int carry = 0;
    string result = "";

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        carry = sum / 10;
        result += ('0' + sum % 10);
    }

    reverse(result.begin(), result.end());
    return result;
}

int main() {
    string a, b;
    cin >> a >> b;
    cout << addBig(a, b) << "\n";
    return 0;
}
```

**Sample run:**
```
Input : 99999999999999999999  +  1
Output: 100000000000000000000
```

This would silently overflow any integer type but works perfectly here.

---

## 7. Gotchas to Avoid

| Mistake | What goes wrong | Fix |
|---------|-----------------|-----|
| `stoi` / `stoll` on a 50-digit string | Runtime exception or silent overflow | Only convert if `s.size() <= 18` |
| Comparing `"9" > "12"` directly | Lexicographically true, numerically false | Compare lengths first (§6.4) |
| Forgetting `s[i] - '0'` | `'7'` has ASCII value 55, not 7 | Always subtract `'0'` |
| Stripping leading zeros without a floor | `"000"` becomes `""` | Stop stripping at `size - 1` |
| Digit product overflow for long strings | Multiplying 10⁵ single digits overflows `long long` | Use `__int128` or apply modulo |
| Sorting digits naively for "smallest number" | `"302"` → `"023"` has a leading zero | Swap first non-zero digit to front |

---

## 8. Practice Problems

| Problem | Concept practised |
|---------|------------------|
| [CF 281A — Word Capitalization](https://codeforces.com/problemset/problem/281/A) | Basic char manipulation |
| [CF 1202C — WASD String](https://codeforces.com/problemset/problem/1202/C) | String logic, no numeric conversion needed |
| [CF 1736C — Good Subarrays](https://codeforces.com/problemset/problem/1736/C) | Digit-level observation |
| [SPOJ VFMUL](https://www.spoj.com/problems/VFMUL/) | Big integer multiplication via strings |
| [CF 102B — Sum of Digits](https://codeforces.com/problemset/problem/102/B) | §6.1 + §6.6 — Number exceeds `long long`; must read as string and repeatedly sum digits |
| [CF 1811A — Insert Digit](https://codeforces.com/problemset/problem/1811/A) | §6.8 — Insert a digit at the best position to get the largest possible number |
| [CF 489C — Given Length and Sum of Digits](https://codeforces.com/problemset/problem/489/C) | §6.10 + §6.6 — Construct smallest and largest number of length `m` with digit sum `s` |
| [CF 509C — Sums of Digits](https://codeforces.com/problemset/problem/509/C) | §6.1 + §6.8 — Output numbers exceed `long long`; must build digit-by-digit as strings |

---

## Summary

```
Use string input for a number when:
  ├── it exceeds long long  (> ~9.2 × 10¹⁸)
  ├── leading zeros are meaningful
  ├── you need to operate on individual digits
  ├── you need digit frequency, sorting, or permutations
  ├── you need to insert / delete / replace digits
  └── comparison is positional / lexicographic
```

The core insight is simple: **a number is just a string of digit characters.** Once you internalize that, an entire class of problems that look numeric become string problems — often far easier to implement correctly and without any risk of overflow.

---

*Happy Coding — Ace_Azimuth_Aviator*
