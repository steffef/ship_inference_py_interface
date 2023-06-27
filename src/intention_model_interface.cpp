//#include "intention_model_interface.h"
#include <pybind11/pybind11.h>
#include <map>
#include "Eigen/Dense"
#include "intention_model.h"
#include "parameters.h"

namespace py = pybind11;
constexpr auto byref = py::return_value_policy::reference_internal;
namespace INTENTION_INFERENCE
{
  PYBIND11_MODULE(intention_model, m) {
    m.doc() = "optional module docstring";
    py::class_<IntentionModelParameters>(m, "IntentionModelParameters");

    py::class_<IntentionModel>(m, "IntentionModel")
      .def(py::init<std::string, const IntentionModelParameters&, int,
           const std::map<int, Eigen::Vector4d>&,
           const std::map<std::string, std::string>&>())
      .def("insertObservation", &IntentionModel::insertObservation)
      .def("insertObservationRelativeSituation", &IntentionModel::insertObservationRelativeSituation);
  }
}
