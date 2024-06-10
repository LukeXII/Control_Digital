%%
% Ploteo de variables de control con observador
clc
clear all

filename = 'putty.csv';
ts = 0.008;

data = csvread(filename);

res = 3.3/4095;
data = data*res;

plot(data)

risetime(data(:,2), 1/ts)
%rt = mean(risetime(data(:,2), 1/ts))
