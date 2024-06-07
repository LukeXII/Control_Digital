%% Construccion de espacio de estados

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

P = [0.78 0.1];
%P = [0.68 0.7];

K = place(sys_ss_disc.A, sys_ss_disc.B, P)

Acl = sys_ss_disc.A - sys_ss_disc.B*K;

syscl = ss(Acl, sys_ss_disc.B, sys_ss_disc.C, sys_ss_disc.D, ts_cont/1000);
Pcl = pole(syscl)

figure(1)
step(syscl)

figure(2)
step(d2c(syscl, 'foh'))
stepinfo(d2c(syscl, 'foh'))

polos_cont_pp = log(Pcl)/(ts_cont/1000)/(2*pi)

kf = -1/(sys_ss_disc.C*inv(Acl)*sys_ss_disc.B)

%% Pole placement con observador

%%

filename = 'putty.csv';
ts = 0.008;

data = csvread(filename);

res = 3.3/4095;
data = data*res;

%plot(data)

risetime(data(:,2), 1/ts)
%rt = mean(risetime(data(:,2), 1/ts))
