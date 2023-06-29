#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h> //This autamtiacally maps map tupes to dicts
#include <pybind11/eigen.h>
#include "intention_model.h"
#include "parameters.h"

namespace py = pybind11;

namespace INTENTION_INFERENCE {
    PYBIND11_MODULE(IntentionModelInterface, m) {
        m.doc() = "optional module docstring";

        py::class_<decltype(IntentionModelParameters::expanding_dbn)>(m, "expanding_dbn")
            .def(py::init<>())
            .def_readwrite("min_time_s",
                           &decltype(IntentionModelParameters::expanding_dbn)::min_time_s)
            .def_readwrite("max_time_s",
                           &decltype(IntentionModelParameters::expanding_dbn)::max_time_s)
            .def_readwrite("min_course_change_rad",
                           &decltype(IntentionModelParameters::expanding_dbn)::min_course_change_rad)
            .def_readwrite("min_speed_change_m_s",
                           &decltype(IntentionModelParameters::expanding_dbn)::min_speed_change_m_s);

        py::class_<decltype(IntentionModelParameters::ample_time_s)>(m, "ample_time_s")
            .def(py::init<>())
            .def_readwrite("mu",
                           &decltype(IntentionModelParameters::ample_time_s)::mu)
            .def_readwrite("sigma",
                           &decltype(IntentionModelParameters::ample_time_s)::sigma)
            .def_readwrite("max",
                           &decltype(IntentionModelParameters::ample_time_s)::max)
            .def_readwrite("n_bins",
                           &decltype(IntentionModelParameters::ample_time_s)::n_bins)
            .def_readwrite("minimal_accepted_by_ownship",
                           &decltype(IntentionModelParameters::ample_time_s)::minimal_accepted_by_ownship);

        py::class_<decltype(IntentionModelParameters::safe_distance_m)>(m, "safe_distance_m")
            .def(py::init<>())
            .def_readwrite("mu",
                           &decltype(IntentionModelParameters::safe_distance_m)::mu)
            .def_readwrite("sigma",
                           &decltype(IntentionModelParameters::safe_distance_m)::sigma)
            .def_readwrite("max",
                           &decltype(IntentionModelParameters::safe_distance_m)::max)
            .def_readwrite("n_bins",
                           &decltype(IntentionModelParameters::safe_distance_m)::n_bins);

        py::class_<decltype(IntentionModelParameters::risk_distance_m)>(m, "risk_distance_m")
            .def(py::init<>())
            .def_readwrite("mu",
                           &decltype(IntentionModelParameters::risk_distance_m)::mu)
            .def_readwrite("sigma",
                           &decltype(IntentionModelParameters::risk_distance_m)::sigma)
            .def_readwrite("max",
                           &decltype(IntentionModelParameters::risk_distance_m)::max)
            .def_readwrite("n_bins",
                           &decltype(IntentionModelParameters::risk_distance_m)::n_bins);

        py::class_<decltype(IntentionModelParameters::risk_distance_front_m)>(m, "risk_distance_front_m")
            .def(py::init<>())
            .def_readwrite("mu",
                           &decltype(IntentionModelParameters::risk_distance_front_m)::mu)
            .def_readwrite("sigma",
                           &decltype(IntentionModelParameters::risk_distance_front_m)::sigma)
            .def_readwrite("max",
                           &decltype(IntentionModelParameters::risk_distance_front_m)::max)
            .def_readwrite("n_bins",
                           &decltype(IntentionModelParameters::risk_distance_front_m)::n_bins);

        py::class_<decltype(IntentionModelParameters::safe_distance_midpoint_m)>(m, "safe_distance_midpoint_m")
            .def(py::init<>())
            .def_readwrite("mu",
                           &decltype(IntentionModelParameters::safe_distance_midpoint_m)::mu)
            .def_readwrite("sigma",
                           &decltype(IntentionModelParameters::safe_distance_midpoint_m)::sigma)
            .def_readwrite("max",
                           &decltype(IntentionModelParameters::safe_distance_midpoint_m)::max)
            .def_readwrite("n_bins",
                           &decltype(IntentionModelParameters::safe_distance_midpoint_m)::n_bins);

        py::class_<decltype(IntentionModelParameters::safe_distance_front_m)>(m, "safe_distance_front_m")
            .def(py::init<>())
            .def_readwrite("mu",
                           &decltype(IntentionModelParameters::safe_distance_front_m)::mu)
            .def_readwrite("sigma",
                           &decltype(IntentionModelParameters::safe_distance_front_m)::sigma)
            .def_readwrite("max",
                           &decltype(IntentionModelParameters::safe_distance_front_m)::max)
            .def_readwrite("n_bins",
                           &decltype(IntentionModelParameters::safe_distance_front_m)::n_bins);

        py::class_<decltype(IntentionModelParameters::change_in_course_rad)>(m, "change_in_course_rad")
            .def(py::init<>())
            .def_readwrite("minimal_change",
                           &decltype(IntentionModelParameters::change_in_course_rad)::minimal_change);

        py::class_<decltype(IntentionModelParameters::change_in_speed_m_s)>(m, "change_in_speed_m_s")
            .def(py::init<>())
            .def_readwrite("minimal_change",
                           &decltype(IntentionModelParameters::change_in_speed_m_s)::minimal_change);

        py::class_<decltype(IntentionModelParameters::colregs_situation_borders_rad)>(m, "colregs_situation_borders_rad")
            .def(py::init<>())
            .def_readwrite("HO_uncertainty_start",
                           &decltype(IntentionModelParameters::colregs_situation_borders_rad)::HO_uncertainty_start)
            .def_readwrite("HO_start",
                           &decltype(IntentionModelParameters::colregs_situation_borders_rad)::HO_start)
            .def_readwrite("HO_stop",
                           &decltype(IntentionModelParameters::colregs_situation_borders_rad)::HO_stop)
            .def_readwrite("HO_uncertainty_stop",
                           &decltype(IntentionModelParameters::colregs_situation_borders_rad)::HO_uncertainty_stop)
            .def_readwrite("OT_uncertainty_start",
                           &decltype(IntentionModelParameters::colregs_situation_borders_rad)::OT_uncertainty_start)
            .def_readwrite("OT_start",
                           &decltype(IntentionModelParameters::colregs_situation_borders_rad)::OT_start)
            .def_readwrite("OT_stop",
                           &decltype(IntentionModelParameters::colregs_situation_borders_rad)::OT_stop)
            .def_readwrite("OT_uncertainty_stop",
                           &decltype(IntentionModelParameters::colregs_situation_borders_rad)::OT_uncertainty_stop);

        py::bind_map<std::map<std::string, double>>(m, "StringDoubleMap");

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
                           &IntentionModelParameters::starting_cpa_distance)
            .def_readwrite("expanding_dbn",
                           &IntentionModelParameters::expanding_dbn)
            .def_readwrite("ample_time_s",
                           &IntentionModelParameters::ample_time_s)
            .def_readwrite("safe_distance_m",
                           &IntentionModelParameters::safe_distance_m)
            .def_readwrite("risk_distance_m",
                           &IntentionModelParameters::risk_distance_m)
            .def_readwrite("risk_distance_front_m",
                           &IntentionModelParameters::risk_distance_front_m)
            .def_readwrite("safe_distance_midpoint_m",
                           &IntentionModelParameters::safe_distance_midpoint_m)
            .def_readwrite("safe_distance_front_m",
                           &IntentionModelParameters::safe_distance_front_m)
            .def_readwrite("change_in_course_rad",
                           &IntentionModelParameters::change_in_course_rad)
            .def_readwrite("change_in_speed_m_s",
                           &IntentionModelParameters::change_in_speed_m_s)
            .def_readwrite("colregs_situation_borders_rad",
                           &IntentionModelParameters::colregs_situation_borders_rad)
            .def_readwrite("ignoring_safety_probability",
                           &IntentionModelParameters::ignoring_safety_probability)
            .def_readwrite("colregs_compliance_probability",
                           &IntentionModelParameters::colregs_compliance_probability)
            .def_readwrite("good_seamanship_probability",
                           &IntentionModelParameters::good_seamanship_probability)
            .def_readwrite("unmodeled_behaviour",
                           &IntentionModelParameters::unmodeled_behaviour)
            .def_readwrite("priority_probability",
                           &IntentionModelParameters::priority_probability);

    // py::class_<IntentionModel>(m, "IntentionModel")
    //       .def(py::init<std::string, const IntentionModelParameters&, int,
    //            const std::map<int, Eigen::Vector4d>&,
    //        const std::map<std::string, std::string>&>())
    //   .def("insertObservation", &IntentionModel::insertObservation)
    //   .def("insertObservationRelativeSituation",
    //        &IntentionModel::insertObservationRelativeSituation);
    }
}
