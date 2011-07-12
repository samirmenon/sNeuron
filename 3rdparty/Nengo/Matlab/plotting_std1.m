function plotting_std1
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
x = [100 200 300 400 500];
y1 = [0.0456 0.0844 0.1120 0.1333 0.1272];
e1 = [0.0597 0.0158 0.0360 0.0371 0.0096];
y2 = [0.0848 0.0920 0.1014 0.1525 0.1260];
e2= [0.0321 0.0572 0.0216 0.0671 0.0070];
y3 = [0.0909 0.1304 0.1250 0.2078 0.0883];
e3=[0.0784 0.0671 0.0115 0.0694 0.1248];

subplot(2,1,1);
errorbar(x,y1,e1,'r','Linewidth',1.5);
hold on;
errorbar(x,y2,e2,'b','Linewidth',1.5);
hold on;
errorbar(x,y3,e3,'k','Linewidth',1.5);
hold on;
target=x.*0 + 0.11;
hold on;
plot(x,target,'k:','Linewidth',2.0);
legend('r=1','r=1.5','r=2.0');
xlabel('No. of neurons');
ylabel('Asymptote values');
xlimits=[80,520];
xlim(xlimits);
title('Simulations with 1 pool');

y1 = [1.9190  1.9827 1.9751 1.5925 1.9910];
e1 = [0.0421 0.0064 0.0130 0.8905 0.0163];
y2 = [1.9727  1.9811 1.9909 1.5830 1.9890];
e2 = [0.0274 0.0053 0.0050 0.8849 0.0012];
y3 = [1.8831  1.9772 1.8832 1.9597 1.9524];
e3 = [0.0682 0.0043 0.0486 0.0080 0.0393];
subplot(2,1,2);
errorbar(x,y1,e1,'r','Linewidth',1.5);
hold on;
errorbar(x,y2,e2,'b','Linewidth',1.5);
hold on;
errorbar(x,y3,e3,'k','Linewidth',1.5);
xlabel('No. of neurons');
ylabel('Time taken to reach 90%');
xlimits=[80,520];
xlim(xlimits);
legend('r=1','r=1.5','r=2.0');

end

