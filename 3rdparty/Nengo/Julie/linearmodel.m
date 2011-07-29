function out  = linearmodel(seed, neural, x0, DFm, Sm)

persistent xk;


if seed == 1 || isempty(xk)
    % initialize
    xk = x0;
    
    % handle initial condition
    out = xk;
else
    xk = DFm*xk + Sm*neural;
    
    out = xk;
end
