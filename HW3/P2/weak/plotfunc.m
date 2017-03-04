clear all; close all; clc;
p1 = load('write_pi12.dat');
p2 = load('write_pi24.dat');
p3 = load('write_pi36.dat');
p4 = load('write_pi48.dat');
p5 = load('write_pi60.dat');
p6 = load('write_pi72.dat');
p7 = load('write_pi84.dat');
p8 = load('write_pi96.dat');
p9 = load('write_pi108.dat');
t = 91.05649;

p = p1;
p(2,:) = p2;
p(3,:) = p3;
p(4,:) = p4;
p(5,:) = p5;
p(6,:) = p6;
p(7,:) = p7;
p(8,:) = p8;
p(9,:) = p9;

figure(1);
plot(p(:,1), p(:,2), '-b', 'LineWidth', 2);
title('Study of weak scaling - Time in seconds vs Number of Processors');
xlabel('Number of Processors');
ylabel('Time in seconds');
axis square;