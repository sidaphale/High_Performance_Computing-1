clear all; close all; clc;

%Loading the data files
p4gcc = load('Run1.dat');
p4intel = load('Run2.dat');
p4cblas = load('Run3.dat');
p4mkl = load('Run4.dat');

%Calculating the log values of vector size, consider base 4
p4gcc(:,3) = (log(p4gcc(:,1))/log(4));
p4intel(:,3) = (log(p4intel(:,1))/log(4));
p4cblas(:,3) = (log(p4cblas(:,1))/log(4));
p4mkl(:,3) = (log(p4mkl(:,1))/log(4));

figure(1);
% plot(p4gcc(:,3), p4gcc(:,2), 'o-b', 'LineWidth' ,3)
hold on
plot(p4intel(:,3), p4intel(:,2), 'o-r', 'LineWidth' ,3)
% plot(p4cblas(:,3),p4cblas(:,2), 'o-g', 'LineWidth' ,3)
% plot(p4mkl(:,3),p4mkl(:,2), 'o-k', 'LineWidth' ,3)
title('Performance Plot - L1 BLAS Function', 'FontSize', 22);
xlabel('Vector Size(Bytes)', 'FontSize', 18);
ylabel('MFlops', 'FontSize', 18);
% legend('GCC Compiler', 'CBLAS Library', 'MKL Library', 'Location', 'northwest');
set(gca, 'XTick', [1 2 3 4 5 6 7 8 9 10 11 12 13 14]);
set(gca, 'XTickLabel', {'1', '4', '16', '64', '256', '1K', '4K', '16K', '64K', '256K', '1M', '4M', '16M', '64M'});