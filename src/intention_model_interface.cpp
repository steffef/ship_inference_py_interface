#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>
#include "intention_model.h"

namespace py = pybind11;

namespace INTENTION_INFERENCE {
    PYBIND11_MODULE(intention_model, m) {
    m.doc() = "Calculates intentions of tracked ships given ais data";

    py::class_<IntentionModel>(m, "IntentionModel")
        .def(py::init<std::string, const IntentionModelParameters&, int,
             const std::map<int, Eigen::Vector4d>&>())
        .def(py::init<std::string, const IntentionModelParameters&, int,
             const std::map<int, Eigen::Vector4d>&,
             const std::map<std::string, std::string>&>())
        .def("insertObservation", &IntentionModel::insertObservation);
    }
}
