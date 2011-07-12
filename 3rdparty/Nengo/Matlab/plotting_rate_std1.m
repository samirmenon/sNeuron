function plotting_rate_std1
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here
x = [100 200 300 400 500];
y1 = [0.5151 0.0392 0.0970 0.0704 0.1401];
y2 = [-0.1053 0.1600 0.0786 0.1817 0.1140];
y3 = [0.1184 0.2367 0.1563 0.0321 0.1373];
y4 = [-0.0208 0.0840 0.0898 0.2084 0.2746];
y5 = [0.1412 0.1473 0.2000 0.2544  0.0741];

e1 = [0.1451 0.2025 0.0103 0.0261 0.0203];
e2 = [0.0885 0.0150 0.0623 0.0187 0.0055];
e3 = [0.0714 0.0493 0.0076 0.1257 0.0104];
e4 = [0.1134 0.0603 0.0432 0.0495 0.0449];
e5 = [0.0279 0.0913 0.0768 0.0397 0.0360];

subplot(2,1,1);
errorbar(x,y1,e1,'r','Linewidth',1.5);
hold on;
errorbar(x,y2,e2,'b','Linewidth',1.5);
hold on;
errorbar(x,y3,e3,'k:','Linewidth',1.5);
hold on;
errorbar(x,y4,e4,'m','Linewidth',1.5);
hold on;
errorbar(x,y5,e5,'g','Linewidth',1.5);
hold on;
target=x.*0 + 0.11;
hold on;
plot(x,target,'k','Linewidth',2);
legend('d=10','d=50','d=100','d=150','d=200');
xlabel('No. of neurons');
ylabel('Asymptote values');
xlimits=[80,520];
xlim(xlimits);
title('Simulations with 1 pool');
y1 = [1.6941 1.9597 1.9873 1.9802 1.9790];
y2 = [1.9105 1.9817 1.9921 1.9210 1.9265];
y3 = [1.9247 1.8807 1.9693 1.9898 1.9814];
y4 = [1.9740 1.9083 1.9273 1.9488 1.9575];
y5 = [1.9767 1.9494 1.9913 1.9913 1.9793];

e1 = [0.0574 0.0030 0.0260 0.0069 0.0014];
e2 = [0.0150 0.0102 0.0004 0.0074 0.0333];
e3 = [0.0985 0.0197 0.0147 0.0064 0.0386];
e4 = [0.0576 0.0324 0.0402 0.0285 0.0101];
e5 = [0.0519 0.0246 0.0097 0.0112 0.0167];

subplot(2,1,2);
errorbar(x,y1,e1,'r','Linewidth',1.5);
hold on;
errorbar(x,y2,e2,'b','Linewidth',1.5);
hold on;
errorbar(x,y3,e3,'k:','Linewidth',1.5);
hold on;
errorbar(x,y4,e4,'m','Linewidth',1.5);
hold on;
errorbar(x,y5,e5,'g','Linewidth',1.5);
hold on;
xlimits=[80,520];
xlim(xlimits);
xlabel('No. of neurons');
ylabel('Time taken to reach 90%');
legend('d=10','d=50','d=100','d=150','d=200');

end

