#include <pybind11/pybind11.h>
//#include <pybind11/stl_bind.h> //For binding maps to dicts
#include <pybind11/stl.h>
//#include <pybind11/embed.h>
#include <pybind11/eigen.h>
#include "geometry.h"

namespace py = pybind11;

namespace INTENTION_INFERENCE {
    PYBIND11_MODULE(geometry, m) {
        m.doc() = "optional module docstring";

        m.attr("PX") = 0;
        m.attr("PY") = 1;
        m.attr("CHI") = 2;
        m.attr("U") = 3;

        m.attr("DEG2RAD") = M_PI / 180.0f;
        m.attr("RAD2DEG") = 180.0f / M_PI;

        py::class_<CPA>(m, "CPA")
            .def(py::init<>())
            .def_readwrite("bearing_relative_to_heading",
                           &CPA::bearing_relative_to_heading)
            .def_readwrite("distance_at_CPA",
                           &CPA::distance_at_CPA)
            .def_readwrite("time_untill_CPA",
                           &CPA::time_untill_CPA)
            .def_readwrite("passing_in_front",
                           &CPA::passing_in_front)
            .def_readwrite("has_passed",
                           &CPA::has_passed);

        m.def("evaluateDistance", &evaluateDistance);
        m.def("evaluateCPA", (CPA (*)(const Eigen::Vector4d &, const Eigen::Vector4d &)) &evaluateCPA);
        m.def("evaluateCPA", (CPA (*)(const Eigen::MatrixXd &, const Eigen::Vector4d &, double)) &evaluateCPA);
        m.def("evaluateCPA", py::overload_cast<const Eigen::MatrixXd &, const Eigen::MatrixXd &>(&evaluateCPA));
    }
}
