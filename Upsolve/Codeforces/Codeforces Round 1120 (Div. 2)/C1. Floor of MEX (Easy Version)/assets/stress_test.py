#!/usr/bin/env python3
"""Stress test for CF 2263C1 (Floor of MEX, easy).
Usage:  g++ -O2 -o sol sol.cpp   &&   python3 stress_test.py ./sol [rounds]
Idea: pick a random hidden set, compute the array a by brute force, run your
solution, then re-check that the printed B really gives f(B, k) = a_k for every k."""
import random, subprocess, sys

def mex_of_floors(B, k):
    s = {y // k for y in B}
    m = 0
    while m in s:
        m += 1
    return m

def make_case(rng, n_max=12):
    n = rng.randint(1, n_max)
    p = rng.choice([0.1, 0.3, 0.6, 0.9])
    hidden = [y for y in range(n) if rng.random() < p]
    return n, [mex_of_floors(hidden, k) for k in range(1, n + 1)]

def main():
    exe = sys.argv[1]
    rounds = int(sys.argv[2]) if len(sys.argv) > 2 else 200
    rng = random.Random(12345)
    for r in range(rounds):
        cases = [make_case(rng) for _ in range(50)]
        inp = f"{len(cases)}\n" + "".join(f"{n}\n{' '.join(map(str, a))}\n" for n, a in cases)
        out = subprocess.run([exe], input=inp, capture_output=True, text=True, timeout=10).stdout.split("\n")
        for i, (n, a) in enumerate(cases):
            m = int(out[2 * i])
            B = list(map(int, out[2 * i + 1].split()))
            ok = len(B) == m == len(set(B)) and all(0 <= y < n for y in B) \
                 and all(mex_of_floors(B, k) == a[k - 1] for k in range(1, n + 1))
            if not ok:
                print("FAIL on n =", n, "a =", a, "your B =", B)
                sys.exit(1)
    print(f"OK: {rounds * 50} random cases passed")

main()
