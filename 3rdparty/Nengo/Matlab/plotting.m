function plotting
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
a = [100 200 300 400 500 600 700 800];
b = [0.1525 0.0565 0.0458 0.0670 0.1100 0.1232 0.1258 0.1268];
c = [0.1423 0.1943 0.0629 0.0724 0.1386 0.1104 0.1504 0.1173];
d = [0.0493 0.2504 0.1043 0.0836 0.3116 0.1507 0.1402 0.1516];
subplot(2,1,1);
plot(a,b,'r');
hold on;
plot(a,c,'b');
hold on;
plot(a,d,'m');
hold on;
target=a.*0 + 0.11;
hold on;
plot(a,target,'k','Linewidth',1.5);
grid on;
legend('r=1','r=1.5','r=2.0');
xlabel('No. of neurons');
ylabel('Asymptote values');
title('Simulations with 1 pool');
b = [1.9943  1.9757 1.9983 Inf 1.9619 0.1310 1.9842 Inf];
c = [1.9237  1.9905 1.9998 Inf 1.9868 1.9844 1.8763 1.9490];
d = [1.7612  1.9850 1.9701 1.9760 1.8822 Inf 1.9757 0.08];
subplot(2,1,2);
plot(a,b,'r');
hold on;
plot(a,c,'b');
hold on;
plot(a,d,'k');
grid on;
xlabel('No. of neurons');
ylabel('Time taken to reach 90%');
legend('r=1','r=1.5','r=2.0');
end

