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

MAP = 30000             # assumed constant MAP pressure
IAT = 293.0             # assumed constant IAT temperature
η_V = np.linspace(0.5,0.9,676) # speed dependent volumetric efficiencies from 400 - 3200 RPM in increments of 400 RPM for MAP = 30 KPa
#η_V = np.array([1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0]) #  constant volumetric efficiencies 400 - 3200 RPM in increments of 400 RPM

#####################################################################################################################
### ENGINE SPEED ARRAY ###

dN = 3.3                         # speed step
N_start = 300                           # approximate idle speed
N_end = 3000                            # approximate maximum speed
N = np.arange(N_start, N_end + dN, dN)  # set up array of speeds
print(len(N))
print(N.mean())
#####################################################################################################################
### ENGINE CALCULATIONS ###

t_valve = θ_valve/((N*2*np.pi)/60)          # cylinder air inlet valve opening time during induction stoke
fuel_mfr = ρ_E85*Q*NOC                      # fuel mass flow rate
air_mfr = ((MAP*NOC*Vd*N)/(R*IAT*2*60))*η_V # air mass flow rate via speed density method
P = ((2*np.pi*T)/60)*N                      # brake power
ηth = P/(fuel_mfr*NCV_E85)                  # brake thermal efficiency (divide by duty cycle after)
bsfc = fuel_mfr/P                           # brake specific fuel consumption (multiply by duty cycle after)

#####################################################################################################################
### STOICHIOMETRIC CALCULATIONS

t_inj_st = (air_mfr*t_valve)/(fuel_mfr*AFR_st)      # stoichiometric injection duration (using valve opening time)
t_inj_st_2 = (air_mfr)/(fuel_mfr*AFR_st*(N/(2*60))) # stoichiometric injection duration (not using valve opening time)
α_st = t_inj_st_2*(N/(2*60))                        # stoichiometric duty cycle of injection pulses at a given speed

#####################################################################################################################
### PLOTS vs SPEED ###

plt.plot(N, P/1000)
plt.title("ENGINE BRAKE POWER vs ENGINE SPEED (CONSTANT TORQUE = 35 Nm)")
plt.xlabel("ENGINE SPEED (RPM)")
plt.ylabel("BRAKE POWER (kW)")
plt.show()

plt.plot(N, 100*η_V)
plt.title("VOLUMETRIC EFFICIENCY vs ENGINE SPEED (MAP = 30 kPa)")
plt.xlabel("ENGINE SPEED (RPM)")
plt.ylabel("VOLUMETRIC EFFICIENCY (%)")
plt.show()

for i in range (0, len(η_V)):
    plt.plot(N, air_mfr)
plt.title("AIR MASS FLOW RATE vs ENGINE SPEED")
plt.xlabel("ENGINE SPEED (RPM)")
plt.ylabel("AIR MASS FLOW RATE (kg/s)")
plt.show()

plt.plot(N, t_inj_st_2*1000)
plt.title("STOICHIOMETRIC INJECTION DURATION vs ENGINE SPEED")
plt.xlabel("ENGINE SPEED (RPM)")
plt.ylabel("STOICHIOMETRIC INJECTION DURATION (ms)")
plt.show()

plt.plot(N, fuel_mfr * α_st)
plt.title("AVERAGE FUEL MASS FLOW RATE VS ENGINE SPEED")
plt.xlabel("ENGINE SPEED (RPM)")
plt.ylabel("AVERAGE FUEL MASS FLOW RATE (kg/s)")
plt.show()

"""plt.plot(N, α_st)
plt.title("STOICHIOMETRIC INJECTION DUTY CYCLE vs ENGINE SPEED")
plt.xlabel("ENGINE SPEED (RPM)")
plt.ylabel("STOICHIOMETRIC INJECTION DUTY CYCLE")
plt.show()"""

"""for i in range (0, len(α_st)):
    plt.plot(N,100*(ηth / α_st[i]), label="α = " + str(np.around(α_st[i], 4)))

plt.title("THERMAL EFFICIENCY vs ENGINE SPEED FOR DIFFERENT INJECTION CYCLE DURATIONS")
plt.xlabel("ENGINE SPEED (RPM)")
plt.ylabel("THERMAL EFFICIENCY, ηth (%)")
plt.legend(loc="upper left")
plt.show()"""

for i in range (0, len(α_st)):
    plt.scatter(N[i],100*(ηth[i] / α_st[i]))
plt.title("STOICHIOMETRIC THERMAL EFFICIENCIES vs ENGINE SPEED")
plt.xlabel("ENGINE SPEED (RPM)")
plt.ylabel("STOICHIOMETRIC THERMAL EFFICIENCY, ηth (%)")
plt.show()

"""for i in range (0, len(α_st)):
    plt.plot(N, 3.6e9 * bsfc * α_st[i], label="α = " + str(np.around(α_st[i], 4)))
plt.title("BRAKE SPECIFIC FUEL CONSUMPTION vs ENGINE SPEED FOR DIFFERENT INJECTION CYCLE DURATIONS")
plt.xlabel("ENGINE SPEED (RPM)")
plt.ylabel("BSFC (g/kWh)")
plt.legend(loc="upper right")
plt.show()"""

for i in range (0, len(α_st)):
    plt.scatter(N[i], 3.6e9 * bsfc[i] * α_st[i])
plt.title("STOICHIOMETRIC BRAKE SPECIFIC FUEL CONSUMPTION vs ENGINE SPEED")
plt.xlabel("ENGINE SPEED (RPM)")
plt.ylabel("BSFC (g/kWh)")
plt.show()