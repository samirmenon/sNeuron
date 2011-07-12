function plotting_rate
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

a = [100 200 300 400 500];
b = [0.2556 0.4014 0.0786 0.0238 0.1039];
c = [0.0531 0.1869 0.1900 0.2151 0.1042];
d = [-0.0093 0.1486 0.1699 0.1762 0.1558];
e = [-0.2237 0.1919 0.1670 0.1451 0.1985];
f = [0.0913 -0.0161 0.0676 0.2116 0.0424];
subplot(2,1,1);
plot(a,b,'r');
hold on;
plot(a,c,'b');
hold on;
plot(a,d,'m');
hold on;
plot(a,e,'g');
hold on;
plot(a,f,'c');
target=a.*0 + 0.11;
hold on;
plot(a,target,'k','Linewidth',1.5);
grid on;
legend('d=10','d=50','d=100','d=150','d=200');
xlabel('No. of neurons');
ylabel('Asymptote values');
title('Simulations with 1 pool');
b = [1.5915 1.9650 1.9401 1.9926 1.9815];
c = [1.8837 1.9635 1.9912 1.9078 1.9861];
d = [1.7485 1.8454 1.9430 1.9986 1.9124];
e = [1.8710 1.9662 1.9993 1.9909 1.9566];
f = [1.8838 1.9055 1.9865 1.9736 1.9952];
subplot(2,1,2);
plot(a,b,'r');
hold on;
plot(a,c,'b');
hold on;
plot(a,d,'m');
hold on;
plot(a,e,'g');
hold on;
plot(a,f,'c');
grid on;
xlabel('No. of neurons');
ylabel('Time taken to reach 90%');
legend('d=10','d=50','d=100','d=150','d=200');
end

