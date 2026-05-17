# Data Lineage Blast Radius (C++)

This project models a directed data-lineage graph and answers:
"If node X changes, what downstream nodes are affected, and how far away are they?"

## What is blast radius?

In this codebase, blast radius means the set of nodes reachable downstream from a change origin, plus the shortest dependency distance (in hops) from that origin.

- Distance 0: the origin itself
- Distance 1: direct children
- Distance 2+: transitive downstream nodes

Example:
- A -> B -> C
- If A changes, blast radius includes A(0), B(1), C(2)

Current project graph (from `src/main.cpp`):

```text
exchange_feed
		|
		v
normalized_prices
	 /           \
	v             v
risk_model   price_history
		|
		v
client_report
```

Example blast radius on this graph:
- If `origin = normalized_prices`, affected nodes are:
	- normalized_prices (0)
	- risk_model (1)
	- price_history (1)
	- client_report (2)

## What `computeBlastRadius` does

`DataLineageGraph::computeBlastRadius(origin)` performs a breadth-first traversal (BFS) from `origin`.

It returns:
- `unordered_map<string, int>` where key is node name
- value is shortest distance from `origin`

Why BFS is used:
- BFS processes by layers, so first time a node is visited, its distance is minimal.
- This gives shortest-hop impact distance naturally.

High-level behavior:
1. Start with `origin` at distance 0.
2. Push direct children with distance 1.
3. Repeatedly pop from queue and visit children.
4. If child is unseen, assign `distance(current) + 1` and enqueue.

Complexity:
- Time: O(V + E) over the reachable subgraph
- Space: O(V) for visited/distance map and queue

## What this project is trying to achieve

The project demonstrates a minimal but practical lineage-impact engine:

- Represent upstream/downstream dependencies as a directed graph.
- Simulate change events and compute impact scope.
- Store audit history (`origin`, `timestamp`, affected nodes).
- Support node-centric tracing (`traceNode`) via an index from node -> event list.
- Keep implementation lightweight with STL and simple assertions for tests.

## Project structure

- `lineage/`: core library (`lineage_core`)
- `src/`: main executable (`main`)
- `test/`: test executable (`test`) using custom assert macros (no GTest)

## Build and run

### Configure and build (app only)

```powershell
cmake -S . -B build
cmake --build build
```

By default, tests are OFF (`BUILD_TESTS=OFF`).

### Run app executable

This project sets custom runtime output directories to `bin/` in the source tree.

For Visual Studio generators, configuration subfolders are used:

```powershell
.\bin\src\Debug\main.exe
```

For Release:

```powershell
.\bin\src\Release\main.exe
```

### Configure and build with tests

```powershell
cmake -S . -B build -DBUILD_TESTS=ON
cmake --build build
```

Run tests:

```powershell
.\bin\test\Debug\test.exe
```

For Release:

```powershell
.\bin\test\Release\test.exe
```

## Useful CMake commands

Incremental build:

```powershell
cmake --build build
```

Clean then build:

```powershell
cmake --build build --clean-first
```

Clean target only:

```powershell
cmake --build build --target clean
```

## Notes

- If `origin` does not exist, `computeBlastRadius` currently uses `_graph.at(origin)` and will throw.
- Tests are intentionally framework-free and use a simple custom assert macro.
