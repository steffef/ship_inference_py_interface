#!/usr/bin/env python3
import sys
sys.path.append("build/")
import IntentionModelInterface as im

def setModelParameters(num_ships):
    param = im.IntentionModelParameters()
    param.number_of_network_evaluation_samples = 100000
    param.max_number_of_obstacles = num_ships-1 #must be set to num_ships-1 or else segmantation fault
    param.time_into_trajectory = 10
    param.starting_distance = 10000
    param.starting_cpa_distance = 15000
    param.expanding_dbn.min_time_s = 10
    param.expanding_dbn.max_time_s = 1200
    param.expanding_dbn.min_course_change_rad = 0.18
    param.expanding_dbn.min_speed_change_m_s = 2
    param.ample_time_s.mu = 200
    param.ample_time_s.sigma = 100
    param.ample_time_s.max = 1000
    param.ample_time_s.n_bins = 30 # this value must match the bayesian network
    param.ample_time_s.minimal_accepted_by_ownship = 20
    param.safe_distance_m.mu = 200
    param.safe_distance_m.sigma = 30
    param.safe_distance_m.max = 800
    param.safe_distance_m.n_bins = 30
    param.risk_distance_m.mu = 1800
    param.risk_distance_m.sigma = 500
    param.risk_distance_m.max = 2500
    param.risk_distance_m.n_bins = 30 # this value must match the bayesian network
    param.risk_distance_front_m.mu = 1900
    param.risk_distance_front_m.sigma = 500
    param.risk_distance_front_m.max = 2000
    param.risk_distance_front_m.n_bins = 30
    param.safe_distance_midpoint_m.mu = 600
    param.safe_distance_midpoint_m.sigma = 20
    param.safe_distance_midpoint_m.max = 2500
    param.safe_distance_midpoint_m.n_bins = 30 # this value must match the bayesian network
    param.safe_distance_front_m.mu = 100
    param.safe_distance_front_m.sigma = 50
    param.safe_distance_front_m.max = 1000
    param.safe_distance_front_m.n_bins = 30 # this value must match the bayesian network
    param.change_in_course_rad.minimal_change = 0.18
    param.change_in_speed_m_s.minimal_change = 2
    param.colregs_situation_borders_rad.HO_uncertainty_start = 2.79
    param.colregs_situation_borders_rad.HO_start = 2.96
    param.colregs_situation_borders_rad.HO_stop = -2.96
    param.colregs_situation_borders_rad.HO_uncertainty_stop = -2.79
    param.colregs_situation_borders_rad.OT_uncertainty_start = 1.74
    param.colregs_situation_borders_rad.OT_start = 2.18
    param.colregs_situation_borders_rad.OT_stop = -2.18
    param.colregs_situation_borders_rad.OT_uncertainty_stop = -1.74
    param.ignoring_safety_probability = 0
    param.colregs_compliance_probability = 0.97
    param.good_seamanship_probability = 0.99
    param.unmodeled_behaviour = 0.001
    param.priority_probability["lower"] = 0.05
    param.priority_probability["similar"] = 0.90
    param.priority_probability["higher"] = 0.05
    return param

if __name__ == "__main__":
    num_ships = 2
    filename = "new_1_Case - 09-17-2018, 18-24-32 - 0URFX-60-sec.csv"
    intentionModelFilename = "intention_model_with_risk_of_collision_no_startpoint_3.xdsl"

    parameters = setModelParameters(num_ships)

    print("done")
