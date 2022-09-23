% Based on camshaft positions
% 20 BTDC for 3000RPM 

ignition_1 =  160
ignition_2 = 250
ignition_3 = 340
ignition_4 = 70

ignition_dwell_time = 0.003; % 3 ms

injection_start_1 = 120; %BTDC
injection_start_2 = 210;
injection_start_3 = 300;
injection_start_4 = 30;
injection_end_1 = 144;
injection_end_2 = 234;
injection_end_3 = 324;
injection_end_4 = 54;

injection_duration = 24;

% Injection time calculations
manifold_pressure = 100000; %Pascals
intake_air_temp = 300; %K
engine_displacement = 0.000599; %m3
volumetric_efficiency = 1;
fuel_mass_flow_rate = 1; %??
inj_valve_open_time = 1.134; %rad
AFR = 9.75;

lambda_v = 0.9;
fuel_temp = 40;

cam_angle = 0;

rpm = 3000;