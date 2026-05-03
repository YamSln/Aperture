#include "../Aperture.h"

using namespace std;
using namespace Aperture;

template <ValidLiteral TLit, ValidWeight TWeight>
SolverStatus Solver<TLit, TWeight>::ObvBS(Lits<TLit> assumps,
                                          Lits<TLit> targets) {
  vector<TLit> assumptions(assumps.begin(), assumps.end());

  CallWhenLeavingScope clear_polarities_when_leaving_scope(
      [&]() { solver_->ClearAllPolarities(); });

  SolverStatus status = SolveInitialSat(assumps, targets);
  if (status != SolverStatus::SAT) {
    return status;
  }

  for (size_t i = 0; i < targets.size(); i++) {
    TLit lit = targets[i];
    assumptions.push_back(-lit);
    if (LitValue(lit) != TLitValue::FALSE) {
      status = SolveLimited(assumptions);
      if (status != SolverStatus::SAT) {
        assumptions.pop_back();
        assumptions.push_back(lit);
      } else {
        SaveLatestSolutionFromSolver();
      }
    }
  }

  return SolverStatus::SAT;
}

template class Solver<int32_t, uint64_t>;