function [ output_args ] = controller( A )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
x(1)=4.0;
dt=0.0:0.001:1.0;
for i=2:length(dt)
    x(i)=x(i-1)+ (A*sin(x(i-1)));
end
plot(dt,x);
grid on;
xlabel('time')
ylabel('x-values')
title('controller simulation');
end

