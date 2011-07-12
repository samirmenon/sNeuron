function [ w ] = weights

%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
alpha = load('C:\Users\Srish\Desktop\nengo-1132\product_scale.txt');
enc = load('C:\Users\Srish\Desktop\nengo-1132\product_B_encoders.txt');
dec = load('C:\Users\Srish\Desktop\nengo-1132\b_X_decoders.txt');

w(1,1)=0;

for i = 1:length(dec)
    for j= 1:length(enc)
         if enc(j)==-1
             enc(j)=0;
         end
        w(j,i)= alpha(j)*enc(j)*dec(i);
    end
end

w1 = w - min(min(w));
w2 = w1 ./ max(max(w1));
imshow(w2);
xlabel('Neurons in Pool B');
ylabel('Neurons in Pool C');
title('Connection Matrix');
end

