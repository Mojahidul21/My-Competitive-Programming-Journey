# Trust the Predicate: Stop Simulating What You've Already Proven

**Category:** Contest Strategy — Thinking Methodology  

**Use case:** Any problem where you've derived a closed-form, declarative condition for the answer (an invariant, a parity argument, a residue check, a reachability formula) but still feel the pull to verify it by simulating the underlying process.

---

## 1. The Trap

A lot of contest problems have two solutions living inside them at once:

1. **A predicate** — a condition you can check directly, in one pass, with no state and no mutation. "The answer is YES iff every element satisfies `X`."
2. **A simulation** — actually carrying out the process the problem describes (swapping, moving, building) and checking the result afterward.

When you first derive the predicate, it often doesn't feel finished. It feels like a claim, not a solution — so the instinct is to "double-check" it by writing the simulation too, or to just code the simulation directly because it feels safer than trusting an argument you made in your head thirty seconds ago.

This is usually a mistake, for a very specific reason: **the predicate and the simulation are not equally likely to be correct once implemented.** The predicate is typically one loop with one condition. The simulation has to get *everything* right — indexing conventions, which array holds values versus positions, whether one pass is enough or you need to iterate to a fixed point, whether an early exit is actually correct or just looks correct. Every one of those is a separate place to introduce a bug that has nothing to do with whether your original reasoning was right.

In other words: reverting to simulation doesn't make you safer. It just trades one risk (an unverified proof) for a different, usually larger, set of risks (implementation bugs in a more complex program) — and it's easy to walk away from a stack of wrong answers still believing the *reasoning* was the problem, when actually the reasoning was fine and the simulation was where things broke.

---

## 2. Why This Happens

A few things make this trap easy to fall into specifically under contest pressure:

- **A predicate feels too short to be a real solution.** If the whole check is `if (i - target(i)) % g != 0: NO`, it can feel like you must be missing something, so you look for more to write.
- **Simulation feels concrete.** Watching state change step by step feels like verification, even though it isn't — it only verifies that specific run, not the general claim.
- **A wrong answer is ambiguous about its own cause.** When simulation code fails, it's tempting to patch the simulation (add a condition, restrict a direction, loop again) rather than step back and ask whether the *reasoning* was already correct and the bug is purely mechanical.

---

## 3. The Discipline

- **If you've proven the predicate, code the predicate — not the simulation "just to be safe."** Trusting a correct proof is not a risk; it's the entire point of having proven it.
- **If you don't fully trust the predicate, the fix is to re-verify the proof, not to fall back on simulation.** Take one small sample case and check the predicate by hand, term by term. This is faster than debugging a simulation and it directly tests the thing you're actually unsure about.
- **If a simulation is failing, ask first whether a predicate exists that would make the simulation unnecessary.** Repeated wrong answers on a simulation are a good moment to step back one level, rather than adding another special case to the process you're mimicking.
- **Treat every added condition in a simulation with suspicion.** A clean predicate has no room for stray conditions. If you find yourself adding an `if` to a simulation that isn't obviously implied by your original reasoning, that's a signal the simulation has drifted from the proof, not that the problem needed the extra case.
- **A predicate that only checks, and never mutates, has fewer places to be wrong.** All else equal, prefer the version of your solution that reads input once and answers, over the version that reads input, changes it, and re-inspects it.

---

## 4. Mental Checklist

- [ ] Have I derived a condition that can be checked in one pass, with no state changes?
- [ ] If yes — am I coding that condition directly, or am I still writing a simulation "to be safe"?
- [ ] If I don't trust the condition, have I checked it by hand on a sample, rather than reaching for simulation?
- [ ] If a simulation is failing, have I asked whether a predicate would remove the need for it entirely?
- [ ] Does every condition inside my code trace back to something in my original reasoning, or did one get added just because the previous version failed?
- [ ] If I'm about to simulate a process, have I asked what property is *invariant* across every operation — and whether comparing that property directly replaces the simulation entirely?

---

*This principle applies across problem types — parity arguments, invariants, reachability formulas, and constructive existence checks all tend to produce a predicate that's cleaner and more trustworthy than the process it's describing.*  

*See the companion technique article, [GCD-Reachability Under Fixed-Step Moves](https://github.com/Mojahidul21/My-Competitive-Programming-Journey/blob/main/Tricks%20%26%20Techniques/GCD/GCD-Reachability%20Under%20Fixed-Step%20Moves.md), for one concrete family of problems where this distinction matters.*
