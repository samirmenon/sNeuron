
function out = Kalmantotal(seed, neural, x0, DFm, Sm)
% Setup a Kalman-filter decoder.

%% INITIALIZE PARAMETERS
% There are the same for all the simulation and should be set only once
binsize          = 0.050; %bin for the neural recording
dt               = 0.001; %simulation time constant

persistent N
persistent Gain          
persistent Jbias     
persistent DECVECS              
persistent ENCVECS             

if isempty(N) || isempty(Gain) || isempty(Jbias) || isempty(DECVECS) || isempty(ENCVECS)
    load 'save1000.mat';
    N = 1000;
    Gain = zeros(N, 2);
    Jbias = zeros(N, 2);
    DECVECS = zeros(2, N);
    ENCVECS = zeros(2, N);
    assert(N == ws1.signals.values);
    Gain = ws2.signals.values;
    Jbias = ws3.signals.values;
    DECVECS = ws4.signals.values;
    ENCVECS = ws5.signals.values;
end
      
persistent tauPSC           
persistent TimeConstant              
persistent tref             
persistent trc              
persistent epsSoma

if isempty(binsize) || isempty(tauPSC)||isempty(TimeConstant) || isempty(dt) || isempty(tref)||isempty(trc) ||isempty(epsSoma)
    
    tauPSC           = 0.02;  % post-synaptic current time constant
    TimeConstant     = 0.005; % filter time constant
    tref             = 0.001; % refractory period of neurons
    trc              = 0.02;  % RC time constant of neurons
    epsSoma          = dt/trc;
end
    
% Encoding and Decoding vectors.
persistent Out_Start
persistent NumEns

if isempty(Out_Start) || isempty(NumEns) 
    NumEns   = 2;
    Out_Start   = 1:NumEns;
end

%% SET UP CONNECTION MATRICES

persistent Mxd
persistent Myd

% Make the matrices neurally plausible
if isempty(Mxd) || isempty(Myd)
    Matrix_X = zeros(3,3);
    Matrix_X(1:2, 1:2) = DFm(4:5, 4:5);
    Matrix_X(1:2, 3) = DFm(4:5, 7);
    Matrix_X(3, 3) = DFm(7, 7);
    
    Matrix_Y = zeros(3,96);
    Matrix_Y(1:2,:) = Sm(4:5,:);
    Matrix_Y(3,:) = Sm(7,:);

    % Go from discret time to continuous time
    Mxc = (Matrix_X-eye(size(Matrix_X)))/binsize;
    Myc = Matrix_Y/binsize;
    % Go from continuous time to discrete synapse
    Mxd = tauPSC*Mxc+eye(size(Matrix_X));
    Myd = tauPSC*Myc;
end

% Setup coupling matrices in local variables
persistent WMatrixFB
persistent WMatrixFF
persistent SynA

if isempty(WMatrixFB) || isempty(WMatrixFF) ||isempty(SynA)
    M         = Mxd(1:2,1:2);
    WMatrixFB   = zeros(NumEns*N,NumEns*N);
    SynA      = dt/tauPSC;
    WMatrixFF   = Gain.*ENCVECS';
    
    for m=1:NumEns
        for n=1:NumEns
            WMatrixFB(1+(m-1)*N:m*N,1+(n-1)*N:n*N) = Gain(:, m).* ENCVECS(m,:)'* M(m,n)*DECVECS(n,:);
        end
    end
end

persistent xk;
if seed == 1 || isempty(xk)
    % initialize
    xk = x0(4:5,1);
    
    % handle initial condition
    out = xk;
else
    

%% RUN SIMULATION
% Perform simulation at each time step
for ii = 1:binsize/dt
    xk = runsimulation(N, tref, TimeConstant, dt, Mxd, Myd, NumEns, Jbias, epsSoma, DECVECS, WMatrixFF, WMatrixFB, SynA, Out_Start, neural);
    out = xk;
end

end
%% RUN THE SIMULATION
function runDatanetwork = runsimulation(N, tref, TimeConstant, dt, Mxd, Myd, NumEns, Jbias, epsSoma, DECVECS, WMatrixFF, WMatrixFB, synA, Out_Start, Neuralspikes)

% Set the inputs signals
ext_INPUTS = Myd(1:2,:) * Neuralspikes + Mxd(1:2, 3);

% Initialize storage for past input values
persistent pastInput; 

if isempty(pastInput)
    pastInput = zeros(size(ext_INPUTS));    
end

% Set up the storage and initialize arrays

% Storage for ensemble variables
persistent Vsoma;
persistent InRef;

if isempty(Vsoma) || isempty(InRef)
    Vsoma   = zeros(N, NumEns);
    InRef   = zeros(N, NumEns);
    
    for m=1:NumEns
        Vsoma(:, m) = rand(N,1);
        InRef(:, m) = zeros(N,1);
    end
end

% Initialize storage for output data
persistent sys_OUTPUTS;

if isempty(sys_OUTPUTS)
    sys_OUTPUTS = zeros(1,NumEns);
end

% Initialize storage for state vectors data
persistent currentValue; %% Holds all the system state vectors.
persistent newValues;   %% Holds all the temporary system state vectors.
persistent filterTmp;   %% Intermediate storage for the filters.

if isempty(currentValue) || isempty(newValues) || isempty(filterTmp)
    currentValue = zeros(N, NumEns);    
    newValues    = zeros(NumEns * N, NumEns);
    filterTmp    = zeros(NumEns * N, NumEns);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% RUN THE SIMULATION %%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Update and filter the inputs to the neurons
for m=1:NumEns
    for n=1:NumEns
        newValues(1+(m-1)*N:m*N, n) = WMatrixFB(1+(m-1)*N:m*N, 1+(n-1)*N:n*N) * currentValue(:, n);
        filterTmp(1+(m-1)*N:m*N, n) = synA * newValues(1+(m-1)*N:m*N, n) + (1-synA)*filterTmp(1+(m-1)*N:m*N, n);
    end
end

neuronValue = sum(filterTmp(:,:),2);


% Pass the state vector through the neuronal nonlinearity and compute the
% estimated state vector values
for m=1:NumEns

    J        = Jbias(:, m) + neuronValue(1+(m-1)*N:m*N) + WMatrixFF(1:N,m).*(synA * ext_INPUTS(m)+(1-synA)* pastInput(m));
    V        = Vsoma(:, m);
    inref    = InRef(:, m);
    
    dV       = epsSoma*(J-V);                  % standard LIF neuron
    V        = V+dV;
    
    output   = zeros(N,1);
    for ii = 1: length(V)
        if V(ii)>1
            deltaT     = dt*(V(ii)-1)./dV(ii); % Interpolated spike time
            output(ii) = 1/dt;
            inref(ii)  = tref+dt-deltaT;       % We subtract dt in the next loop
        end
    end
    
    for ii = 1: length(inref)
        if inref(ii)>0
            V(ii)     = 0.0;                   % Reset the soma to 0 for neurons in refractory period.
            inref(ii) = inref(ii) - dt;        % Countdown
            if inref(ii)<=0
                V(ii) = epsSoma*J(ii).*(-inref(ii)/dt);
            end
        end
    end

    V                           = (V>0).*V;  
    Vsoma(:, m)                 = V;                      % Save tmp values in cells
    InRef(:, m)                 = inref;
    currentValue(:, m)          = output;
    pastInput                   = ext_INPUTS;
    
    sys_OUTPUTS(1,Out_Start(m)) = (DECVECS(m,1:N)*output)'; % Save the present (unfiltered) values of state vectors
end

% Save precedent signal for filtering
persistent pastsignal;

if isempty(pastsignal)
    pastsignal = zeros(1,2);
end

% Data to output
runDatanetwork = zeros(1,2);

% Filter the output
for n=1:NumEns
    runDatanetwork(1,n) = FilterSignal(pastsignal(1,n), sys_OUTPUTS(1,n), dt, TimeConstant);
end

% Save precedent signal for filtering
pastsignal = runDatanetwork;

% Function to perform the filtering
function FilSignal = FilterSignal(pastSignal, newSignal, dt, TimeConstant)
    if TimeConstant == 0
        FilSignal = newSignal(:, end);
    else
        if(TimeConstant<dt)
            eps = 1;
        else
            eps = dt/TimeConstant;
        end
        FilSignal = (1-eps)*pastSignal+eps*newSignal;
    end
