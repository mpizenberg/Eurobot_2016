#ifndef _PID_H_
#define _PID_H_


/*****************************    Structures    *******************************/

// k + Coeffs du PID (proportionnel, integrale, derivee) et coef de moyennage
typedef struct {
    float k;
    float kp;
    float ki;
    float kd;
    float mu_p;
} PidCoefs;

// Etat des valeurs du PID (erreur, integrale de l'erreur, derivee de l'erreur) et borne de l'integrale
typedef struct {
    float err;
    float err_moy; // erreur moyennee
    float err_int;
    float err_int_moy; // integrale moyennee
    float err_der;
    float err_der_moy; // derivee moyennee
    float max_int;
} PidState;

// Valeurs de l'erreur et de sa derivee permettant de considerer que le pid est stable
typedef struct {
    float err_eps;
    float der_eps;
} PidEps;

// Un PID est constitue de coefs, de valeurs d'etat et d'une consigne
typedef struct {
    PidCoefs coefs;
    PidState state;
    PidEps eps;
    float order;
} Pid;



/******************************    Fonctions    *******************************/

// assigner des valeurs aux coefs
void pid_set_coefs(Pid *pid, PidCoefs coefs);
void pid_set_k(Pid *pid, float k);
void pid_set_kp(Pid *pid, float kp);
void pid_set_ki(Pid *pid, float ki);
void pid_set_kd(Pid *pid, float kd);
void pid_set_mu_p(Pid *pid, float mu_p);

// assigner des valeurs a  l'etat du PID
void pid_set_state(Pid *pid, PidState state);
void pid_set_err(Pid *pid, float err);
void pid_set_err_moy(Pid *pid, float err_moy);
void pid_set_err_int(Pid *pid, float err_int);
void pid_set_err_int_moy(Pid *pid, float err_int_moy);
void pid_set_err_der(Pid *pid, float err_der);
void pid_set_err_der_moy(Pid *pid, float err_der_moy);
void pid_set_max_int(Pid *pid, float max_int);

// assigner des valeurs aux erreur et derivee permettant de considerer que le pid est stable
void pid_set_eps(Pid *pid, PidEps eps);
void pid_set_eps_err(Pid *pid, float err);
void pid_set_eps_der(Pid *pid, float der);

// remise a  zero de l'integrale du PID
void pid_reset(Pid *pid);
// assigner une valeur de consigne
void pid_set_order(Pid *pid, float order);

// maj de l'etat du PID
void pid_maj(Pid *pid, float value);
void pid_maj_err(Pid *pid, float value);
void pid_maj_err_int(Pid *pid);
void pid_maj_err_der(Pid *pid, float err_old, float err_moy_old);

// calcule la commande du PID
float pid_process(Pid *pid);

// indique si le pid a termine
int pid_done(Pid *pid);


#endif // _PID_H_
