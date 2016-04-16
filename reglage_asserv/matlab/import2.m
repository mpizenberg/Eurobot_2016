
x1 = import_data('pwm_100_2016-04-14/x1.csv');
x2 = import_data('pwm_100_2016-04-14/x2.csv');
x3 = import_data('pwm_100_2016-04-14/x3.csv');
x4 = import_data('pwm_100_2016-04-14/x4.csv');
x5 = import_data('pwm_100_2016-04-14/x5.csv');

y1 = import_data('pwm_100_2016-04-14/y1.csv');
y2 = import_data('pwm_100_2016-04-14/y2.csv');
y3 = import_data('pwm_100_2016-04-14/y3.csv');
y4 = import_data('pwm_100_2016-04-14/y4.csv');
y5 = import_data('pwm_100_2016-04-14/y5.csv');

d_t = 0.005;

v1 = vitesse(x1,y1,d_t);
v2 = vitesse(x2,y2,d_t);
v3 = vitesse(x3,y3,d_t);
v4 = vitesse(x4,y4,d_t);
v5 = vitesse(x5,y5,d_t);

a1 = acceleration(v1,d_t);
a2 = acceleration(v2,d_t);
a3 = acceleration(v3,d_t);
a4 = acceleration(v4,d_t);
a5 = acceleration(v5,d_t);
