clear all; close all; clc;
m1 = load('mandelbrot12.dat');
m2 = load('mandelbrot24.dat');
m3 = load('mandelbrot36.dat');
m4 = load('mandelbrot48.dat');
m5 = load('mandelbrot60.dat');
m6 = load('mandelbrot72.dat');
m7 = load('mandelbrot120.dat');
format long;

m = m1;
m(2,:) = m2;
m(3,:) = m3;
m(4,:) = m4;
m(5,:) = m5;
m(6,:) = m6;
m(7,:) = m7;

%Time required to run the serial code
t = 317.86;
%m(:,1) = m(:,1)/12;

for i = 1:7
    m(i,4) = t/m(i,2);
end

%Calculating Karp-Flatt serial metric
for i = 2:7
    m(i,5) = abs(((1/m(i,4))-1/(m(i,1)))/(1-(1/m(i,1))));
end

figure(1);
plot(m(:,1), m(:,4), '-b', 'LineWidth', 2);
title('Speedup Factor vs Number of Processors, strong scaling for Mandelbrot Set');
xlabel('Number of processors');
ylabel('Speedup Factor');
axis square;

figure(2);
plot(m(:,1), m(:,5), '-g', 'LineWidth', 2);
title('Karp-Flatt Serial Fraction plot');
xlabel('Number of processors');
ylabel('Karp-Flatt Serial Fraction');
axis square;