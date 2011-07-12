function [ v ] = LIF_NeuronSet
%Function to show spiking in a neuron in Nengo
close all; clear all;
% Actuall parameter values from Nengo
tau= 0.02; 
input = 0.5;

%open the exported files having bias and scale values for 100 neurons
fp1=fopen('bias.txt','r');
fp2=fopen('scale.txt','r');

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
    
    color = ['r','g','b','k','c'];
    V = [-1:0.01:1];
    dV = a*V+b;
    plot(V,dV,color(mod(k,5)+1)); hold on;
end
ylimits = [-0.5,0.3];
xlimits = [-1.3 1.3];
plot(xlimits,[-0.000001,0.000001],'k','LineWidth',2);
plot([0 0+0.000001],ylimits,'k','LineWidth',2);
xlim(xlimits);
ylim(ylimits*1.01);
xlabel('Normalized Membrane Voltage');
ylabel('dV');
title('Phase portraits V-dV for 100 neurons reprenting one variable x = TODO');

fclose(fp1);
fclose(fp2);
end