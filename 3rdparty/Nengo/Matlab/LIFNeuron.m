function [ v ] = LIFNeuron
%Function to show spiking in a single neuron in Nengo

% Actuall parameter values from Nengo
bias = 2.0458784103393555;
scale = 4.2928147315979;
tau= 0.02;      

%functional input to the pool
input = 0.5;

%calculating a and b for equation  dv =a*v+b
    a = -1*tau;
    b = (scale*input+ bias)*tau;
    vb=0;
    
    
    %V_max is the x intercept = (-b/a)
    vmax=((-1*b)/a);
    vth= vmax- 0.0001;
    v(1)= vb;
    dv(1)=0;
    
    dt = 0.0001;
    t=0:dt:1;
    v = t.*0; V(1) = 0;
    dv = t.*0;
    count=0;
    for i=1:length(t)-1
        dv(i)=a*v(i)+b;
        v(i+1)= v(i)+dv(i);
        if(v(i+1)>vth) 
            v(i+1)=vb;
            count=count+1;
        end;
    end;
    plot(t,v/max(v));
    xlimits=[0,1];
    ylimits=[0,1];
    xlim(xlimits);
    ylim(ylimits*1.05);
    xlabel('Time');
    ylabel('Normalised membrane voltage');
    
end