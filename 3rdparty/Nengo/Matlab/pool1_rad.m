function [ mean_time std_time mean_val std_val ] = pool1_rad( val )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
str = strcat('C:\Users\Srish\Desktop\NewestSimulations\1pool_Radius\Value',num2str(val),'\');
timeFilter =exp(-1*0.001*[1:100]);
timeFilter=timeFilter/sum(timeFilter);
diff=[1 2 10 17];
x=[100 200 300 400];
color = ['r' 'b' 'g' 'k'];
for d=1:length(diff)
    mean_time=[];
    std_time=[];
    mean_val=[];
    std_val=[];

    for n=100:100:400
        aval=[];
        time=[]
        for trial = 1:5
            file= strcat(str,'Trial',num2str(trial),'\r',num2str(diff(d)),num2str(n));
            load(file);
            a=data;
            b=data_time;
            data_filtered = filter(timeFilter,1, a);

            for i=2:length(data_filtered)
                if(abs((data_filtered(i) - (val*0.9)))<= 0.001) %change 0.41 to 0.11 for 1 pool
                    time = [time b(i)];
                    break;
                end;
            end;
            
            aval=[aval mean(data_filtered((length(data_filtered)-1000):length(data_filtered)))];
        end;
        mean_val=[mean_val mean(aval)];
        std_val=[std_val std(aval)];
        mean_time=[mean_time mean(time)];
        std_time=[std_time std(time)];  

    end;
subplot(2,1,1);
errorbar(x,mean_val,std_val,color(d),'Linewidth',1.5);
hold on;

subplot(2,1,2);
errorbar(x,mean_time,std_time,color(d),'Linewidth',1.5);
hold on;
end;
subplot(2,1,1);
target=x.*0 + val;
hold on;
h=plot(x,target,'k-.','Linewidth',2);
legend('rad=1','rad=2','rad=10','rad=17');
xlabel('No. of neurons');
ylabel('Asymptote values');
xlimits=[90,410];
xlim(xlimits);
title('Simulations with 1 pool');
subplot(2,1,2);

xlimits=[90,410];
xlim(xlimits);
xlabel('No. of neurons');
ylabel('Time taken to reach 90%');
legend('rad=1','rad=2','rad=10','rad=17');
ss1 = strcat('Plots_Newest/Radius1_Value_',num2str(val),'.tif');
ss2 = strcat('Plots_Newest/Radius1_Value_',num2str(val),'.eps');
saveas(h,ss1);
saveas(h,ss2);
close;
end