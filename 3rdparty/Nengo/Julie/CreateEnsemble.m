
function []= CreateEnsemble
% Setup the variables for a neural network.

%% INITIALIZE PARAMETERS
% There are the same for all the simulation and should be set only once

N                = 1000;  % Number of neurons in each integrator
tref             = 0.001; % Refractory period of neurons
trc              = 0.02;  % RC time constant of neurons

%% CREATE INTEGRATORS

p = [N;      %  Number of neurons
    1;       % 	radius = 1;
    0.05;    % 	dRadius = radius*0.05;
    -1;      % 	threshRangeMin = radius*(-1);
    1;       % 	threshRangeMax = radius*( 1);
    0.2;     % 	satRangeMin = 0.2; %kHz - Smallest maximum firing rate
    0.4;     % 	satRangeMax = 0.4; %kHz - Largest maximum firing rate
    tref;    % 	tauRefractory = 0.001;  %% 1 ms
    trc;     % 	tauRC = 0.02;           %% 20 ms - RC time constant
    0.1];    % 	noise = 0.1;            %% necessary !!!!!

ensvectX = createensemble(p);
ensvectY = createensemble(p);
ensvectt = [ensvectX ensvectY];
NumEns   = 2;

%% SET UP VECTORS

% Gain and Jbias vectors.

    
Gain    = zeros(N, NumEns);
Jbias   = zeros(N, NumEns);

for m=1:NumEns
    Gain(:, m)  = ensvectt(1:N, m);
    Jbias(:, m) = ensvectt(N+1:2*N, m);
end

% Encoding and Decoding vectors.
    
DECVECS     = zeros(2, N);
ENCVECS     = zeros(2, N);

In_Start    = 1:NumEns;

for l=1:NumEns;
    DECVECS(In_Start(l), 1:N) = ensvectt(3*N+1:end,l)';
    ENCVECS(In_Start(l), 1:N) = ensvectt(2*N+1:3*N,l)';
end



savefile = 'save1000.mat';
ws1.time = [];
ws1.signals.dimensions = [1 1];
ws1.signals.values = N;
ws2.time = [];
ws2.signals.dimensions = [N NumEns];
ws2.signals.values = Gain;
ws3.time = [];
ws3.signals.dimensions = [N NumEns];
ws3.signals.values = Jbias;
ws4.time = [];
ws4.signals.dimensions = [NumEns N];
ws4.signals.values = DECVECS;
ws5.time = [];
ws5.signals.dimensions = [NumEns N];
ws5.signals.values = ENCVECS;
save(savefile, 'ws1', 'ws2', 'ws3', 'ws4', 'ws5')


%% FUNCTION TO CREATE ENSEMBLE VECTORS: GAIN, JBIAS, ENCODING AND DECODING VECTORS
function ensvect = createensemble(p)	

N        = p(1);
Radius   = p(2);
dR       = p(3);
TRange   = [p(4), p(5)];
SRange   = [p(6), p(7)];
tref     = p(8);
trc      = p(9);
noise    = p(10);
epsilon  = trc / tref;
maxFR    = 1.0 / tref; % maximum firing frequency (refractory period limits)

% Create the neuron parameters

Noise       = noise*SRange(2)*maxFR;  %% Rescale the noise level
TypeParms   = [Radius, epsilon];      %% Used in genNeuronVecRep() 

NeuronParms = genNeuronVecRep(N, TypeParms, TRange, SRange, maxFR);

% NeuronParms(:,1:5) = [Rthreshold,Gain,maxFR,tRC,Jbias] for each neuron.
EncVec  = NeuronParms(:,6:end); %% Pulls out the encoding vectors from NeuronParms.
gain    = NeuronParms(:,2);     %% Pulls out the gains from NeuronParms.
bias    = NeuronParms(:,5);     %% Pulls out jbias from NeuronParms.

%Compute Cmatrix = <an(R)am(R)> and moments = <an(R)r(R)>

CntlParms = [Radius,dR];
[Cmatrix Moments] = getDecVecParms(NeuronParms, CntlParms);

% Compute the linear decoding weights
DecVec = getDecVec(N, Cmatrix, Moments, Noise);

ensvect = [
    gain;
    bias;
    EncVec;
    DecVec];

%% FUNCTION TO CREATE GAIN, JBIAS ADN ENCODING VECTORS
function Neurons = genNeuronVecRep(N, TypeParms, TRange, SRange, maxFR0)

Radius       = TypeParms(1);

% Generate intercepts between -Radius and +Radius
EUV          = genuniD(N);
Rthres       = (TRange(2)-TRange(1))*rand(N,1)+TRange(1); 
iOn          = find(EUV>0);
Rthres(iOn)  = sort(Rthres(iOn));
Rthres(iOn)  = flipud(Rthres(iOn));
iOff         = find(EUV<0);
Rthres(iOff) = sort(Rthres(iOff));
Rthres(iOff) = flipud(Rthres(iOff));

Sat          = (SRange(2)-SRange(1))*rand(N,1)+SRange(1);

epsilon      = TypeParms(2)*ones(N,1);
maxFR        = maxFR0*ones(N,1);
% Gain and Jbias must satisfy max(G(J(x)) and G(J(x))=0
Gain         = (1./(1-exp((Sat-maxFR*10^(-3))./(Sat.*epsilon)))-1)./(Radius-Rthres);
Jbias        = 1.0-Gain.*Rthres;
Neurons      = [Rthres, Gain, maxFR, epsilon, Jbias, EUV];

%% FUNCTION TO CREATE THE ENCODING VECTORS
function U = genuniD(N)
% genuniD generates N 1-dimensional vectors in or on the unit hypersphere\
% encoding vectors are either +1 (ON) or -1 (OFF)
Uinv                       = ones(1,N);
Uinv((floor((N+1)/2)+1):N) = -1;
U                          = Uinv';

%% FUNCTION TO COMPUTE Cmatrix AND  MOMENTS (see book page 38)
function [Cmatrix, Moments] = getDecVecParms(NeuronParms, CntlParms)

Radius  = CntlParms(1);
dr      = CntlParms(2);

EUV     = NeuronParms(:,6:end); % Encoding Unit Vectors \tilde \phi_i

r       = -Radius:dr:Radius;
hsVolD  = 2*Radius; % Vol of 1D sphere.
Rvalues = EUV*r;
an      = genActivities(NeuronParms,Rvalues);

Moments = an*r'*(dr/hsVolD);
Cmatrix = an*an'*(dr/hsVolD);

%% FUNCTION TO GENERATE THE ai(x) FUNCTIONS FOR A SET A PREDEFINED VALUES
function a = genActivities(NeuronParms,Rvalues)

[N, M] = size(Rvalues);
% Leaky integrate and fire model

Gain    = NeuronParms(:,2)*ones(1,M);
maxFR   = NeuronParms(:,3)*ones(1,M);
epsilon = NeuronParms(:,4)*ones(1,M);
Jbias   = NeuronParms(:,5)*ones(1,M);
  
% index = find(Rvalues>Rthres);
J        = Gain.*Rvalues+Jbias;
a        = zeros(N, M);
index    = find(J>1);
a(index) = maxFR(index)./(1-epsilon(index).*log(1-1./J(index)));
plot(a')

%% FUNCTION TO COMPUTE THE LINEAR DECODING WEIGHTS (see book page 43)
function  DecVec = getDecVec(N, Cmatrix, Moments, noise)

[U,S,~] = svd(Cmatrix);
Sinv    = 1./(diag(S)+noise^2*ones(N,1));
DecVec  = (U*diag(Sinv)*U')*Moments;