function plotting_rate_std1
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here
x = [100 200 300 400 500];
y1 = [0.4493 0.4234 0.4450 0.4553 0.4624];
y2 = [0.3586 0.6533 0.4006 0.5030 0.4390];
y3 = [0.3981 0.4309 0.4423 0.4450 0.4276];
y4 = [0.4602 0.4064 0.4716 0.4600 0.4111];
y5 = [0.4609 0.6107 0.4601 0.4206 0.3954];
e1 = [0.0537 0.0616 0.0309 0.0262 0.0510];
e2 = [0.0189 0.1780 0.0244 0.0697 0.0237];
e3 = [0.0341 0.0406 0.0205 0.0242 0.0564];
e4 = [0.0989 0.0440 0.0600 0.0437 0.0267];
e5 = [0.0893 0.1300 0.0667 0.0339 0.0077];

subplot(2,1,1);
errorbar(x,y1,e1,'r','Linewidth',1.5);
hold on;
errorbar(x,y2,e2,'b','Linewidth',1.5);
hold on;
errorbar(x,y3,e3,'k:','Linewidth',1.5);
hold on;
errorbar(x,y4,e4,'b-o','Linewidth',1.5);
hold on;
errorbar(x,y5,e5,'g','Linewidth',1.5);
hold on;
target=x.*0 + 0.41;
hold on;
plot(x,target,'k','Linewidth',2);
legend('d=10','d=50','d=100','d=150','d=200');
xlabel('No. of neurons');
ylabel('Asymptote values');
xlimits=[80,520];
xlim(xlimits);
title('Simulations with 2 pools');
y1 = [1.7086 1.9881 1.9571 1.9536 1.9918];
y2 = [1.9257 1.6011 1.9840 1.9830 1.9688];
y3 = [1.8910 1.9600 1.9975 1.9971 1.9922];
y4 = [1.9953 1.9865 1.9867 1.9550 1.9832];
y5 = [1.9971 1.9832 1.9866 1.9828 1.9694];

e1 = [0.1528 0.0145 0.0194 0.0220 0.0051];
e2 = [0.0491 0.2215 0.0036 0.0056 0.0192];
e3 = [0.0593 0.0060 0.00008 0.0036 0.0680];
e4 = [0.0007 0.0029 0.0111 0.0244 0.0069];
e5 = [0.0030 0.0090 0.0078 0.0077 0.0155];

subplot(2,1,2);
errorbar(x,y1,e1,'r','Linewidth',1.5);
hold on;
errorbar(x,y2,e2,'b','Linewidth',1.5);
hold on;
errorbar(x,y3,e3,'k:','Linewidth',1.5);
hold on;
errorbar(x,y4,e4,'b-o','Linewidth',1.5);
hold on;
errorbar(x,y5,e5,'g','Linewidth',1.5);
hold on;
xlimits=[80,520];
xlim(xlimits);
xlabel('No. of neurons');
ylabel('Time taken to reach 90%');
legend('d=10','d=50','d=100','d=150','d=200');

end

