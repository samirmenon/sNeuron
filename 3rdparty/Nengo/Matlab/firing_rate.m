function [ v ] = firing_rate(vth)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
bias = 2.0458784103393555;
scale = 4.2928147315979;
tau= 0.02;
input = 0.5;
a = -1/tau
b = scale*input+ bias
vb=0;
%vth= (-1*b)/a;
v(1)= vb;
dv(1)=0;
for i=1:100
    dv(i)=a*v(i)+b;
    v(i+1)=v(i)+dv(i);
    if(v(i+1)>vth) v(i+1)=vb;
    end;
end;
plot(1:101,v);
hold on;
plot(1:100,dv,'r');
%plot(v(1:length(v)-1),dv);
end

