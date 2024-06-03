%%
% Construccion SS a partir de identificacion

%[0 0.164 0.073],[1 -0.856 0.094]
% N = 140, ts = 15 ms
ts_ident = 15;
s_ident_disc = tf([0 0.164 0.073],[1 -0.856 0.094], ts_ident/1000);

%pzmap(s_ident_disc)
%grid on

ts_cont = 8;

sysd_ss = ss(d2d(s_ident_disc, ts_cont/1000))

P = [0.78 0.1];
%P = [0.68 0.7];

K = place(sysd_ss.A, sysd_ss.B, P)

Acl = sysd_ss.A - sysd_ss.B*K;

syscl = ss(Acl, sysd_ss.B, sysd_ss.C, sysd_ss.D, ts_cont/1000);
Pcl = pole(syscl)

step(d2c(syscl, 'foh'))
stepinfo(d2c(syscl, 'foh'))

polos_cont_pp = log(Pcl)/(ts_cont/1000)/(2*pi)