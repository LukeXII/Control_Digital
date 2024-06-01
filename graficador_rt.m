%%
% Calculo y ploteo de rise time practico
clc
clear all

filename = 'step_response.csv';
ts = 0.008;

data = csvread(filename);

res = 3.3/4095;
data = data*res;

%plot(data)

risetime(data(:,2), 1/ts)
%rt = mean(risetime(data(:,2), 1/ts))
