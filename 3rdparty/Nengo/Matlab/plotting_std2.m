function plotting_std2
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
x = [100 200 300 400 500];
y1 = [0.3155 0.3915 0.3641 0.3913 0.4090];
e1 = [0.0004 0.0160 0.0028 0.0032 0.0079];
y2 = [0.3648 0.4125 0.4039 0.4229 0.4204];
e2= [0.0487 0.0088 0.0107 0.0271 0.0025];
y3 = [0.5121 0.4195 0.4382 0.4372 0.4087];
e3=[0.0067 0.0183 0.0447 0.0127 0.0412];

subplot(2,1,1);
errorbar(x,y1,e1,'r','Linewidth',1.5);
hold on;
errorbar(x,y2,e2,'b','Linewidth',1.5);
hold on;
errorbar(x,y3,e3,'k','Linewidth',1.5);
hold on;
target=x.*0 + 0.41;
hold on;
plot(x,target,'k:','Linewidth',2.0);
legend('r=1','r=1.5','r=2.0');
xlabel('No. of neurons');
ylabel('Asymptote values');
xlimits=[80,520];
xlim(xlimits);
title('Simulations with 1 pool');

y1 = [1.9940  1.9819 1.9941 1.9745 1.9907];
e1 = [0.0038 0.0044  0.0031 0.0078 0.0051];
y2 = [1.9869  1.9705 1.9875 1.9806 1.9602];
e2 = [0.0043 0.0033 0.0041  0.0052 0.0129];
y3 = [1.8407  1.9309 1.9309 1.9839 1.9808];
e3 = [0.0720 0.0252  0.0252 0.0017 0.0105];
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

