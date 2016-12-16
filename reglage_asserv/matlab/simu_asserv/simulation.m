entre_roues = 0.25598;
v_max = 0.9;
vt_max = v_max/entre_roues;
a_max = 2;
at_max = a_max/entre_roues;
ac_max = v_max*vt_max;
t = 0.010;

n = 1000;
v = ones(1,n);

Kp = 110;
Ki = 10;
sim simMoteur
