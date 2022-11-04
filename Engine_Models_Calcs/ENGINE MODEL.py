import matplotlib.pyplot as plt
import numpy as np

### THEORETICAL CALCULATIONS FOR CONTROL SYSTEM AIMING FOR STOICHIOMETIC TRANSIENT & STEADY STATE VIA SPEED-DENSITY METHOD ###

#####################################################################################################################
### CONSTANTS ###
T = 35.0                # torque constant
Q = 8.75e-6             # volumetric flow rate of BOSCH
ρ_E85 = 779             # fuel density
NCV_E85 = 30e6          # fuel net calorific value
R = 287.0               # air ideal gas constant
BORE = 67.0e-3          # cylinder bore
STROKE = 42.5e-3        # cylinder stroke
NOC = 4                 # number of cylinders
Vd = np.pi*0.25*(BORE**2)*STROKE*NOC    # volume of one cylinder
AFR_st = 9.75           # ideal stoichiometric air to fuel ratio for E85
θ_valve = 1.134         # valve opening angle

#####################################################################################################################
### VARIABLES ###

MAP = 25012            # assumed constant MAP pressure
IAT = 354.72       # assumed constant IAT temperature
η_V = 0.7 # speed dependent volumetric efficiencies from 400 - 3200 RPM in increments of 400 RPM for MAP = 30 KPa
#η_V = np.array([1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0]) #  constant volumetric efficiencies 400 - 3200 RPM in increments of 400 RPM

#####################################################################################################################
### ENGINE SPEED ARRAY ###

dN = 400                                # speed step
N_start = 400                           # approximate idle speed
N_end = 3200                            # approximate maximum speed
N = np.arange(N_start, N_end + dN, dN)  # set up array of speeds
N = 3000
#####################################################################################################################
### ENGINE CALCULATIONS ###

t_valve = θ_valve/((N*2*np.pi)/60)          # cylinder air inlet valve opening time during induction stoke
print("t", t_valve)
fuel_mfr = ρ_E85*Q*NOC                      # fuel mass flow rate
air_mfr = ((MAP*NOC*Vd*N)/(R*IAT*2*60))*η_V # air mass flow rate via speed density method
print("a",air_mfr)
P = ((2*np.pi*T)/60)*N                      # brake power
ηth = P/(fuel_mfr*NCV_E85)                  # brake thermal efficiency (divide by duty cycle after)
bsfc = fuel_mfr/P                           # brake specific fuel consumption (multiply by duty cycle after)

#####################################################################################################################
### STOICHIOMETRIC CALCULATIONS

t_inj_st = (air_mfr*t_valve)/(fuel_mfr*AFR_st)      # stoichiometric injection duration (using valve opening time)
t_inj_st_2 = (air_mfr)/(fuel_mfr*AFR_st*(N/(2*60))) # stoichiometric injection duration (not using valve opening time)
print("tinj",t_inj_st_2*1000)
α_st = t_inj_st_2*(N/(2*60))                        # stoichiometric duty cycle of injection pulses at a given speed

#####################################################################################################################
### PLOTS vs SPEED ###
