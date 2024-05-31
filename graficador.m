%%
% Calculo rise time practico
clc
clear all

filename = 'output.csv';

data = csvread(filename);

res = 3.3/4095;

data = data*res;

plot(data);

%%
% Planta teorica (tiempo continuo)

C = 1e-6;
R1 = 10e3;
R2 = 27e3;

s = tf([1], [C*C*R1*R2 2*R1*C+C*R2 1])

figure(1)
step(s)
grid on
stepinfo(s);

figure(2)
pzmap(s)
grid on
[polos_teo, ~] = pzmap(s);

%%
% Discretizacion de la planta teorica para comparar con identificacion

ts_ident = 20;          % tiempo de sampleo en identificacion (en ms)
s_disc = c2d(s, ts_ident/1000, 'foh');

figure(3)
pzmap(s_disc)
grid on
[polos_disc_teo, ~] = pzmap(s_disc);

%%
% Analisis valores obtenidos en identificacion

s_ident_disc = tf([0 0.238 0.087],[1 -0.702 0.026], ts_ident/1000);
[polos_disc_ident, ~] = pzmap(s_ident_disc);
polos_disc_teo
polos_disc_ident

%p1 = (2/(ts_ident/1000))*((polos_disc_ident - 1)/(polos_disc_ident +1))
%p2 = (2/(ts_ident/1000))*((polos_disc_teo - 1)/(polos_disc_teo +1))

p1 = log(polos_disc_teo)/(ts_ident/1000)
p2 = log(polos_disc_ident)/(ts_ident/1000)