% This file is automatically generated by EcoNet(http://eco.engr.uga.edu).
% Run this M-file in Matlab to load all results into Matlab environment.
%
% ================== EcoNet Model ===================
% * ->  A c=1
% A ->  B c=1
% A ->  C c=1
% C ->  B c=1
% B ->  * c=1
% 
% A = 1
% B = 1
% C = 1
% % ===================================================


% Compartment Names (NM):

NM = { 'A'
'B'
'C'
};

% Environmental inputs (Z):

Z = [ 1.000000000000000e+00
0.000000000000000e+00
0.000000000000000e+00
];

% Environmental Outputs (Y):

Y = [ 0.000000000000000e+00
1.000000000000000e+00
0.000000000000000e+00
];

% Initial storage values (IC):

IC = [ 1.000000000000000e+00
1.000000000000000e+00
1.000000000000000e+00
];

%  Final storage values - assumed Steady-state (SS):

SS = [ 5.000000000000000e-01
1.000000000000000e+00
5.000000000000001e-01
];

% Output throughflow (T):

T = [ 1.000000000000000e+00
1.000000000000000e+00
5.000000000000001e-01
];

% Input hroughflow (TP):

TP = [ 1.000000000000000e+00
1.000000000000000e+00
5.000000000000000e-01
];

% Residence times (RT):

RT = [ 5.000000000000000e-01
1.000000000000000e+00
1.000000000000000e+00
];

% Trophic Levels (TL):

TL = [ 1.000000000000000e+00
1.500000000000000e+00
2.000000000000000e+00
];

% Stoichiometric matrix (SM):

SM = [     1.000000000000000e+00   -1.000000000000000e+00   -1.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00
    0.000000000000000e+00    1.000000000000000e+00    0.000000000000000e+00    1.000000000000000e+00   -1.000000000000000e+00
    0.000000000000000e+00    0.000000000000000e+00    1.000000000000000e+00   -1.000000000000000e+00    0.000000000000000e+00

];

% Adjacency Matrix (A):

A = [     0.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00
    1.000000000000000e+00    0.000000000000000e+00    1.000000000000000e+00
    1.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00

];

% Flow Matrix (F):

F = [     0.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00
    5.000000000000000e-01    0.000000000000000e+00    5.000000000000001e-01
    5.000000000000000e-01    0.000000000000000e+00    0.000000000000000e+00

];

% Normalized flow matrix (G):

G = [     0.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00
    5.000000000000000e-01    0.000000000000000e+00    1.000000000000000e+00
    5.000000000000000e-01    0.000000000000000e+00    0.000000000000000e+00

];

% Throughflow Analysis (N):

N = [     1.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00
    1.000000000000000e+00    1.000000000000000e+00    1.000000000000000e+00
    5.000000000000000e-01    0.000000000000000e+00    1.000000000000000e+00

];

% Normalized flow matrix - output oriented (GP):

GP = [     0.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00
    5.000000000000000e-01    0.000000000000000e+00    5.000000000000001e-01
    9.999999999999998e-01    0.000000000000000e+00    0.000000000000000e+00

];

% Throughflow Analysis - output oriented (NP):

NP = [     1.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00
    1.000000000000000e+00    1.000000000000000e+00    5.000000000000001e-01
    9.999999999999998e-01    0.000000000000000e+00    1.000000000000000e+00

];

% Partial turnover rate matrix (C):

C = [    -2.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00
    1.000000000000000e+00   -1.000000000000000e+00    1.000000000000000e+00
    1.000000000000000e+00    0.000000000000000e+00   -1.000000000000000e+00

];

% Storage Analysis (S):

S = [     5.000000000000000e-01    0.000000000000000e+00    0.000000000000000e+00
    1.000000000000000e+00    1.000000000000000e+00    1.000000000000000e+00
    5.000000000000000e-01    0.000000000000000e+00    1.000000000000000e+00

];

% Partial Turnover Rates - output oriented (CP):

CP = [    -2.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00
    5.000000000000000e-01   -1.000000000000000e+00    5.000000000000001e-01
    9.999999999999998e-01    0.000000000000000e+00   -1.000000000000000e+00

];

% Storage Analysis - output oriented (SP):

SP = [     5.000000000000000e-01    0.000000000000000e+00    0.000000000000000e+00
    5.000000000000000e-01    1.000000000000000e+00    5.000000000000001e-01
    4.999999999999999e-01    0.000000000000000e+00    1.000000000000000e+00

];

% Utility series matrix (D):

D = [     0.000000000000000e+00   -5.000000000000000e-01   -5.000000000000000e-01
    5.000000000000000e-01    0.000000000000000e+00    5.000000000000001e-01
    9.999999999999998e-01   -1.000000000000000e+00    0.000000000000000e+00

];

% Utility Analysis (U):

U = [     6.666666666666669e-01   -0.000000000000000e+00   -3.333333333333333e-01
    4.444444444444444e-01    6.666666666666666e-01    1.111111111111111e-01
    2.222222222222220e-01   -6.666666666666666e-01    5.555555555555555e-01

];

% Control matrix I (CD):

CD = [     0.000000000000000e+00   -1.000000000000000e+00   -9.999999999999998e-01
    1.000000000000000e+00    0.000000000000000e+00    1.000000000000000e+00
    9.999999999999998e-01   -1.000000000000000e+00    0.000000000000000e+00

];

% Control matrix II (CR):

CR = [     0.000000000000000e+00    1.000000000000000e+00    1.000000000000000e+00
    0.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00
    0.000000000000000e+00    1.000000000000000e+00    0.000000000000000e+00

];

% Compact NEA matrix (Nea):

Nea = [     0.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00    1.000000000000000e+00    5.000000000000000e-01
    5.000000000000000e-01    0.000000000000000e+00    5.000000000000001e-01    0.000000000000000e+00    1.000000000000000e+00
    5.000000000000000e-01    0.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00    5.000000000000001e-01
    0.000000000000000e+00    1.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00    0.000000000000000e+00

];

% Link density (LD):

LD = 1.000000000000000e+00

% Connectance (CON):

CON = 3.333333333333333e-01

% Total system throughflow (TST):

TST = 2.500000000000000e+00

% Flow (Finn's) Cycling Index (FCI):

FCI = 0.000000000000000e+00

% Storage Cycling Index (SCI):

SCI = 0.000000000000000e+00

% Indirect to Direct Effects Ratio, Original (IE):

IE = 2.500000000000000e-01

% Indirect to Direct Effects Ratio, Realized (IEz):

IEz = 5.000000000000000e-01

% Indirect to Direct Effects Ratio, Revised (IEt):

IEt = 3.333333333333333e-01

% Indirect effects index, Original (IEI):

IEI = 2.000000000000000e-01

% Indirect effects index, Realized (IEIz):

IEIz = 3.333333333333333e-01

% Indirect effects index, Revised (IEIt):

IEIt = 2.500000000000000e-01

% Ascendency (ASC):

ASC = 5.825742227201614e+00

% Development Capacity (DC):

DC = 7.825742227201614e+00

% Synergism Index (SYN):

SYN = 2.666666666666666e+00

% Mutualism index (MUT):

MUT = 3.500000000000000e+00

%  Aggradation index (AGG):

AGG = 2.500000000000000e+00

% Homogenization index (HM):

HM = 2.055748754390105e+00

% Homogenization index - output based (HMP):

HMP = 2.055748754390105e+00





disp(' ')
disp('You have successfully imported the following EcoNet results:')
disp(' ')
disp(' === VECTOR VALUES === ')
disp(' ')
disp('Environmental inputs (Z):')
disp('Environmental Outputs (Y):')
disp('Initial storage values (IC):')
disp('Final storage values - assumed Steady-state (SS):')
disp('Output throughflow (T):')
disp('Input hroughflow (TP):')
disp('Residence times (RT):')
disp('Trophic Levels (TL):')
disp(' ')
disp(' === MATRIX VALUES === ')
disp(' ')
disp('Adjacency Matrix (A):')
disp('Flow Matrix (F):')
disp('Normalized flow matrix (G):')
disp('Throughflow Analysis (N):')
disp('Normalized flow matrix - output oriented (GP):')
disp('Throughflow Analysis - output oriented (NP):')
disp('Partial turnover rate matrix (C):')
disp('Storage Analysis (S):')
disp('Partial Turnover Rates - output oriented (CP):')
disp('Storage Analysis - output oriented (SP):')
disp('Utility series matrix (D):')
disp('Utility Analysis (U):')
disp('Control matrix I (CD):')
disp('Control matrix II (CR):')
disp('Compact Nea matrix (Nea):')
disp(' ')
disp(' === SCALAR VALUES === ')
disp(' ')
disp('Link density (LD):')
disp('Connectance (CON):')
disp('Total system throughflow (TST):')
disp('Flow (Finns) Cycling Index (FCI):')
disp('Storage Cycling Index (SCI):')
disp('Indirect to Direct Effects Ratio, Original (IE):')
disp('Indirect to Direct Effects Ratio, Realized (IEz):')
disp('Indirect to Direct Effects Ratio, Revised (IEt):')
disp('Indirect effects index, Original (IEI):')
disp('Indirect effects index, Realized (IEIz):')
disp('Indirect effects index, Revised (IEIt):')
disp('Ascendency (ASC):')
disp('Development Capacity (DC):')
disp('Synergism Index (SYN):')
disp('Mutualism index (MUT):')
disp('Aggradation index (AGG):')
disp('Homogenization index (HM):')
disp('Homogenization index - output based (HMP):')
disp(' ')