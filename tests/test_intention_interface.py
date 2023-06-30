#!/usr/bin/env python3
import sys
sys.path.append("build/")
import IntentionModelInterface as im
import test_parameters_interface as param

import numpy as np
import datetime
from typing import Dict, List

def readFileToVecs(filename: str, mmsi_vec: List[int], time_vec: List[float], x_vec: List[float], y_vec: List[float], sog_vec: List[float], cog_vec: List[float]):
    filename_open = "ship_intention_inference/files/" + filename

    with open(filename_open, 'r') as file:
        lines = file.readlines()

        for line in lines[1:]:
            tokens = line.strip().split(',')
            mmsi = int(tokens[0])

            time_str = tokens[1]
            time_dt = datetime.datetime.strptime(time_str, "%Y-%m-%d %H:%M:%S")
            time_d = time_dt.timestamp()

            x = float(tokens[2])
            y = float(tokens[3])
            sog = float(tokens[4])
            cog = float(tokens[5])

            mmsi_vec.append(mmsi)
            x_vec.append(x)
            y_vec.append(y)
            sog_vec.append(sog)

            cog_rad = cog * (3.14159 / 180)  # Convert degrees to radians
            cog_vec.append(cog_rad)

            if not time_vec:
                time_vec.append(time_d)
            else:
                time_from_null = time_d - time_vec[0]
                time_vec.append(time_from_null)

        if time_vec:
            time_vec[0] = 0
        else:
            print("Could not open file")

def vecsToShipStateVectorMap(ship_state: List[Dict[int, np.ndarray]], unique_time_vec: List[float], num_ships: int, mmsi_vec: List[int], time_vec: List[float], x_vec: List[float], y_vec: List[float], sog_vec: List[float], cog_vec: List[float]):
    for i in range(len(time_vec)//num_ships):
        current_ship_states = {}
        for c in range(num_ships):
            index = c * len(time_vec)//num_ships + i
            states = np.array([x_vec[index], y_vec[index], cog_vec[index], sog_vec[index]])
            current_ship_states[mmsi_vec[index]] = states
        ship_state.append(current_ship_states)
        unique_time_vec.append(time_vec[i])

def getShipList(mmsi_vec: List[int]) -> List[int]:
    ship_list = list(set(mmsi_vec))
    return ship_list

if __name__ == "__main__":
    num_ships = 2
    filename = "new_1_Case - 09-17-2018, 18-24-32 - 0URFX-60-sec.csv"
    intentionModelFilename = "ship_intention_inference/intention_model_with_risk_of_collision_no_startpoint_3.xdsl"

    ship_state = []
    mmsi_vec = []
    time_vec = []
    x_vec = []
    y_vec = []
    sog_vec = []
    cog_vec = []
    unique_time_vec = []
    ship_state: List[Dict[int, np.ndarray]] = []

    readFileToVecs(filename, mmsi_vec, time_vec, x_vec, y_vec, sog_vec, cog_vec)
    vecsToShipStateVectorMap(ship_state, unique_time_vec, num_ships, mmsi_vec,\
                             time_vec, x_vec, y_vec, sog_vec, cog_vec)
    ship_list = getShipList(mmsi_vec)

    parameters = param.setModelParameters(num_ships)
    ship_intentions = {}

    timestep = 0
    inserted = False

    while not inserted:
        for i in range(num_ships):
            # print(ship_state[timestep][ship_list[1]]["PX"] - ship_state[timestep][ship_list[2]]["PX"])
            # dist = evaluateDistance(ship_state[timestep][ship_list[1]]["PX"] - ship_state[timestep][ship_list[2]]["PX"], ship_state[timestep][ship_list[1]]["PY"] - ship_state[timestep][ship_list[2]]["PY"])
            # print("dist:", dist)
            # CPA = evaluateCPA(ship_state[timestep][ship_list[1]], ship_state[timestep][ship_list[2]])
            # print("CPA dist:", CPA["distance_at_CPA"])
            # if dist < parameters.starting_distance and sog_vec[timestep] > 0.1 and sog_vec[len(unique_time_vec) + timestep] > 0.1 and timestep > 0:  # and CPA["distance_at_CPA"] < parameters.starting_cpa_distance: #only checks the speed for two ships
            print("intentionModelFilename", intentionModelFilename)
            print("parameters", parameters)
            print("ship_list[i]", ship_list[i])
            print("ship_state[timestep]", ship_state[timestep])
            ship_intentions[ship_list[i]] = im.IntentionModel(intentionModelFilename, parameters, ship_list[i], ship_state[timestep])
            inserted = True
        timestep += 1

    print("done")
