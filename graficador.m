filename = 'output.csv';

data = csvread(filename);

res = 3.3/4095;

data = data*res;

plot(data);

%%

C = 1e-6;
R1 = 10e3;
R2 = 27e3;

s = tf([1], [C*C*R1*R2 2*R1*C+C*R2 1])
step(s)
zpk(s)
stepinfo(s)