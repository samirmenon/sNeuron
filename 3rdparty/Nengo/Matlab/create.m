function create(a)  
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
t=[0.0 0.0 0.0 0.0 0.0];
d=[0.0 0.0 0.0 0.0 0.0];
load C:\Users\Srish\Documents\2_pool_rate\Trial1\r100200.mat
timeFilter =exp(-1*a*[1:100]);
timeFilter=timeFilter/sum(timeFilter);
a=data;
b=data_time;
data_filtered = filter(timeFilter,1, a);

for i=2:length(data_filtered)
    if(abs((data_filtered(i) - (0.41*0.9)))<= 0.001) %change 0.41 to 0.11 for 1 pool
        t(1) = b(i);
        break;
    end;
end;

d(1)=mean(data_filtered((length(data_filtered)-1000):length(data_filtered)));


load C:\Users\Srish\Documents\2_pool_rate\Trial2\r100200.mat

a=data;
b=data_time;
data_filtered = filter(timeFilter,1, a);

for i=2:length(data_filtered)
    if(abs((data_filtered(i) - (0.41*0.9)))<= 0.001)
        t(2) = b(i);
        break;
    end;
end;

d(2)=mean(data_filtered((length(data_filtered)-1000):length(data_filtered)));


load C:\Users\Srish\Documents\2_pool_rate\Trial3\r100200.mat
a=data;
b=data_time;
data_filtered = filter(timeFilter,1, a);

for i=2:length(data_filtered)
    if(abs((data_filtered(i) - (0.41*0.9)))<= 0.001)
        t(3) = b(i);
        break;
    end;
end;

d(3)=mean(data_filtered((length(data_filtered)-1000):length(data_filtered)));


load C:\Users\Srish\Documents\2_pool_rate\Trial4\r100200.mat
a=data;
b=data_time;
data_filtered = filter(timeFilter,1, a);

for i=2:length(data_filtered)
    if(abs((data_filtered(i) - (0.41*0.9)))<= 0.001)
        t(4) = b(i);
        break;
    end;
end;

d(4)=mean(data_filtered((length(data_filtered)-1000):length(data_filtered)));


load C:\Users\Srish\Documents\2_pool_rate\Trial5\r100200.mat
a=data;
b=data_time;
data_filtered = filter(timeFilter,1, a);

for i=2:length(data_filtered)
    if(abs((data_filtered(i) - (0.41*0.9)))<= 0.001)
        t(5) = b(i);
        break;
    end;
end;
length(data_filtered);
d(5)=mean(data_filtered((length(data_filtered)-1000):length(data_filtered)));
d
t
mean_time = mean(t)
std_time = std(t)
mean_val = mean(d)
std_val = std(d)
end