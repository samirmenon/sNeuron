function callFire
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
input=[-0.4:0.01:0.4];
a=input.*0;
for i=1:length(input)
    a(i)=FireRate(input(i));
end
plot(input,a);
end
