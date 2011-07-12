function plotting_rate2
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

a = [100 200 300 400 500];
b = [0.3633 0.3529 0.3911 0.4098 0.3792];
c = [0.3666 0.3348 0.3570 0.3783 0.4070];
d = [0.3371 0.3582 0.4056 0.4017 0.3785];
e = [0.2832 0.3277 0.3645 0.3818 0.3634];
f = [0.3011 0.3781 0.3661 0.3600 0.3816];
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
target=a.*0 + 0.41;
hold on;
plot(a,target,'k','Linewidth',1.5);
grid on;
legend('d=10','d=50','d=100','d=150','d=200');
xlabel('No. of neurons');
ylabel('Asymptote values');
title('Simulations with 2 pools');
b = [1.9752 1.9970 1.9918 1.9911 1.9983];
c = [1.9959 1.9973 1.9905 1.9931 1.9966];
d = [1.9970 1.9708 1.9973 1.9907 1.9811];
e = [1.9939 1.9916 1.9934 1.9986 1.9955];
f = [1.9917 1.9993 1.9994 1.9966 1.9971];
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

