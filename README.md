# Aperture: SAT Based Optimization Tool

Aperture is an anytime and incremental SAT-based optimization tool that supports SAT solving and various SAT based optimization problems, including MaxSAT, Modulo Bit-Vector Optimization (OBV), and Black-Box Optimization - all incrementally under assumptions.
It provides an Aplication Programming Interface (API) as well as a unified input format called ACNF, which allows to specify clauses, constraints, encodings, and solve types in a flexible manner.

# Features

- <b>SAT Solving</b>: Solve Boolean satisfiability problems under assumptions.
- <b>MaxSAT Solving</b>: Solve unweighted and weighted MaxSAT problems under assumptions.
- <b>Modulo Bit-Vector Optimization (OBV)</b>: Optimize modulo bit-vector problems under assumptions.
- <b>Black-Box Optimization</b>: Optimize black-box problems under assumptions.
- <b>ACNF Input Format</b>: A unified input format that allows to specify clauses, constraints, encodings, and solve types in a flexible manner.
- <b>Python API</b>: A Python API that allows to interact with the solver programmatically in python.

## MaxSAT Solving

For MaxSAT solving, Aperture also:

- <b>Supports the WCNF format</b>: which is a standard input format for MaxSAT problems in the MaxSAT community.
- <b>Anytime</b>: intermediate solutions are available (printed) during the solving process, and are guarenteed to be strictly improving overtime. This allows to stop the solving process at any time and obtain the best solution found so far.
- <b>Complete</b>: the final solution for both weighted and unweighted problems is guaranteed to be optimal.
- <b>Incremental</b>: Aperture implements IPAMIR, which is a standard interface for incremental MaxSAT solvers. This allows to solve a sequence of related MaxSAT problems efficiently by reusing information from previous solves.

# Installation

In the root directory of the repository, the following cammands are available:

- `make`: build the solver as a standalone executable.
- `make rs`: build the solver as a standalone executable statically linked.
- `make ls`: build the solver as a static library.
- `make lp`: build the solver as a static library with the -fPIC flag.
- `make lpy`: build the python bindings for the solver. The module (shared library) will be in the `python` directory.

# Usage

The standalone executable can be used by providing an input file in the ACNF or WCNF format. The default mode is WCNF. To select between modes, run with the mode flag:

- `-m 1` for ACNF mode.
- `-m 2` for WCNF mode.

For example, to solve a problem specified in `input.acnf`, you can run:

```
./aperture -m 1 input.acnf
```

# ACNF

The ACNF is an input file format for Aperture. It is a superset of the DIMACS CNF format, i.e. every valid (DIMACS) CNF file is also a valid ACNF file. The ACNF format also allows the following lines:

| Operation                                                    | Line Prefix | Line Content                                                                                          | Example                                                                                                                                                                                                                      |
| ------------------------------------------------------------ | ----------- | ----------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Clause                                                       | $\emptyset$ | \<literals\> 0                                                                                        | 1 2 3 0 <br> add the clause $(x_1 \vee x_2 \vee x_3)$                                                                                                                                                                        |
| New Variable                                                 | n           | \<num_of_new_vars\> 0                                                                                 | n 1 0 <br> create 1 new variable                                                                                                                                                                                             |
| Cardinality Constraint                                       | d           | \<literals\> \<predicate\> \<right_hand_side\> \<optional_selector\> 0                                | d 1 2 3 <= 2 0 <br> the constraint $x_1 + x_2 + x_3 \leq 2$ with no selector                                                                                                                                                 |
| Pseudo-Boolean Constraint                                    | D           | \<weighted_literals\> \<predicate\> \<right_hand_side\> \<optional_selector\> 0                       | D 1 1 2 2 3 3 <= 2 0 <br> the constraint $1 \cdot x_1 + 2 \cdot x_2 + 3 \cdot x_3 \leq 2$ with no selector                                                                                                                   |
| Totalizer Encoding                                           | t           | \<selector\> \<rhs_simplification\> \<literals\> 0                                                    | t 4 2 1 -2 3 0 <br> Encode Totalizer for the literals $\{x_1,\neg x_2,x_3\}$ with the selector literal $x_4$ and perform right hand side simplification for cost $\leq 2$                                                    |
| Generalizer Totalizer Encoding                               | T           | \<selector\> \<rhs_simplification\> \<weighted_literals\> 0                                           | t 4 3 1 1 2 -2 3 3 0 <br> Encode Generalized Totalizer for the weighted literals $\{1 \cdot x_1,2 \cdot \neg x_2,3 \cdot x_3\}$ with the selector literal $x_4$ and perform right hand side simplification for cost $\leq 3$ |
| Solve SAT Under Assumptions                                  | s           | \<assumptions\> 0                                                                                     | s 1 2 3 0 <br> solve SAT under the assumptions: $\{x_1,x_2,x_3\}$                                                                                                                                                            |
| Solve Unweighted MaxSAT Under Assumptions                    | u           | \<num_of_assumptions\> \<num_of_soft_literals\> \<assumptions\> \<soft_literals\> 0                   | u 1 3 1 1 -2 3 0 <br> solve Unweighted MaxSAT under 1 assumption: $\{x_1\}$ for the 3 soft literals: $\{x_1, \neg x_2, x_3\}$                                                                                                |
| Solve Weighted MaxSAT Under Assumptions                      | w           | \<num_of_assumptions\> \<num_of_weighted_soft_literals\> \<assumptions\> \<weighted_soft_literals\> 0 | w 1 3 1 1 1 -2 2 3 3 0 <br> solve Unweighted MaxSAT under 1 assumption: $\{x_1\}$ for the 3 weighted soft literals: $\{1 \cdot x_1, 2 \cdot \neg x_2, 3 \cdot x_3\}$                                                         |
| Solve Modulo Bit-Vector Optimization (OBV) Under Assumptions | b           | \<num_of_assumptions\> \<num_of_targets\> \<assumptions\> \<targets\> 0                               | b 1 3 1 2 3 0 <br> solve OBV under 1 assumption: $\{x_1\}$ for the 3 targets: $\{x_1, x_2, x_3\}$                                                                                                                            |
| Solve Black-Box Optimization Under Assumptions               | g           | \<num_of_assumptions\> \<num_of_observables\> \<assumptions\> \<observables\> 0                       | g 1 3 1 2 3 0 <br> solve Black-Box under 1 assumption: $\{x_1\}$ for the 3 observables: $\{x_1, x_2, x_3\}$                                                                                                                  |

If there is no solve type line after adding clause(s), constraint(s) or encoding(s), the solver will perform a SAT solving under no assumptions.
