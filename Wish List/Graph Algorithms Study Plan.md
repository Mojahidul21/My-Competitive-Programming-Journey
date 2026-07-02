# Graph Algorithms Study Plan

**Format:** 4 weeks · 3 sessions/week · 1 hour/session · 12 sessions total  
**Session structure (every day):** 15 min concept + trace by hand → 15 min implement from scratch (no old code/notes) → 30 min solve problems.

---

## Week 1 — Traversal Foundations

| Day | Topic | Why | Learn From | Practice |
|---|---|---|---|---|
| **D1-W1** | Graph representation (adj. list/matrix) + BFS | Base case for every unweighted shortest-path problem | [cp-algorithms: BFS](https://cp-algorithms.com/graph/breadth-first-search.html) | CSES *Counting Rooms*, *Message Route* |
| **D2-W1** | DFS + connected components | Component-counting is a building block used inside harder problems too | [cp-algorithms: DFS](https://cp-algorithms.com/graph/depth-first-search.html) | CSES *Building Roads*, *Labyrinth* |
| **D3-W1** | Cycle detection + bipartite check (2-coloring) | Common yes/no graph question in easier problems | [cp-algorithms: Cycle detection](https://cp-algorithms.com/graph/finding-cycle.html) | CSES *Building Teams*, *Round Trip* |

**Checkpoint:** Write BFS & DFS from memory in under 5 minutes, no lookup.

---

## Week 2 — Structure & Ordering

| Day | Topic | Why | Learn From | Practice |
|---|---|---|---|---|
| **D4-W2** | DSU (Union-Find) | Dynamic connectivity queries; prerequisite for Kruskal's MST | [cp-algorithms: DSU](https://cp-algorithms.com/data_structures/disjoint_set_union.html) | CSES *Road Construction* |
| **D5-W2** | Dijkstra's algorithm | Standard weighted single-source shortest path | [cp-algorithms: Dijkstra](https://cp-algorithms.com/graph/dijkstra.html) | CSES *Shortest Routes I*, *Flight Discount* |
| **D6-W2** | Topological sort (Kahn's + DFS) | Dependency-ordering/DAG problems — likely your recent contest's 4th-problem type | [cp-algorithms: Topo sort](https://cp-algorithms.com/graph/topological-sort.html) | CSES *Course Schedule*, *Longest Flight Route* |

**Checkpoint:** Solve 2-3 fresh, unseen CF problems (mixed tags from Weeks 1-2) cold, no notes.

---

## Week 3 — MST, Negative Weights, SCC

| Day | Topic | Why | Learn From | Practice |
|---|---|---|---|---|
| **D7-W3** | MST — Kruskal's (+ DSU) & Prim's | Direct payoff of D4-W2's DSU; common standalone problem type | [cp-algorithms: MST](https://cp-algorithms.com/graph/mst_kruskal.html) | CSES *Road Reparation* |
| **D8-W3** | Bellman-Ford + Floyd-Warshall | Dijkstra fails silently on negative edges — need to recognize when to switch | [Bellman-Ford](https://cp-algorithms.com/graph/bellman_ford.html), [Floyd-Warshall](https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html) | CSES *High Score*, *Shortest Routes II* |
| **D9-W3** | SCC (Kosaraju's) + bridges/articulation points | "Critical edge/node" problems — recurring shape once recognized | [SCC](https://cp-algorithms.com/graph/strongly-connected-components.html), [Bridges](https://cp-algorithms.com/graph/bridge-searching.html) | CSES *Planets and Kingdoms* |

**Checkpoint:** Given an unfamiliar graph problem, classify which technique (of the 9 so far) it needs within a few minutes of reading.

---

## Week 4 — Trees, LCA, BFS Variants (Final Week)

| Day | Topic | Why | Learn From | Practice |
|---|---|---|---|---|
| **D10-W4** | Trees as graphs — rooting, diameter, basic tree DP | Trees are their own recurring category, not just "graph with V-1 edges" | [cp-algorithms: Tree traversal](https://cp-algorithms.com/graph/tree-euler-tour.html) | CSES *Tree Diameter*, *Subordinates* |
| **D11-W4** | LCA — binary lifting | Prerequisite for tree-distance/path query problems | [cp-algorithms: LCA](https://cp-algorithms.com/graph/lca_binary_lifting.html) | CSES *Company Queries II* |
| **D12-W4** | 0/1 BFS + multi-source BFS + timed mixed mock | Cheap high-value BFS variants; mock tests retrieval across all 4 weeks | [cp-algorithms: 0/1 BFS](https://cp-algorithms.com/graph/01_bfs.html) | CSES *Monsters* + 2-3 cold mixed problems |

**Final checkpoint:** Timed mock (2-3 cold problems, mixed weeks) solved 2/3 cleanly = plan has done its job. Remaining growth from here is volume (upsolving), not new theory.

---

## Note — Topics Not Covered
Deliberately scoped to what's highest-ROI for your current contest level. Left out, roughly in order of how soon you'd likely need them next:
- **Network flow** (Max Flow/Min Cut, Edmonds-Karp, Dinic's) — harder Div1 problems, bipartite matching
- **2-SAT** — niche but clean once graphs + implication reasoning are solid
- **DSU on tree / small-to-large merging** — an optimization layered on top of what you'll already know
- **Heavy-Light Decomposition (HLD)** — path/subtree queries on trees, harder tier than D11-W4's LCA
- **Euler paths/circuits** (distinct from the tree Euler tour in D10/D11-W4) — occasional but standalone
- **Persistent/advanced data structures over trees** — well beyond this scope
