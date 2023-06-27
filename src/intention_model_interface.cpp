//#include "intention_model_interface.h"
#include <pybind11/pybind11.h>
#include "intention_model.h"

namespace py = pybind11;
constexpr auto byref = py::return_value_policy::reference_internal;

PYBIND11_MODULE(intention_model, m) {
  m.doc() = "optional module docstring";

  py::class_<Intention_Model>(m, "Intention_Model")
    .def(py::init<std::string, const IntentionModelParameters&, int,
         const std::map<int, Eigen::Vector4d>&,
         const std::map<std::string, std::string>&>())
    .def("insertObservation", &Intention_Model::insertObservation, py::call_guard<py::gil_scoped_release>())
    ;
}
