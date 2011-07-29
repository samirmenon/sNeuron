
q1 = 0;%sym('q1','real');
q2 = 0;%sym('q2','real');
q3 = 0;%sym('q3','real');

m1 = 0.5; %sym('m1','real');
m2 = 0.1;     %sym('m2','real');
m3 = 0.1;   %sym('m3','real');

l1 = 0.7;%sym('l1','real');
l2 = 0.75;%sym('l2','real');
l3 = 0.75;%sym('l3','real');

Ix1 = 0;%sym('Ix1','real');
Iy1 = 0;%sym('Iy1','real');
Iz1 = 0.020833;%sym('Iz1','real');
Ix2 = 0;%sym('Ix2','real');
Iy2 = 0;%sym('Iy2','real');
Iz2 = 0.004771;%sym('Iz2','real');
Ix3 = 0;%sym('Ix3','real');
Iy3 = 0;%sym('Iy3','real');
Iz3 = 0.004771;%sym('Iz3','real');

%ALL OF THE ABOVE -> INPUTS FOR THE A MATRIX: q1,q2,q3 are angles (from
%ROOM). m1~3 are masses, l1~3 are lengths of joints, Ixyz are moments of
%inertia (remember we don't need Ix, Iy)

JW1 = [ 0 0 0; 0 0 0; 1 0 0];
JW2 = [ 0 0 0; 0 0 0; 1 1 0];
JW3 = [ 0 0 0; 0 0 0; 1 1 1];
%This is the rotational jacobian for the A matrix caculation
% A1 = (mass of 1)*(JV1')*(JV1) + (JW1')*Inertia*(JW1)


In1 = [Ix1 0 0 ;0 Iy1 0; 0 0 Iz1];
In2 = [Ix2 0 0 ;0 Iy2 0; 0 0 Iz2];
In3 = [Ix3 0 0 ;0 Iy3 0; 0 0 Iz3];
%moment of inertia for shoulder, elbow, and wrist

Jv1 = [ (-l1*sin(q1)) 0 0; (l1*cos(q1)) 0 0; 0 0 0];
Jv2 = [ (-l1*sin(q1)-l2*sin(q1+q2)) (-l2*sin(q1+q2)) 0 ; (l1*cos(q1)+l2*cos(q1+q2)) (l2*cos(q1+q2)) 0; 0 0 0];
Jv3 = [(-l1*sin(q1)-l2*sin(q1+q2)-l3*sin(q1+q2+q3)) (-l2*sin(q1+q2)-l3*sin(q1+q2+q3)) (-l3*sin(q1+q2+q3));
     (l1*cos(q1)+l2*cos(q1+q2)+l3*cos(q1+q2+q3))  (l2*cos(q1+q2)+l3*cos(q1+q2+q3))  (l3*cos(q1+q2+q3));
     0 0 0];


%A1 = m1*(Jv1')*(Jv1) + (JW1')*In1*(JW1); this simplifies to the expression
%below
A1 = [m1*l1^2 + Iz1 0 0;0 0 0;0 0 0];
%A2 = m2*(Jv2')*(Jv2) + (JW2')*In2*(JW2)
A2 = [(m2*(l1^2+l2^2+2*l1*l2*cos(q2))+Iz2) (m2*(l2^2+l1*l2*cos(q2))+Iz2) 0;(m2*(l2^2+l1*l2*cos(q2))+Iz2) (m2*l2^2+Iz2) 0;0 0 0];
%A3 is a pain to simplify
A3 = m3*(Jv3')*(Jv3) + (JW3')*In3*(JW3);

A = A1+A2+A3





