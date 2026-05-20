# Aperture Python API

Aperture is a SAT-based optimization solver providing a Python interface for:
- **SAT solving** – check satisfiability of Boolean formulas
- **MaxSAT solving** – minimize satisfied (weighted) soft literals
- **OBV solving** – optimize modulo bit-vector problems
- **Black-box optimization** – optimize generic objective functions

## Installation

```bash
pip install aperture-sat
```

## Quick Start

```python
import aperture as ap

solver = ap.Solver()
x = solver.new_var()
y = solver.new_var()

solver.add_clause(ap.lits(x, y))  # x OR y

if solver.solve():
    print("SAT")
    print(solver.get_latest_solution())
```

## Supported Solvers

- `"topor"` 
- `"cadical"`
- `"glucose"` (default)
- `"kissat"` – initial SAT query only

## Core Methods

| Method | Purpose |
|--------|---------|
| `new_var()` | Create a new Boolean variable |
| `add_clause(lits)` | Add a clause |
| `solve(assumptions=[])` | Solve SAT |
| `solve_maxsat(assumptions, soft_lits, fix_model_value)` | Solve MaxSAT |
| `solve_weighted_maxsat(assumptions, soft_wlits, fix_model_value)` | Solve weighted MaxSAT |
| `solve_obv(assumptions, targets)` | Optimize bit-vectors |
| `solve_black_box(assumptions, observables, pb_func)` | Black-box optimization |
| `get_latest_solution()` | Get solution |
| `get_latest_solve_status()` | Get status ("SAT", "UNSAT", "ERROR", "UNKNOWN") |

## Constraints

Add cardinality and pseudo-Boolean constraints:
- `add_constraint_less_than((W)lits, rhs)`
- `add_constraint_less_than_equal((W)lits, rhs)`
- `add_constraint_equal((W)lits, rhs)`
- `add_constraint_greater_than_equal((W)lits, rhs)`
- `add_constraint_greater_than((W)lits, rhs)`

All methods return `bool` and support weighted variants with `(weight, literal)` pairs (wlits).

## Documentation

For further information and examples, see the notebook in the [docs/](../docs/) directory. ReadTheDocs documentation will be available in the future.
