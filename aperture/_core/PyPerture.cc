#include "PythonWrapper.h"

namespace nb = nanobind;

using namespace std;
using namespace Aperture;

const char* const __doc__ =
    "Pyperture: A Python interface for the Aperture MaxSAT solver.";

NB_MODULE(_aperture, m) {
  m.doc() = __doc__;

  nb::bind_vector<TLiterals>(m, "lits");
  nb::bind_vector<TWLiterals>(m, "wlits");

  nb::class_<AperturePython>(m, "Solver")
      .def(nb::init<const string&>(), nb::arg("sat_solver") = "glucose")
      .def("add_clause", &AperturePython::AddClause, nb::arg("clause"))
      .def("solve", &AperturePython::Solve,
           nb::arg("assumptions") = TLiterals())
      .def("get_latest_solve_status", &AperturePython::GetLatestSolveStatus)
      .def("get_latest_solution", &AperturePython::GetLatestSolution)
      .def("new_var", &AperturePython::NewVar)
      .def("max_var", &AperturePython::MaxVar)
      .def("lit_value", &AperturePython::LitValue, nb::arg("lit"))
      .def("get_verbosity_level", &AperturePython::GetVerbosityLevel)
      .def("set_verbosity_level", &AperturePython::SetVerbosityLevel,
           nb::arg("level"))
      .def("set_enable_output_coloring",
           &AperturePython::SetEnableOutputColoring, nb::arg("enable"))
      .def("get_latest_error_reason", &AperturePython::GetLatestErrorReason)
      .def("set_param", &AperturePython::SetParam, nb::arg("param_name"),
           nb::arg("value"))
      .def("get_totalizer", &AperturePython::GetTotalizer, nb::arg("lits"),
           nb::arg("selector"), nb::arg("rhs_simplification") = nb::none())
      .def("get_gen_totalizer", &AperturePython::GetGenTotalizer,
           nb::arg("wlits"), nb::arg("selector"),
           nb::arg("rhs_simplification") = nb::none())
      .def("add_constraint_less_than",
           nb::overload_cast<TLiterals&, uint64_t, optional<TLit>>(
               &AperturePython::AddConstraintLessThan),
           nb::arg("lits"), nb::arg("rhs"), nb::arg("selector") = nb::none())
      .def("add_constraint_less_than_equal",
           nb::overload_cast<TLiterals&, uint64_t, optional<TLit>>(
               &AperturePython::AddConstraintLessThanEqual),
           nb::arg("lits"), nb::arg("rhs"), nb::arg("selector") = nb::none())
      .def("add_constraint_equal", &AperturePython::AddConstraintEqual,
           nb::arg("lits"), nb::arg("rhs"), nb::arg("selector") = nb::none())
      .def("add_constraint_greater_than_equal",
           &AperturePython::AddConstraintGreaterThanEqual, nb::arg("lits"),
           nb::arg("rhs"), nb::arg("selector") = nb::none())
      .def("add_constraint_greater_than",
           &AperturePython::AddConstraintGreaterThan, nb::arg("lits"),
           nb::arg("rhs"), nb::arg("selector") = nb::none())
      .def("add_constraint_less_than",
           nb::overload_cast<TWLiterals&, uint64_t, optional<TLit>>(
               &AperturePython::AddConstraintLessThan),
           nb::arg("wlits"), nb::arg("rhs"), nb::arg("selector") = nb::none())
      .def("add_constraint_less_than_equal",
           nb::overload_cast<TWLiterals&, uint64_t, optional<TLit>>(
               &AperturePython::AddConstraintLessThanEqual),
           nb::arg("wlits"), nb::arg("rhs"), nb::arg("selector") = nb::none())
      .def("get_latest_maxsat_value", &AperturePython::GetLatestMaxSATValue)
      .def("is_latest_maxsat_optimal", &AperturePython::IsLatestMaxSATOptimal)
      .def("is_latest_maxsat_fixed_model_value",
           &AperturePython::IsLatestMaxSATFixedModelValue)
      .def("solve_maxsat", &AperturePython::SolveMaxSAT, nb::arg("assumptions"),
           nb::arg("soft_lits"), nb::arg("fix_model_value"),
           nb::arg("callback_on_solution_found") = nb::none())
      .def("solve_weighted_maxsat", &AperturePython::SolveWeightedMaxSAT,
           nb::arg("assumptions"), nb::arg("soft_wlits"),
           nb::arg("fix_model_value"),
           nb::arg("callback_on_solution_found") = nb::none())
      .def("get_latest_black_box_value",
           &AperturePython::GetLatestBlackBoxValue)
      .def("solve_black_box", &AperturePython::SolveBlackBox,
           nb::arg("assumptions"), nb::arg("observables"), nb::arg("pb_func"),
           nb::arg("callback_on_solution_found") = nb::none())
      .def("solve_obv", &AperturePython::SolveOBV, nb::arg("assumptions"),
           nb::arg("targets"));
}
