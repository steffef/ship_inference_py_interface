#!/usr/bin/env python3
import sys
sys.path.append("build/")
import intention_model as im
import geometry as geom
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


def getShipListIndex(mmsi, ship_list):
    index = -1
    for i in range(len(ship_list)):
        if mmsi == ship_list[i]:
            index = i
            break
    if index == -1:
        print("ERROR: mmsi not found in ship list")
    return index

def writeIntentionToFile(timestep, parameters, filename, ship_intentions, ship_state, ship_list, unique_time_vec, x_vec, y_vec):
    intentionFile = open("ship_intention_inference/intention_files/nostart_intention_" + filename, "w")
    intentionFile.write("mmsi,x,y,time,colreg_compliant,good_seamanship,unmodeled_behaviour,has_turned_portwards,has_turned_starboardwards,change_in_speed,is_changing_course,CR_PS,CR_SS,HO,OT_en,OT_ing,priority_lower,priority_similar,priority_higher,risk_of_collision,current_risk_of_collision,start")

    risk_of_collision = {}
    current_risk = {}
    new_initial_ship_states = {}
    last_ship_states = {}
    check_changing_course = {}

    for ship_id in ship_list:
        risk_of_collision[ship_id] = False
        current_risk[ship_id] = False
        new_initial_ship_states[ship_id] = ship_state[timestep][ship_id]
        last_ship_states[ship_id] = new_initial_ship_states[ship_id]

    old_ship_states = {}
    start = False
    new_timestep = False

    for i in range(timestep, len(unique_time_vec)):
        print("timestep:", i)
        new_timestep = True

        for ship_id, current_ship_intention_model in ship_intentions.items():
            print("ship_id:", ship_id)
            j = getShipListIndex(ship_id, ship_list)
            current_ship_intention_model.insertObservation(parameters \
                                                           ,start\
                                                           , new_timestep \
                                                           , check_changing_course \
                                                           , current_risk \
                                                           , new_initial_ship_states \
                                                           , risk_of_collision \
                                                           , ship_state[i] \
                                                           , ship_state \
                                                           , ship_state[i - 1] \
                                                           , old_ship_states \
                                                           , ship_list \
                                                           , False \
                                                           , unique_time_vec[i] \
                                                           , x_vec[len(unique_time_vec) * j + i] \
                                                           , y_vec[len(unique_time_vec) * j + i] \
                                                           , intentionFile\
                                                           )
            new_timestep = False

    intentionFile.close()
    print("Finished writing intentions to file")

if __name__ == "__main__":
    num_ships = 2
    filename = "new_1_Case - 08-09-2018, 19-12-24 - 4XJ3B-60-sec.csv"
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
            print(ship_state[timestep][ship_list[1]][geom.PX] - ship_state[timestep][ship_list[0]][geom.PX])
            dist = geom.evaluateDistance(ship_state[timestep][ship_list[1]][geom.PX] - ship_state[timestep][ship_list[0]][geom.PX],\
                                         ship_state[timestep][ship_list[1]][geom.PY] - ship_state[timestep][ship_list[0]][geom.PY])
            print("dist:", dist)
            CPA = geom.evaluateCPA(ship_state[timestep][ship_list[1]], ship_state[timestep][ship_list[0]])
            print("CPA dist:", CPA.distance_at_CPA)
            if dist < parameters.starting_distance and sog_vec[timestep] > 0.1 and sog_vec[len(unique_time_vec) + timestep] > 0.1 and timestep > 0:  # and CPA["distance_at_CPA"] < parameters.starting_cpa_distance: #only checks the speed for two ships
                ship_intentions[ship_list[i]] = im.IntentionModel(intentionModelFilename, parameters, ship_list[i], ship_state[timestep])
                inserted = True
        timestep += 1

    writeIntentionToFile(timestep, parameters,filename, ship_intentions, ship_state, ship_list, unique_time_vec, x_vec,y_vec); #intentionfile is called: intention_<filename>  NB: not all intentions!

    for i in range(5):
        for key, item in ship_state[i].items():
            print(key, "->", item)
            print("time:", unique_time_vec[i])

    print("done")
