function [ a ] = spike_rate
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
bias = 2.0458784103393555;
scale = 4.2928147315979;
tau= 0.02;  
taur=0.002;
input=[-1.1:0.1:1.1];
J = scale.*input;
J=J+bias;

a = input.*0;


    a=1./(0.002-0.02*log(1 - (3.0./J)));
figure(1);hold on;
plot(input,J,'k');
plot(input,a,'b');

end

