It is a draft article.  


# Numeric String Utility Functions in C++
### A Competitive Programming Reference — Ace_Azimuth_Aviator

---

## Table of Contents

1. [When Do You Need These?](#1-when-do-you-need-these)
2. [The Two Regimes](#2-the-two-regimes)
3. [Foundation — Normalize](#3-foundation--normalize)
4. [Comparison Functions](#4-comparison-functions)
5. [Selection Functions](#5-selection-functions)
6. [Arithmetic Functions](#6-arithmetic-functions)
7. [Query / Predicate Functions](#7-query--predicate-functions)
8. [Full Cheat-Sheet (All Functions Together)](#8-full-cheat-sheet)
9. [Problem Walkthrough — CF 2228 C1](#9-problem-walkthrough--cf-2228-c1)

---

## 1. When Do You Need These?

You are solving a Codeforces problem. You need a numeric string function when you see **one or more** of the following symptoms:

| # | Symptom in Problem Statement | What It Implies |
|---|---|---|
| 1 | `0 ≤ a ≤ 10^17` and input/output is a plain integer | Fits `long long`; `stoll` + arithmetic is enough |
| 2 | `0 ≤ a ≤ 10^100` or "up to 1000 digits" | Beyond `long long`; need pure string arithmetic |
| 3 | "decimal representation contains only digits from d" | You will build candidate strings and compare them numerically |
| 4 | "Find minimum `|a − b|`" where `a` is huge | Need `absDiff` on string form |
| 5 | You generate many candidate numbers and must pick closest/smallest | Need `smallerStr`, `compareNumStr` |
| 6 | Leading zeros appear after string manipulation | Need `trimLeadingZeros` before any comparison |

> **Golden Rule:**
> If the number fits inside `long long` (up to ~9.2 × 10¹⁸), always parse with `stoll` and do normal arithmetic — it is faster and simpler.
> Only use pure string arithmetic when values genuinely exceed `long long`.

---

## 2. The Two Regimes

All functions below are tagged with which regime they belong to:

- 🟢 **LL-safe** — internally uses `long long`; works for values up to ~9.2 × 10¹⁸
- 🔵 **BigInt** — pure string arithmetic; works for arbitrarily large values

CF problems with `a ≤ 10^17` are 🟢. If a constraint says `10^200` or "1000 digits", you need 🔵.

---

## 3. Foundation — Normalize

Always normalize before comparing or printing. A freshly-built candidate string may carry leading zeros.

### 3.1 `trimLeadingZeros` 🟢🔵

```cpp
string trimLeadingZeros(const string& s) {
    size_t start = s.find_first_not_of('0');
    return (start == string::npos) ? "0" : s.substr(start);
}
```

**When to use:**
- After you build a candidate number digit-by-digit (e.g., replacing each digit of `a` with the nearest allowed digit).
- Before any comparison; `"007" < "9"` is wrong lexicographically but `trimLeadingZeros("007") = "7"` is correct.

**Example:**
```
trimLeadingZeros("007")  →  "7"
trimLeadingZeros("000")  →  "0"
trimLeadingZeros("100")  →  "100"
```

---

## 4. Comparison Functions

### 4.1 `compareNumStr` 🟢🔵

Returns `-1`, `0`, or `1` — exactly like a comparator.

```cpp
// Returns -1 if a < b, 0 if a == b, +1 if a > b
int compareNumStr(const string& a, const string& b) {
    string x = trimLeadingZeros(a), y = trimLeadingZeros(b);
    if (x.size() != y.size()) return x.size() < y.size() ? -1 : 1;
    return x < y ? -1 : (x > y ? 1 : 0);
}
```

**How it works:**
1. Trim leading zeros so lengths are meaningful.
2. Shorter string = smaller number.
3. If lengths are equal, lexicographic order equals numeric order (since digits are same-width characters).

**When to use:**
- Sorting a list of numeric strings: `sort(all(v), [](auto& a, auto& b){ return compareNumStr(a,b)<0; });`
- Anywhere you would write `a < b` but `a` and `b` are strings.

**Example:**
```
compareNumStr("99",  "100")  →  -1   (99 < 100)
compareNumStr("100", "100")  →   0
compareNumStr("101", "99")   →  +1
compareNumStr("007", "7")    →   0   (leading zeros handled)
```

### 4.2 `equalNumStr` 🟢🔵

```cpp
bool equalNumStr(const string& a, const string& b) {
    return compareNumStr(a, b) == 0;
}
```

**When to use:** When you want a clean boolean equality check that ignores leading zeros.

---

## 5. Selection Functions

### 5.1 `smallerStr` 🟢

```cpp
// Returns the string representing the smaller value.
// On tie, returns b. Change <= to < if you prefer a on tie.
string smallerStr(const string& a, const string& b) {
    return stoll(a) < stoll(b) ? a : b;
}
```

**When to use:**
- You have two (or more) candidate answers, both encoded as strings, and want the one closer to zero.
- Symptom: "find minimum b" when you generate exactly two candidates (one from below, one from above).

**Example:**
```
smallerStr("333", "777")   →  "333"
smallerStr("1000", "999")  →  "999"
```

### 5.2 `largerStr` 🟢

```cpp
string largerStr(const string& a, const string& b) {
    return stoll(a) > stoll(b) ? a : b;
}
```

**When to use:** You want the maximum of two numeric strings (e.g., "which candidate is farther from a?").

### 5.3 `smallerStrBig` 🔵 (BigInt version)

Use when values may exceed `long long`:

```cpp
string smallerStrBig(const string& a, const string& b) {
    return compareNumStr(a, b) <= 0 ? a : b;
}

string largerStrBig(const string& a, const string& b) {
    return compareNumStr(a, b) >= 0 ? a : b;
}
```

---

## 6. Arithmetic Functions

### 6.1 `absDiff` 🟢

```cpp
// Returns |a - b| as a string. Both a, b must fit in long long.
string absDiff(const string& a, const string& b) {
    lli x = stoll(a), y = stoll(b);
    return to_string(abs(x - y));
}
```

**When to use:**
- Problem asks for `|a − b|` and constraint is `a ≤ 10^17`.
- You are comparing distances between candidates and a target.

**Example:**
```
absDiff("3333", "777")  →  "2556"
absDiff("222",  "333")  →  "111"
absDiff("50",   "50")   →  "0"
```

### 6.2 `absDiffBig` 🔵 (BigInt version)

For values beyond `long long` — implements grade-school subtraction on strings.

```cpp
// Subtract smaller from larger, both non-negative, no leading zeros assumed.
string subtractStr(string a, string b) {
    // Ensure a >= b
    if (compareNumStr(a, b) < 0) swap(a, b);
    string res;
    int i = a.size() - 1, j = b.size() - 1, borrow = 0;
    while (i >= 0) {
        int d = (a[i--] - '0') - borrow - (j >= 0 ? b[j--] - '0' : 0);
        if (d < 0) { d += 10; borrow = 1; } else borrow = 0;
        res.push_back('0' + d);
    }
    reverse(res.begin(), res.end());
    return trimLeadingZeros(res);
}

string absDiffBig(const string& a, const string& b) {
    return subtractStr(a, b);   // subtractStr handles which is larger
}
```

**Example:**
```
absDiffBig("1000000000000000000000", "999999999999999999999")  →  "1"
```

### 6.3 `addStrings` 🔵

For completeness — BigInt addition.

```cpp
string addStrings(const string& a, const string& b) {
    string res;
    int i = a.size() - 1, j = b.size() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int s = carry;
        if (i >= 0) s += a[i--] - '0';
        if (j >= 0) s += b[j--] - '0';
        carry = s / 10;
        res.push_back('0' + s % 10);
    }
    reverse(res.begin(), res.end());
    return res.empty() ? "0" : res;
}
```

**When to use:** Any problem where the sum of two large numbers must stay as a string.

---

## 7. Query / Predicate Functions

### 7.1 `isZeroStr` 🟢🔵

```cpp
bool isZeroStr(const string& s) {
    return trimLeadingZeros(s) == "0";
}
```

**When to use:** After subtraction, check if the result is zero before printing or branching.

### 7.2 `digitCount` 🟢🔵

```cpp
// Number of significant digits (no leading zeros counted)
int digitCount(const string& s) {
    return trimLeadingZeros(s).size();
}
```

**When to use:** Length-based comparisons, building candidates of a specific length.

---

## 8. Full Cheat-Sheet

Paste this block above `tourist` in your template file:

```cpp
// ─── Numeric String Utilities ───────────────────────────────────────────────

string trimLeadingZeros(const string& s) {
    size_t p = s.find_first_not_of('0');
    return (p == string::npos) ? "0" : s.substr(p);
}

// -1 : a < b | 0 : a == b | +1 : a > b   (BigInt-safe)
int compareNumStr(const string& a, const string& b) {
    string x = trimLeadingZeros(a), y = trimLeadingZeros(b);
    if (x.size() != y.size()) return x.size() < y.size() ? -1 : 1;
    return x < y ? -1 : (x > y ? 1 : 0);
}

bool equalNumStr  (const string& a, const string& b) { return compareNumStr(a,b)==0; }

// LL-safe (values ≤ 9.2e18)
string absDiff    (const string& a, const string& b) { lli x=stoll(a),y=stoll(b); return to_string(abs(x-y)); }
string smallerStr (const string& a, const string& b) { return stoll(a)<=stoll(b)?a:b; }
string largerStr  (const string& a, const string& b) { return stoll(a)>=stoll(b)?a:b; }

// BigInt-safe
string smallerStrBig(const string& a,const string& b){return compareNumStr(a,b)<=0?a:b;}
string largerStrBig (const string& a,const string& b){return compareNumStr(a,b)>=0?a:b;}

string addStrings(const string& a, const string& b) {
    string res; int i=a.size()-1,j=b.size()-1,carry=0;
    while(i>=0||j>=0||carry){
        int s=carry;
        if(i>=0)s+=a[i--]-'0'; if(j>=0)s+=b[j--]-'0';
        carry=s/10; res.push_back('0'+s%10);
    }
    reverse(res.begin(),res.end());
    return res.empty()?"0":res;
}

string subtractStr(string a, string b) {          // returns |a-b|, BigInt-safe
    if(compareNumStr(a,b)<0)swap(a,b);
    string res; int i=a.size()-1,j=b.size()-1,borrow=0;
    while(i>=0){
        int d=(a[i--]-'0')-borrow-(j>=0?b[j--]-'0':0);
        if(d<0){d+=10;borrow=1;}else borrow=0;
        res.push_back('0'+d);
    }
    reverse(res.begin(),res.end());
    return trimLeadingZeros(res);
}

bool isZeroStr  (const string& s){return trimLeadingZeros(s)=="0";}
int  digitCount (const string& s){return(int)trimLeadingZeros(s).size();}

// ────────────────────────────────────────────────────────────────────────────
```

---

## 9. Problem Walkthrough — CF 2228 C1

> **Problem:** Given `a` (0 ≤ a ≤ 10¹⁷) and two allowed digits `d[0] < d[1]`,
> find the minimum `|a − b|` where `b` uses only digits from `{d[0], d[1]}`.

### Which symptoms fired?

| Symptom | Present? |
|---|---|
| Value up to 10¹⁷ | ✅ → use 🟢 LL-safe functions |
| "decimal representation contains only digits from d" | ✅ → build candidate strings |
| "Find minimum `|a − b|`" | ✅ → need `absDiff` |
| Compare two candidates | ✅ → need `smallerStr` |

### Core Idea

Convert `a` to a string. For each digit of `a`, the nearest allowed replacement is either `d[0]` or `d[1]`. This gives at most two candidate numbers per digit position, but the key insight is:

- **Candidate "floor"** (`b_lo`): replace every digit with the nearest `d[i]` that does **not exceed** it (going down).
- **Candidate "ceil"** (`b_hi`): replace every digit with the nearest `d[i]` that is **≥** it (going up).

Then answer = `min(|a − b_lo|, |a − b_hi|)` = `smallerStr(absDiff(sa, b_lo), absDiff(sa, b_hi))`.

### Simulation Table (a = 3333, d = {6, 7})

| Digit of a | Nearest d below | Nearest d above |
|---|---|---|
| 3 | none → use d[0]=6 for whole number going up | 6 |

Since no digit ≤ 3 exists in `{6,7}`, the only valid candidate is `b = 777...` (all 6s is still > 3333... wait — 6 > 3, so floor doesn't exist per digit; the entire number with all 6s = 6666, and going below means reducing length: max number with fewer digits using {6,7} = 777).

- `b_hi = 6666`, `|3333 − 6666| = 3333`
- `b_lo = 777`,  `|3333 −  777| = 2556`
- Answer: `min(3333, 2556) = 2556` ✅

### AC Code (Easy Version, n=2)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define tourist int main(){ios::sync_with_stdio(0);cin.tie(0);
#define Ace_Azimuth_Aviator return 0;}
#define css <<' '
#define cnl <<'\n'
#define pnl cout<<'\n';
#define tcl int t;cin>>t;while(t--){
#define tnl if(t)pnl}
#define lli long long
#define all(a) a.begin(),a.end()

// ─── Numeric String Utilities ────────────────────────────────────────────────
string trimLeadingZeros(const string& s){
    size_t p=s.find_first_not_of('0');
    return(p==string::npos)?"0":s.substr(p);
}
int compareNumStr(const string& a,const string& b){
    string x=trimLeadingZeros(a),y=trimLeadingZeros(b);
    if(x.size()!=y.size())return x.size()<y.size()?-1:1;
    return x<y?-1:(x>y?1:0);
}
string absDiff(const string& a,const string& b){
    lli x=stoll(a),y=stoll(b);
    return to_string(abs(x-y));
}
string smallerStr(const string& a,const string& b){
    return stoll(a)<=stoll(b)?a:b;
}
// ─────────────────────────────────────────────────────────────────────────────

// Build smallest number >= x using only digits in d (length >= len of x, or shorter for floor)
// Returns "" if impossible for that direction
string buildCeil(const string& s, vector<int>& d) {
    int n = s.size();
    string res(n, '0');
    // Try to build same-length number >= s
    for (int i = 0; i < n; i++) {
        int cur = s[i] - '0';
        // Find smallest d[j] >= cur
        auto it = lower_bound(all(d), cur);
        if (it == d.end()) {
            // Must increment previous position
            int j = i - 1;
            while (j >= 0) {
                int prv = res[j] - '0';
                auto nxt = upper_bound(all(d), prv);
                if (nxt != d.end()) { res[j] = '0' + *nxt; break; }
                j--;
            }
            if (j < 0) {
                // Need one more digit: smallest d (non-zero if possible) followed by all d[0]
                int lead = (d[0] == 0 && d.size() > 1) ? d[1] : d[0];
                if(lead == 0) return ""; // can't build positive n+1 digit number with only 0
                res = string(1,'0'+lead) + string(n, '0'+d[0]);
                return res;
            }
            // Fill rest with d[0]
            for (int k = j + 1; k < n; k++) res[k] = '0' + d[0];
            return res;
        }
        res[i] = '0' + *it;
        if (*it > cur) {
            // Fill rest with d[0]
            for (int k = i + 1; k < n; k++) res[k] = '0' + d[0];
            return res;
        }
    }
    return res;
}

string buildFloor(const string& s, vector<int>& d) {
    int n = s.size();
    string res(n, '0');
    for (int i = 0; i < n; i++) {
        int cur = s[i] - '0';
        // Find largest d[j] <= cur
        auto it = upper_bound(all(d), cur);
        if (it == d.begin()) {
            // Must decrement previous position
            int j = i - 1;
            while (j >= 0) {
                int prv = res[j] - '0';
                auto prv_it = lower_bound(all(d), prv);
                if (prv_it != d.begin()) { --prv_it; res[j] = '0' + *prv_it; break; }
                j--;
            }
            if (j < 0) {
                // Need smaller length: largest (n-1)-digit number using d
                if (n == 1) return "0"; // only option
                int lead = d.back();
                if (lead == 0) return "0";
                return string(1, '0' + lead) + string(n - 2, '0' + d.back()) ;
            }
            for (int k = j + 1; k < n; k++) res[k] = '0' + d.back();
            return trimLeadingZeros(res);
        }
        --it;
        res[i] = '0' + *it;
        if (*it < cur) {
            for (int k = i + 1; k < n; k++) res[k] = '0' + d.back();
            return trimLeadingZeros(res);
        }
    }
    return trimLeadingZeros(res);
}

tourist
tcl
    lli a; int n;
    cin >> a >> n;
    vector<int> d(n);
    for(auto& x : d) cin >> x;

    string sa = to_string(a);
    string bhi = buildCeil(sa, d);
    string blo = buildFloor(sa, d);

    string diff_hi = absDiff(sa, bhi);
    string diff_lo = absDiff(sa, blo);
    cout << smallerStr(diff_hi, diff_lo) cnl;
tnl
Ace_Azimuth_Aviator
```

---

## Quick Reference Card

| Function | Regime | Input | Returns |
|---|---|---|---|
| `trimLeadingZeros(s)` | 🟢🔵 | `string` | normalized `string` |
| `compareNumStr(a,b)` | 🟢🔵 | two `string` | `-1 / 0 / 1` |
| `equalNumStr(a,b)` | 🟢🔵 | two `string` | `bool` |
| `absDiff(a,b)` | 🟢 ≤10¹⁸ | two `string` | `string` |
| `smallerStr(a,b)` | 🟢 ≤10¹⁸ | two `string` | `string` |
| `largerStr(a,b)` | 🟢 ≤10¹⁸ | two `string` | `string` |
| `smallerStrBig(a,b)` | 🔵 any | two `string` | `string` |
| `largerStrBig(a,b)` | 🔵 any | two `string` | `string` |
| `subtractStr(a,b)` | 🔵 any | two `string` | `string` (`\|a-b\|`) |
| `addStrings(a,b)` | 🔵 any | two `string` | `string` |
| `isZeroStr(s)` | 🟢🔵 | `string` | `bool` |
| `digitCount(s)` | 🟢🔵 | `string` | `int` |

---

*Written for Ace_Azimuth_Aviator — Codeforces competitive programming reference.*
