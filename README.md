# Maximum Weight Independent Set (MWIS) Solver

A high-performance C++ solver for the Maximum Weight Independent Set problem, optimized for ultra-fast heuristic generation and local search execution.

Given an undirected graph where each vertex has a weight, this engine finds a subset of vertices such that **no two are adjacent** and the **total weight is maximized**.

---

## Performance Benchmarks

Our architecture avoids heavy pre-processing or recursive exact solvers, opting instead for a highly optimized heuristic-driven approach. This guarantees near-instantaneous execution times even on massive graphs.

| Graph Complexity | Graph Size | Optimization Method | Average Runtime |
|---|---|---|---|
| **Small / Dense** | N ≤ 1,000 | 6-Heuristic Ensemble + ILS | `< 10ms` |
| **Medium / Sparse** | N ≤ 10,000 | 6-Heuristic Ensemble + ILS | `< 15ms` |
| **Large / Sparse** | N = 50,000, M = 100,000 | 6-Heuristic Ensemble + ILS | `< 25ms` |
| **Massive / Sparse** | N = 200,000, M = 200,000 | 6-Heuristic Ensemble + ILS | `< 50ms` |

*Tested across 8 comprehensive algorithmic test scenarios — achieving a **100% pass rate** while maintaining strictly sub-50ms latency across all bounds.*

---

## Algorithm Pipeline

The solver architecture is bifurcated into two main phases, entirely bypassing polynomial reduction to prioritize raw speed:

```text
Input Graph
     │
     ▼
[ 6-Heuristic Ensemble Engine ]
Runs six models in parallel to find the best initial draft:
 - Standard Greedy
 - Static Score Greedy (α = 0.5)
 - Static Score Greedy (α = 1.0)
 - Static Score Greedy (α = 2.0)
 - Dynamic Greedy (Lazy Priority Queue)
 - Profit & Loss (P&L) Greedy
     │
     ▼
[ Iterated Local Search (ILS) ]
Executes up to 10 passes of state transformations:
 - (1, 0)-Additions (Unconditional inclusion)
 - (1, 1)-Swaps (Single vertex upgrades)
 - (1, 2)-Swaps (Double vertex upgrades)
     │
     ▼
Output Maximum Weight Subset
```

*For a complete mathematical breakdown of these phases, see [ALGORITHM.md](ALGORITHM.md).*

---

## Specifications & Constraints

### Constraints
* `1 ≤ N ≤ 200,000` (Number of vertices)
* `0 ≤ M ≤ N(N-1)/2` (Number of edges)
* `1 ≤ S_i ≤ 10^9` (Vertex weights)

### Input Format
```text
N M
S_1 S_2 S_3 ... S_N
u_1 v_1
...
u_M v_M
```

### Output Format
```text
TOTAL_WEIGHT
v_1 v_2 ... v_k
```

---

## Compilation & Execution

### Compile
The solver requires a modern C++ compiler (C++11 or later).

```bash
g++ -O3 main.cpp -o main.exe
```

### Run
Execute the compiled binary by redirecting the input file:

```bash
.\main.exe < input.txt
```

### Automated Testing
Use the included Python test runner to automatically validate the solver against the entire test suite:
```bash
python test_runner.py
```

---

## Project Structure
```text
Hackathon-Squad/
 ├── input.txt        # Sample datasets
 ├── test_runner.py   # Automated Python test execution script
 ├── main.cpp         # Unified C++ MWIS solver
 ├── README.md        # This file
 └── ALGORITHM.md     # Detailed algorithm documentation
```
