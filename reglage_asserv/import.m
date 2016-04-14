
x10 = import_data('x_10.csv');
x20 = import_data('x_20.csv');
x30 = import_data('x_30.csv');
x40 = import_data('x_40.csv');
x50 = import_data('x_50.csv');
x60 = import_data('x_60.csv');
x70 = import_data('x_70.csv');
x80 = import_data('x_80.csv');
x90 = import_data('x_90.csv');
x100 = import_data('x_100.csv');

y10 = import_data('y_10.csv');
y20 = import_data('y_20.csv');
y30 = import_data('y_30.csv');
y40 = import_data('y_40.csv');
y50 = import_data('y_50.csv');
y60 = import_data('y_60.csv');
y70 = import_data('y_70.csv');
y80 = import_data('y_80.csv');
y90 = import_data('y_90.csv');
y100 = import_data('y_100.csv');

d_t = 0.005;

v10 = vitesse(x10,y10,d_t);
v20 = vitesse(x20,y20,d_t);
v30 = vitesse(x30,y30,d_t);
v40 = vitesse(x40,y40,d_t);
v50 = vitesse(x50,y50,d_t);
v60 = vitesse(x60,y60,d_t);
v70 = vitesse(x70,y70,d_t);
v80 = vitesse(x80,y80,d_t);
v90 = vitesse(x90,y90,d_t);
v100 = vitesse(x100,y100,d_t);

a10 = acceleration(v10,d_t);
a20 = acceleration(v20,d_t);
a30 = acceleration(v30,d_t);
a40 = acceleration(v40,d_t);
a50 = acceleration(v50,d_t);
a60 = acceleration(v60,d_t);
a70 = acceleration(v70,d_t);
a80 = acceleration(v80,d_t);
a90 = acceleration(v90,d_t);
a100 = acceleration(v100,d_t);