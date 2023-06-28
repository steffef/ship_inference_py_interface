#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include "intention_model.h"
#include "parameters.h"

namespace py = pybind11;
namespace INTENTION_INFERENCE
{
    PYBIND11_MODULE(IntentionModelInterface, m) {
        m.doc() = "optional module docstring";



        py::class_<IntentionModelParameters>(m, "IntentionModelParameters")
            .def(py::init<>())
            .def_readwrite("number_of_network_evaluation_samples",
                &IntentionModelParameters::number_of_network_evaluation_samples)
            .def_readwrite("max_number_of_obstacles",
                &IntentionModelParameters::max_number_of_obstacles)
            .def_readwrite("time_into_trajectory",
                &IntentionModelParameters::time_into_trajectory)
            .def_readwrite("starting_distance",
                &IntentionModelParameters::starting_distance)
            .def_readwrite("starting_cpa_distance",
                &IntentionModelParameters::starting_cpa_distance);
        // struct{
//             double min_time_s;
//             double max_time_s;
//             double min_course_change_rad;
//             double min_speed_change_m_s;
//         } expanding_dbn;
//         struct{
//             double mu;
//             double sigma;
//             double max;
//             unsigned n_bins;
//             double minimal_accepted_by_ownship;
//         }ample_time_s;
//         struct{
//             double mu;
//         double sigma;
//         double max;
//         unsigned n_bins;
//     }safe_distance_m;
//     struct{
//         double mu;
//         double sigma;
//         double max;
//         unsigned n_bins;
//     }
//     risk_distance_m;
//     struct{
//         double mu;
//         double sigma;
//         double max;
//         unsigned n_bins;
//     }risk_distance_front_m;
//     struct{
//         double mu;
//         double sigma;
//         double max;
//         unsigned n_bins;
//     }safe_distance_midpoint_m;
//     struct{
//         double mu;
//         double sigma;
//         double max;
//         unsigned n_bins;
//     }safe_distance_front_m;
//     struct{
//         double minimal_change;
//     }change_in_course_rad;
//     struct{
//         double minimal_change;
//     }change_in_speed_m_s;
//     struct{
//         double HO_uncertainty_start;
//         double HO_start;
//         double HO_stop;
//         double HO_uncertainty_stop;
//         double OT_uncertainty_start;
//         double OT_start;
//         double OT_stop;
//         double OT_uncertainty_stop;
//     }colregs_situation_borders_rad;
//     double ignoring_safety_probability;
//     double colregs_compliance_probability;
//     double good_seamanship_probability;
//     double unmodeled_behaviour;
//     std::map<std::string, double> priority_probability;
// }

    // py::class_<IntentionModel>(m, "IntentionModel")
        //   .def(py::init<std::string, const IntentionModelParameters&, int,
        //        const std::map<int, Eigen::Vector4d>&,
    //        const std::map<std::string, std::string>&>())
    //   .def("insertObservation", &IntentionModel::insertObservation)
    //   .def("insertObservationRelativeSituation",
    //        &IntentionModel::insertObservationRelativeSituation);
    }
}
