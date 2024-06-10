%% Construccion de espacio de estados
clc
clear all

C = 1e-6;
R1 = 10e3;
R2 = 27e3;

ts_cont = 8;

A = [-1/(R1*C)-1/(R2*C) 1/(R2*C); 1/(R2*C) -1/(R2*C)];
B = [1/(R1*C); 0];
C = [0 1];

sys_ss = ss(A, B, C, 0);
sys_ss_disc = c2d(sys_ss, ts_cont/1000);

pole(sys_ss_disc)

%% Pole placement sin observador

rt = 0.075;

polo_deseado = 0.35/rt;
polo_deseado_disc = exp(-polo_deseado*(2*pi)*ts_cont/1000);

%P = [0.1 0.75];            % polo dominante
P = [0.643 0.642];

K = place(sys_ss_disc.A, sys_ss_disc.B, P)

Acl = sys_ss_disc.A - sys_ss_disc.B*K;

kf = 1/(sys_ss_disc.C*(eye(2)-Acl)^(-1)*sys_ss_disc.B)

syscl = ss(Acl, kf*sys_ss_disc.B, sys_ss_disc.C, sys_ss_disc.D, ts_cont/1000);
Pcl = pole(syscl);

figure(1)
step(d2c(syscl))
stepinfo(d2c(syscl))

figure(2)
step(syscl)
stepinfo(syscl)
grid on
hold on

polos_cont_pp = log(Pcl)/(ts_cont/1000)/(2*pi);         % polos del lazo cerrado (en Hz)

%%

filename = 'putty.csv';
ts = 0.008;

data = csvread(filename);

res = 3.3/4095;
data = data*res;

% figure(2)
% step(d2c(syscl))
% stepinfo(d2c(syscl))
% 
% figure(3)
% stairs(0:ts:0.280, data(:,4), '--.r')
% hold on
% grid on
% plot(0:ts:0.280, data(:,2), 'b--x')
% plot(0:ts:0.280, data(:,3), 'g--x')

risetime(data(:,2), 1/ts)
%rt = mean(risetime(data(:,2), 1/ts))
