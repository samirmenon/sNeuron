function [ v ] = LIF_NeuronSet_Activity
%Function to show spiking in a neuron in Nengo
close all; clear all;
% Actuall parameter values from Nengo
tau= 0.02; 
input = 0.5;

%open the exported files having bias and scale values for 100 neurons
fp1=fopen('bias.txt','r');
fp2=fopen('scale.txt','r');
color = ['r','g','b','m','c'];
for k=1:100,
    %read biases and scales from the files.
    sb=fgetl(fp1);
    ss=fgetl(fp2);
    
    bias = str2double(sb);
    scale = str2double(ss);
    
    %calculating constants a and b
    a = -1*tau;
    b = (scale*input+ bias)*tau;
    vb=0;
    
    
    %V_max is the x intercept = (-b/a)
    vmax=((-1*b)/a);
    vth= vmax- 0.0001;
    v(1)= vb;
    dv(1)=0;
    
    dt = 0.0005;
    t=0:dt:1;
    v = t.*0; V(1) = 0;
    dv = t.*0;
    
    for i=1:length(t)-1
        dv(i)=a*v(i)+b;
        v(i+1)= v(i)+dv(i);
        if(v(i+1)>vth) v(i+1)=vb;
        end;
    end;
    if(k<=25) 
        subplot(1,4,1);
        hold on;
        plot(t,v/max(v)+k,color(mod(k,5)+1));
        xlimits=[0,1];
        ylimits=[0,25];
        xlim(xlimits);
        ylim(ylimits*1.01);
    end;
    
    if(k>25 && k<=50) 
        subplot(1,4,2);
        hold on;
        plot(t,v/max(v)+k,color(mod(k,5)+1));
        xlimits=[0,1];
        ylimits=[26,50];
        xlim(xlimits);
        ylim(ylimits*1.01)
    end;
    if(k>50 && k<=75) 
        subplot(1,4,3);
        hold on;
        plot(t,v/max(v)+k,color(mod(k,5)+1));
        xlimits=[0,1];
        ylimits=[51,75];
        xlim(xlimits);
        ylim(ylimits*1.01)
        title('Activity of each Neuron in Nengo Pool');
    end;
    if(k>75 && k<=100) 
        subplot(1,4,4);
        hold on;
        plot(t,v/max(v)+k,color(mod(k,5)+1));
        xlimits=[0,1];
        ylimits=[76,100];
        xlim(xlimits);
        ylim(ylimits*1.01)
    end;
    
    %plot(xlimits,[k-0.000001,k+0.000001],'k','LineWidth',0.05);

   % plot(t,[k-0.000001,k+0.000001],'k','LineWidth',2); 
    xlabel('Time');
    ylabel('Activity(normalised) per neuron');
end
      

fclose(fp1);
fclose(fp2);
end