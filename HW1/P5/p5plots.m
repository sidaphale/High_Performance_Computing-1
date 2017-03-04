clear all; close all; clc;

%Loading the data files
p5gcc = load('Run1.dat');
p5intel = load('Run2.dat');
p5mkl = load('Run3.dat');

p5gcc(:,1) = 2*p5gcc(:,1);
p5intel(:,1) = 2*p5intel(:,1);
p5mkl(:,1) = 2*p5mkl(:,1);

p5gcc(:,3) = log(p5gcc(:,1))/log(4);
p5intel(:,3) = log(p5intel(:,1))/log(4);
p5mkl(:,3) = log(p5mkl(:,1))/log(4);

figure(1);
plot(p5gcc(:,3), p5gcc(:,2), 'o-b', 'LineWidth', 3);
hold on;
plot(p5intel(:,3), p5intel(:,2), 'o-g', 'LineWidth', 3)
plot(p5mkl(:,3), p5mkl(:,2), 'o-r', 'LineWidth', 3);
title('Performance Plot for L3 BLAS Function', 'FontSize', 22);
xlabel('Vector Size(Bytes)', 'FontSize', 18);
ylabel('MFlops', 'FontSize', 18);
legend('GCC Compiler', 'Intel Compiler', 'MKL Library', 'Location', 'northwest')
set(gca, 'XTick', [1 2 3 4 5 6 7 8 9 10 11 12, 13]);
set(gca, 'XTickLabel', {'1', '4', '16', '64', '256', '1K', '4K', '16K', '64K', '256K', '1M', '2M'});