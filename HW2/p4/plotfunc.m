% Plot function to plot Mandelbrot set strong scaling
clear all; close all; clc;
%Time required by serial code to execute Mandelbrot Set code for 500x500 grid
t = 12.2786;

%Time required by Parallel code various scheduling

stat = load('static.dat');
dynamic = load('dynamic.dat');
guided = load('guided.dat');

%Numbering the threads in above three data sets
stat(:,1) = stat(:,1)+1;
dynamic(:,1) = dynamic(:,1)+1;
guided(:,1) = guided(:,1)+1;

%Finding out the Speedup Factor
%Speedup Factor = (Time required by 1 processor/Time required by n number
%of threads)

for i = 1:12
    stat(i,3) = t/stat(i,2);
    dynamic(i,3) = t/dynamic(i,2);
    guided(i,3) = t/guided(i,2);
end

%Finding out the Karp-Flatt Serial Metric Fraction
for i=2:12
stat(i,4)=((1/stat(i,3))-(1/stat(i,1)))/(1-1/stat(i,1));
dynamic(i,4)=((1/dynamic(i,3))-(1/dynamic(i,1)))/(1-1/dynamic(i,1));
guided(i,4)=((1/guided(i,3))-(1/guided(i,1)))/(1-1/guided(i,1));
end

%Plotting the Speedup Factor vs Number of Threads
figure(1);
plot(stat(:,1), stat(:,3), '-b', 'LineWidth', 2);
hold on;
plot(dynamic(:,1), dynamic(:,3), '-g','LineWidth', 2);
plot(guided(:,1), guided(:,3), '-r', 'LineWidth', 2);
title('Speedup Factor vs Number of Threads for Strong Scaling');
xlabel('Number of Threads');
ylabel('Speedup Factor');
legend('Static Scheduling', 'Dynamic Scheduling', 'Guided Scheduling', 'Location', 'northwest');
axis square;

%Plotting the Karp-Flatt Serial Fraction Metric
figure(2);
plot(stat(:,1), stat(:,4), '-b', 'LineWidth', 2);
hold on;
plot(dynamic(:,1), dynamic(:,4), '-g', 'LineWidth', 2);
plot(guided(:,1),guided(:,4), '-r', 'LineWidth',2);
title('Karp-Flatt Serial Fraction Metric');
xlabel('Number of threads');
ylabel('Serial Fraction');
legend('Static Scheduling', 'Dynamic Scheduling', 'Guided Scheduling', 'Location', 'northwest');
axis square;