## 1. Mobile-Air-Travel

```markdown
# ✈️ Mobile Air Travel

A C++ airline simulation game where you manage a network of airports — transporting goods and passengers to earn revenue and expand your fleet.

## Architecture

```
Building (base class)
└── airPort         ← named airport node with location data
mapQueue            ← custom pointer-based queue of airPort objects
Plane / Person / Goods  ← transport entities
```

## Key Concepts
- **Inheritance** — `Building` base class with `airPort` derived class
- **Custom Data Structure** — `mapQueue`: pointer-based queue with insert, remove, and sort operations
- **Header/Source Separation** — classes split across `.hpp`/`.cpp` for modularity
- **Graph Design** — airports connected by distance-weighted edges (planned)
- **OOP Design Patterns** — encapsulation, abstraction across transport entities

## Development Log
- **Nov 18, 2020** — `airPort` + `mapQueue` with insert/remove; identified remove bug with stale pointer references
- **Nov 21, 2020** — Added `Building` base class; fixed remove bug; added sort/display functions; improved documentation

## Build
```bash
g++ -std=c++11 -o air_travel *.cpp
./air_travel
```

## Status
Core data structures complete. Graph integration and full gameplay loop in progress.
