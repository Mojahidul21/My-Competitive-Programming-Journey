# CP Rating Growth Plan — 4 Weeks (Speed & Implementation Focus)

**Context:** Newbie/Pupil (<1200), main leak is speed/implementation mistakes under time pressure, goal is fastest realistic rating growth.
**Why this plan differs from the graph plan:** At <1200, rating is driven almost entirely by solving 800-1300 rated problems *fast and correctly* — not by algorithm breadth. Graph/DP are real gaps but aren't what's costing you rating right now. That track stays valid and waits until Weeks 1-4 here move you toward Pupil→Specialist territory.

**Format:** 4 weeks · 3 structured sessions/week · 1 hour/session, **plus** a non-negotiable daily habit (below) — the structured sessions alone won't get you the volume this needs.

**Daily habit (outside the 3 sessions):** 1-2 problems/day rated 800-1200, untimed is fine on non-session days. Every real contest you enter (aim for at least 1/week — Div3/Div4/Div2), **upsolve every problem you didn't finish within 24 hours** while it's still fresh.

---

## Week 1 — Implementation Hygiene + Core Speed Patterns

| Day | Focus | Why | Drill |
|---|---|---|---|
| **D1-W1** | Implementation pitfalls checklist: integer overflow (`int` vs `lli`), off-by-one, `n=0/1` edge cases, reading input format exactly | This is the single biggest silent rating-killer at your level — a correct idea failing on a dumb bug costs more than not knowing an algorithm | Solve 5-6 rating 800-1000 problems; for each, write down the bug *before* you'd have caught it in a real contest |
| **D2-W1** | Greedy & sorting-based problems | Huge fraction of CF A/B/C problems reduce to "sort by X, then greedily pick" | 5-6 problems tagged `greedy, sortings`, rating 900-1200 |
| **D3-W1** | Brute force / complete search + constraint reading | Learn to read `n ≤ 20` → bitmask/backtrack vs `n ≤ 10^6` → must be O(n log n) *before* writing code — saves minutes per problem | 4-5 problems tagged `brute force, implementation`, rating 800-1100, timed 10 min each |

**Checkpoint:** Re-solve 2 of your own recently-WA'd submissions and correctly spot the bug within 2 minutes.

---

## Week 2 — Pattern Library

| Day | Focus | Why | Drill |
|---|---|---|---|
| **D4-W2** | Prefix sums & difference arrays | Extremely common building block, near-zero implementation cost once internalized | CSES *Range Sum Queries I*; 3-4 CF problems tagged `prefix-sums` |
| **D5-W2** | Two pointers / sliding window | Converts O(n²) brute force into O(n) — recognizable pattern, fast to code | 4-5 problems tagged `two pointers`, rating 1000-1300 |
| **D6-W2** | Binary search (on array + on answer) | "Binary search the answer" unlocks problems that look hard but reduce to a monotonic check | CSES *Factory Machines*; 3-4 CF problems tagged `binary search`, rating 1100-1400 |

**Checkpoint:** Time yourself — average under 12 minutes per problem across this week's rating range, including read time.

---

## Week 3 — Math & Ad-hoc

| Day | Focus | Why | Drill |
|---|---|---|---|
| **D7-W3** | Basic number theory: GCD/LCM, modular arithmetic (your `mod` macro), sieve of Eratosthenes | Shows up constantly as a 1-2 line sub-step inside otherwise-easy problems | 4-5 problems tagged `math, number theory`, rating 900-1200 |
| **D8-W3** | Ad-hoc / simulation problems | These are pure careful-reading + careful-coding tests — directly targets your stated weak point | 4-5 problems tagged `implementation`, rating 800-1100, strict 8 min timer each |
| **D9-W3** | String basics: frequency counting, palindrome checks, simple manipulation | Common in Div3/4 A-C slots | 4-5 problems tagged `strings, implementation`, rating 800-1200 |

**Checkpoint:** Solve a full mock Div4 A-D set (4 problems) in under 40 minutes combined.

---

## Week 4 — Contest Simulation

| Day | Focus | Why | Drill |
|---|---|---|---|
| **D10-W4** | Timed virtual contest (Div3 or Div4, full length) | Real time pressure is the only way to actually test the speed you've built | Do a virtual participation on Codeforces; afterward, log every minute lost to bugs vs. genuine thinking time |
| **D11-W4** | Review D10's error log + targeted drill on whatever pattern tripped you up | Fixes the specific leak this cycle exposed, rather than guessing | 4-5 problems on that one weak pattern |
| **D12-W4** | Second timed virtual contest + build a personal "contest-day checklist" card from everything caught this month | Confirms improvement with a second data point; the checklist becomes your permanent pre-submit habit | Virtual participation + write the checklist (fast IO, overflow check, edge cases n=0/1, re-read constraints before coding) |

**Final checkpoint:** Compare D10 vs D12 virtual contest results — fewer bugs and faster solve time on the same-difficulty problems is the real signal, more than raw problems-solved count.

---

## Note
This plan intentionally sidelines graph algorithms and deep DP for 4 weeks. Once you're consistently clearing Div3 A-D / Div2 A-C fast with few implementation errors (roughly Pupil→Specialist range), that's the right time to pick the graph track back up — at that point algorithm breadth becomes the actual bottleneck instead of speed.
