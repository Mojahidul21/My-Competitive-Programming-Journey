# Thinking Procedure: Self-Referential Constructive Problems

**Category:** Contest Strategy — Constructive Algorithms  
**Use case:** Problems where you must *build* a sequence/array/structure that satisfies a condition involving itself (its own sum, its own product, its own elements) — rather than problems where you search, count, or optimize over existing data.

---

## 1. How to Recognize This Family of Problems

Before you can apply any procedure, you need to notice you're in this territory. Suspect a **self-referential construction** problem when the statement has this shape:

- You are asked to **build** an array/sequence/set from scratch (not process a given one).
- The condition involves a **property of the whole structure** (sum, product, GCD, LCM, XOR, etc.) applied back onto **each individual element**.
- There is freedom in the values — usually a wide range like `1 ≤ ai ≤ 10^17`, meaning the problem wants a *constructive trick*, not an exact/unique answer.
- "Any valid answer is accepted" appears in the statement. This is the biggest tell — it means the graders expect many different constructions to work, so there's a flexible, mechanical way to build one.

If you catch yourself trying to reverse-engineer a formula or searching for a *specific* number-theoretic identity (primes, LCMs, exact factorizations) — stop. That's usually the wrong instinct for this family. The right instinct is closer to: *"What if I define each term in terms of what I've already built?"*

---

## 2. The General Thinking Procedure

### Step 1 — Restate the condition as a relationship, not a static property

Don't think of the condition as "this array must satisfy X." Think of it as "X must remain true as I add each element, one at a time."

Ask: *If I already have a partial structure that satisfies the condition so far, what value can I append that keeps the condition true?*

This reframes a global constraint into a **local, incremental rule** — which is almost always easier to construct against.

### Step 2 — Look for a self-referencing definition

Try defining the next term as a function of what already exists:

- Next term = running sum so far
- Next term = running product so far
- Next term = LCM of everything so far
- Next term = max/min of everything so far, shifted by some offset
- And so on ...

The instinct to chase is: **"What if the new term is *made of* the old terms, instead of being independent of them?"** This is the single most reusable idea in this class of problems. It converts a number-theory search into an algebraic identity that verifies itself.

### Step 3 — Verify the identity in the abstract, with variables, not numbers

Before coding anything, do this on paper with symbols:

```
Let P = current accumulated value (sum, product, etc.)
Let next term a = P
New accumulated value = P (op) a = P (op) P
```

Check: does the new accumulated value stay a "clean multiple" (or equivalent notion) of `a`? Often the operation naturally doubles, squares, or otherwise scales — and that scaling is exactly what preserves divisibility, or whatever property is required.

This step is where you *prove* correctness before you ever write code — which also means you can catch off-by-one / edge-case issues early instead of during a contest AC hunt.

### Step 4 — Identify what breaks at the boundaries (small `n`)

Self-referential constructions almost always have a **bootstrapping problem**: the very first 1–2 terms have nothing to reference yet, so the "next term = f(previous terms)" rule can't start immediately.

For each small case (`n = 1`, `n = 2`, `n = 3`, ...) ask explicitly:
- Does the general rule even apply yet?
- If not, what values do I need to seed manually?
- Is there a boundary case where **no valid array exists at all**? (Prove it, don't guess — small cases are exactly where impossibility proofs live, using pigeonhole-style or bounding arguments: *"the sum must lie strictly between X and Y, but no valid value exists there."*)

Never assume small n "obviously" extends the general pattern. Test it by hand.

### Step 5 — Confirm distinctness / other side-constraints

Constructive problems often bury a second constraint inside the first (e.g., "distinct positive integers"). Once you have a scaling/self-referential rule, distinctness is usually automatic *if* the sequence is strictly increasing — but confirm this explicitly rather than assuming it.

### Step 6 — Check the value bounds

Self-referential rules (especially doubling ones) grow **exponentially**. Before finalizing:
- Compute the largest value your construction could produce for the largest allowed `n`.
- Compare against the problem's stated bound (e.g., `≤ 10^17`).
- If it overflows the bound, you need a different scaling factor (e.g., not full doubling, but some smaller multiplicative or additive growth) — or you need to reconsider whether the constraint even allows a construction that grows this fast.

### Step 7 — Translate to code as a direct simulation

Once verified, the code is usually a simple loop: seed the first few terms, then repeatedly apply the self-referential rule for the rest. If your proof in Step 3 was solid, the code has no hidden edge cases left to discover — it's just a transcription.

---

## 3. Worked Example of the Procedure (not the solution itself)

To see the procedure in action rather than in the abstract, here's how it plays out on a real problem: *"construct `n` distinct positive integers such that their total sum is divisible by every individual element."*

| Step | What it looks like here |
|---|---|
| 1. Reframe | Instead of "sum divisible by every ai," think: "each time I add a new term, can I guarantee it divides the *running* sum?" |
| 2. Self-reference | Try: next term = sum of everything placed so far. |
| 3. Verify abstractly | If `a = P` (current sum), new sum `= P + a = 2P`. Every later sum is `P` times a power of 2 → always divisible by `a`. Identity confirmed. |
| 4. Boundaries | `n = 1` needs no rule (trivial). `n = 2` can't even start the self-referential rule — check by hand: forces `-1` via a bounding argument. `n ≥ 3` needs 1–2 seed values before the rule kicks in cleanly. |
| 5. Distinctness | Sequence is strictly increasing by construction → automatically distinct. |
| 6. Bounds | Values roughly triple/double each step — well under `10^17` even at `n = 50`. |
| 7. Code | Print seed values, then loop doubling a running sum. |

Notice: the *procedure* is what's transferable. The specific "sum-doubling" trick is just one instance of "next term = f(accumulated state)" — a different problem might need "next term = product so far" or "next term = LCM so far," and the same seven steps would still apply.

---

## 4. Mental Checklist for Next Time

When you hit a constructive problem, run through this fast:

- [ ] Does it say "any valid answer accepted"? → constructive trick likely exists.
- [ ] Can I define the condition as something that must survive *incrementally*, not just globally?
- [ ] Can the next term be defined *in terms of* the accumulated state (sum/product/LCM/etc.)?
- [ ] Have I verified the self-referential identity **symbolically**, before coding?
- [ ] Have I manually checked every small `n` (especially `n = 1, 2, 3`) for bootstrapping issues or impossibility?
- [ ] Does the growth rate of my construction stay inside the value bounds for the largest `n`?
- [ ] Are side-constraints (distinctness, positivity, etc.) automatically satisfied, or do I need to handle them separately?

If most of these come back "yes" quickly, you likely have a correct construction *before* you've written a single line of code — which is the whole point of thinking procedurally instead of pattern-matching under time pressure.

---

## 5. Practice Problem Set

Problems below all live in the same neighborhood — constructive, divisibility-flavored, "any valid answer accepted." Run the seven-step procedure on each before looking at any editorial.

| Ser # | Problem Title | Problem Short Description | Remark / Hint |
|---|---|---|---|
| 1 | [B. ezraft and Array](https://codeforces.com/contest/2246/problem/B) | Build `n` distinct positive integers whose total sum is divisible by every element, or say it's impossible. | The problem this whole procedure was built around. Ask what value you could append that stays a "clean multiple" of everything before it. |
| 2 | [A. Divisible Array](https://codeforces.com/contest/1828/problem/A) | Build `n` positive integers (not necessarily distinct) whose total sum is divisible by `n` itself. | Here the self-reference target isn't "each element" — it's a single fixed number `n`. Notice you have a very generous tool available: one element you haven't committed to yet. |
| 3 | [A. Array Divisibility](https://codeforces.com/problemset/problem/1983/A) | Build an array where, for every `k` from `1` to `n`, the sum of elements at positions that are multiples of `k` is itself divisible by `k`. | Think about which positions only ever get *one* constraint applied to them, and in what order you'd want to decide values so each new constraint has the fewest unknowns left in it. |
| 4 | [A. K-divisible Sum](https://codeforces.com/contest/1476/problem/A) | Build `n` positive integers whose sum is divisible by `k`, while minimizing the largest element used. | Not every element needs a special role — sometimes only *one* term needs to absorb the "remainder" so the self-reference condition holds, and the rest can be as small/uniform as possible. |

---

---

*Written, inspired by the problem [B. ezraft and Array](https://codeforces.com/contest/2246/problem/B).*
