#include <pybind11/pybind11.h>
#include "intention_model.h"
#include "parameters.h"
#include <Eigen/Dense>

namespace py = pybind11;
namespace INTENTION_INFERENCE
{
  PYBIND11_MODULE(intention_model_interface, m) {
    m.doc() = "optional module docstring";
    py::class_<IntentionModelParameters>(m, "IntentionModelParameters");

    py::class_<IntentionModel>(m, "IntentionModel")
      .def(py::init<std::string, const IntentionModelParameters&, int,
           const std::map<int, Eigen::Vector4d>&,
           const std::map<std::string, std::string>&>())
      .def("insertObservation", &IntentionModel::insertObservation)
      .def("insertObservationRelativeSituation",
           &IntentionModel::insertObservationRelativeSituation);
  }
}
