# Palindrome, Twelve and Two Terms

**Platform:** Codeforces | **Contest:** Round 1102 (Div. 2) | **Problem:** B | **Tags:** math

---

## Problem Summary

Given a positive integer $n$ ($1 \le n \le 10^{18}$), find a pair of non-negative integers $(a, b)$ such that:

- $a + b = n$
- $a$ is a palindrome
- $b$ is divisible by $12$

If no such pair exists, output $-1$.

---

## Solution Reasoning

We start from the constraint directly:

$$n = a + b, \quad a \text{ is a palindrome}, \quad b = 12k$$

Since $b$ is a multiple of $12$, it contributes nothing to $n \bmod 12$. So:

$$n \bmod 12 = a \bmod 12$$

This means whatever palindrome $a$ we pick, its remainder when divided by $12$ must equal $n \bmod 12$. The possible remainders are $\{0, 1, 2, \ldots, 11\}$.

Now observe: all integers in $\{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11\}$ are palindromes themselves. So for any $n$ whose remainder $r = n \bmod 12$ falls in this set, we can simply take $a = r$. Then $b = n - r$ is automatically divisible by $12$, and we are done.

$$\text{If } r \ne 10: \quad \text{answer is } (r,\ n - r)$$

The only remainder that is not a palindrome is $10$.

**Handling $r = 10$:** We need the smallest palindrome $a$ such that $a \bmod 12 = 10$.

- $a = 10$: not a palindrome.
- $a = 10 + 12 = 22$: **22 is a palindrome**, and $22 \bmod 12 = 10$. ✓

So $a = 22$ is the smallest valid choice. As long as $n \ge 22$ (i.e., $n > 10$), we can write:

$$\text{If } r = 10 \text{ and } n > 10: \quad \text{answer is } (22,\ n - 22)$$

The only remaining case is $n = 10$ itself (the unique value where $r = 10$ and $n < 22$). Here $b = n - 22$ would be negative, and no valid pair exists.

$$\text{If } n = 10: \quad \text{output } {-1}$$


---

## Solution

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;

        long long rem = n % 12;

        if (rem != 10) {
            cout << rem << ' ' << n - rem << '\n';
        } else if (n > 10) {
            cout << 22 << ' ' << n - 22 << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
    return 0;
}
```

**Time complexity:** $O(1)$ per test case.  
**Space complexity:** $O(1)$.

---

## Worked Examples

**Example 1:** $n = 1$  
$r = 1 \ne 10$. Output: `1 0`. ($1$ is a palindrome, $0$ is divisible by $12$.)

**Example 2:** $n = 10$  
$r = 10$, $n \not> 10$. Output: `-1`.

**Example 3:** $n = 310$  
$r = 310 \bmod 12 = 10$, $n > 10$. Output: `22 288`. ($22$ is a palindrome, $288 = 12 \times 24$.)

**Example 4:** $n = 12$  
$r = 0 \ne 10$. Output: `0 12`. ($0$ is a palindrome, $12$ is divisible by $12$.)

**Example 5:** $n = 10^9$  
$r = 10^9 \bmod 12 = 4$. Output: `4 999999996`.

**Example 6:** $n = 6111111111111111$  
$r = 3$. Output: `3 6111111111111108`.

---

## Key Takeaway

The problem reduces to one modular observation: $a \bmod 12$ must equal $n \bmod 12$. Since every remainder in $\{0\text{–}9, 11\}$ is itself a palindrome, eleven out of twelve cases resolve instantly. The one troublesome remainder, $10$, is handled by stepping up to the next palindrome with the same remainder — which is $22$. The only impossible case is $n = 10$ exactly.

No palindrome-checking function. No loop. Three lines of logic based on Math.

---

*Solved during upsolve after Codeforces Round 1102 (Div. 2)  
[Problem link](https://codeforces.com/contest/2234/problem/B)  
[Solution link](https://codeforces.com/contest/2234/submission/377713773)*
