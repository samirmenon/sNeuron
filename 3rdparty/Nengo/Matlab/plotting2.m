function plotting2
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
a = [100 200 300 400 500 600 700 800];
b = [0.3147 0.3629 0.3691 0.3971 0.3947 0.4005 0.3905 0.3975];
c = [0.4519 0.4282 0.3847 0.3745 0.4160 0.4241 0.4153 0.4113];
d = [0.5241 0.4522 0.3582 0.4144 0.3350 0.5014 0.3741 0.4195];
subplot(2,1,1);
plot(a,b,'r');
hold on;
plot(a,c,'b');
hold on;
plot(a,d,'m');
hold on;
target=a.*0 + 0.41;
hold on;
plot(a,target,'k','Linewidth',1.5);
grid on;
legend('r=1','r=1.5','r=2.0');
xlabel('No. of neurons');
ylabel('Asymptote values');
b = [1.9873  1.9897 1.9885 1.9884 1.9999 1.9967 1.9790 1.9939];
c = [1.9946  1.9763 1.9948 1.9900 1.9832 1.9970 1.9698 1.9753];
d = [1.9696  1.8815 1.9759 1.9870 1.9995 1.9732 1.9970 1.9984];
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

