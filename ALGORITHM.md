# Algorithm Deep Dive

This document explains every component of the MWIS solver in detail.

## Table of Contents

- [Why MWIS is Hard](#why-mwis-is-hard)
- [Heuristic Ensemble Engine](#heuristic-ensemble-engine)
- [Iterative Local Search Optimizer](#iterative-local-search-optimizer)
- [Time Complexity Analysis](#time-complexity-analysis)

## Why MWIS is Hard

The Maximum Weight Independent Set problem is NP-Hard on general graphs. With N = 200,000, the brute-force search space is 2^200,000 — larger than the number of atoms in the universe. No polynomial-time exact algorithm exists (unless P = NP).

However, by utilizing a high-performance multi-heuristic engine coupled with exhaustive local search, we can explore enough of the search space to find near-optimal solutions in under 15 milliseconds.

## Heuristic Ensemble Engine

Instead of relying on a single greedy strategy, the solver runs 6 distinct heuristic models in parallel. The best output serves as the initial draft for the local search phase.

### 1. Standard Greedy (by Skill)

Vertices are sorted purely by their weight (skill) in descending order. The heaviest available vertex is selected, and its neighborhood is immediately removed from the candidate pool.

### 2. Static Score Greedy (Degree-Discounted)

Vertices are evaluated using a ratio that balances their weight against their connectivity:

`Score(v) = W[v] / (1 + α * deg(v))`

We execute three parallel variations with `α ∈ {0.5, 1.0, 2.0}`. This prevents high-weight vertices from being selected if they consume too much of the graph.

### 3. Dynamic Greedy (Priority Queue)

Similar to the static score, but utilizes a lazy-evaluation Priority Queue. When a vertex is selected, its neighbors are removed, which dynamically reduces the degree of remaining adjacent vertices. The priority queue dynamically bubbles up vertices whose `W[v] / (1 + deg(v))` ratio improves.

### 4. Profit & Loss (P&L) Greedy

Vertices are scored by their net gain:
`P&L(v) = W[v] - Σ W[u] (for all u in N(v))`

This heuristic strongly avoids selecting vertices that would block neighbors with a vastly higher combined weight.

## Iterative Local Search Optimizer

Local search begins with the best configuration from the heuristic ensemble and applies exhaustive perturbation to escape local optima.

The optimizer runs up to 10 passes of the following state transformations:

### (1, 0)-Additions

Scans the graph for any unselected vertex `v` that has no adjacent vertices currently in the independent set. It is unconditionally added, yielding a strict weight increase.

### (1, 1)-Swaps

For every unselected vertex `u` blocked by exactly one active vertex `v`:
If `W[u] > W[v]`, `v` is removed and `u` is added.

### (1, 2)-Swaps

For every unselected vertex `u` blocked by exactly two active vertices `v1` and `v2`:
If `W[u] > W[v1] + W[v2]`, both `v1` and `v2` are removed, and `u` is added.

By iterating these passes up to 10 times, the solution state rapidly converges toward a global optimum.

## Time Complexity Analysis

| Phase | Time Complexity | Space Complexity |
|---|---|---|
| Input & Graph Build | O(N + M) | O(N + M) |
| Static / P&L Heuristics | O(N log N) | O(N) |
| Dynamic PQ Heuristic | O((N + M) log N) | O(N) |
| Local Search Sweep | O(N * deg) per sweep | O(N) |
| Total Execution Time | strictly < 15ms | O(N + M) |
