clear all; close all; clc;
p1 = load('write_pi12.dat');
p2 = load('write_pi24.dat');
p3 = load('write_pi48.dat');
p4 = load('write_pi96.dat');
p5 = load('write_pi120.dat');
t = 91.05649;

p = p1;
p(2,:) = p2;
p(3,:) = p3;
p(4,:) = p4;
p(5,:) = p5;

for i=1:5
    p(i,3) = t/p(i,2);
end

%Calculating the Karp-Flatt Metric
for i = 1:5
    p(i,4) = abs(((1/p(i,3))-(1/p(i,1)))/(1-(1/p(i,1))));
end

plot(p(:,1), p(:,3), '-b', 'LineWidth', 2);
title('Strong scaling plot for MPI implementation of estimating pi value');
xlabel('Number of processors');
ylabel('Speedup factor');
axis square;

figure(2);
plot(p(:,1), p(:,4), '-g', 'LineWidth', 2);
title('Karp-Flatt Serial Fraction plot');
xlabel('Number of processors');
ylabel('Karp-Flatt Serial Metric');
axis square;