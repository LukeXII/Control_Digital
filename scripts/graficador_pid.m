%%
% Calculo y ploteo de rise time practico
clc
clear all

filename = 'control.csv';
ts = 0.008;

data = csvread(filename);

res = 3.3/4095;
data = data*res;

%plot(data)

stairs(0:ts:0.352, data(1:45,3), '--.r')
hold on
grid on
plot(0:ts:0.352, data(1:45,2), 'b--x')

risetime(data(1:45,2), 1/ts)
%rt = mean(risetime(data(:,2), 1/ts))