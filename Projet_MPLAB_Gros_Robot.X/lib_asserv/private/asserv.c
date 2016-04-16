#include "extern_globals_asserv.h"
#include "asserv.h"
#include "odo.h"
#include "pid.h"
#include "../lib_asserv_default.h"
#include "debug.h"
#include "tools.h"
#include <math.h>


/******************************    Variables    *******************************/
volatile int asserv_mode;
volatile PositionAsserv pos_asserv;
volatile SpeedAsserv speed_asserv;
volatile AngleAsserv angle_asserv;



/******************************    Fonctions    *******************************/

// initialiser le mode et les differents asservissement
void asserv_init(){
    asserv_mode = DEFAULT_ASSERV_MODE;

    // PID pour l'asserv en vitesse (delta)
    Pid pid_delta;
    PidCoefs coefs_delta = DEFAULT_PID_COEFS_DELTA;
    PidState state_delta = {0,0,0,0,0,0,DEFAULT_PID_MAX_INT_DELTA};
    PidEps eps_delta = DEFAULT_PID_EPS_DELTA;
    pid_set_coefs(&pid_delta,coefs_delta);
    pid_set_state(&pid_delta, state_delta);
    pid_set_eps(&pid_delta, eps_delta);
    pid_set_order(&pid_delta, 0);

    // PID pour l'asserv en vitesse angulaire (alpha)
    Pid pid_alpha;
    PidCoefs coefs_alpha = DEFAULT_PID_COEFS_ALPHA;
    PidState state_alpha = {0,0,0,0,0,0,DEFAULT_PID_MAX_INT_ALPHA};
    PidEps eps_alpha = DEFAULT_PID_EPS_ALPHA;
    pid_set_coefs(&pid_alpha,coefs_alpha);
    pid_set_state(&pid_alpha, state_alpha);
    pid_set_eps(&pid_alpha, eps_alpha);
    pid_set_order(&pid_alpha, 0);

    // initialisation de l'asservissement en position
    pos_asserv.pos_order = (Position){0,0,0};
    pos_asserv.stop_distance = DEFAULT_STOP_DISTANCE;
    // respect des contraintes d'acceleration max avec ce coef
    pos_asserv.kp = 1.6;
    pos_asserv.state = (MotionState*)(&motionState);
    pos_asserv.constraint = (MotionConstraint*)(&motionConstraint);
    pos_asserv.done = 0;
    pos_asserv.distance = (Distance){0,0};
    // initialisation de l'asservissement en vitesse
    speed_asserv.speed_order = (Speed){0,0};
    speed_asserv.speed_order_constrained = (Speed){0,0};
    speed_asserv.state = (MotionState*)(&motionState);
    speed_asserv.constraint = (MotionConstraint*)(&motionConstraint);
    speed_asserv.pid_delta = pid_delta;
    speed_asserv.pid_alpha = pid_alpha;
    speed_asserv.done = 0;
    // initialisation de l'asservissement en angle
    angle_asserv.angle_order = 0;
    angle_asserv.state = (MotionState*)(&motionState);
    angle_asserv.constraint = (MotionConstraint*)(&motionConstraint);
    angle_asserv.pid_alpha = pid_alpha;
    angle_asserv.done = 0;
}

// choisir le mode d'asservissement (desactive, en position, en vitesse)
void set_asserv_off(){asserv_mode = ASSERV_MODE_OFF;}
void set_asserv_pos_mode(){asserv_mode = ASSERV_MODE_POS;}
void set_asserv_speed_mode(){asserv_mode = ASSERV_MODE_SPEED;}
void set_asserv_angle_mode(){asserv_mode = ASSERV_MODE_ANGLE;}
void set_asserv_seq_mode(){asserv_mode = ASSERV_MODE_SEQUENCE;}

// observer les contraintes aux vitesse et vitesse angulaire
void constrain_speed(float v, float vt, float *v_constrained, float *vt_constrained){
    // contraintes
    float v_max = motionConstraint.v_max.v;
    float vt_max = motionConstraint.v_max.vt;
    float a_max = motionConstraint.a_max.a;
    float at_max = motionConstraint.a_max.at;
    float v_vt_max = motionConstraint.a_max.v_vt;
    float v_c_old = *v_constrained;

    // calcul des contraintes
    float period = DEFAULT_PERIOD;

    // contraintes liees a l'acceleration et vitesse absolues
    *v_constrained = limit_float(v,  v_c_old-a_max*period,  v_c_old+a_max*period);
    *v_constrained = limit_float(*v_constrained,-v_max,v_max);

    // contraintes liees a l'acceleration et vitesse angulaires
    *vt_constrained = limit_float(vt,   *vt_constrained-at_max*period,   *vt_constrained+at_max*period);
    *vt_constrained = limit_float(*vt_constrained,-vt_max,vt_max);

    // contraintes liees a l'acceleration v_vt_max (priorite a la vitesse angulaire)
    if (fabs((*v_constrained)*(*vt_constrained)) > v_vt_max){
        // v_constrained ne peut pas valoir 0 mais peut etre positif ou negatif
        if (*v_constrained>0){
            *v_constrained = limit_float(
                    v_vt_max/fabs(*vt_constrained),
                    v_c_old-a_max*period,
                    v_c_old+a_max*period);
        }
        else {
            *v_constrained = limit_float(
                    -v_vt_max/fabs(*vt_constrained),
                    v_c_old-a_max*period,
                    v_c_old+a_max*period);
        }
    }
}

// contraint la consigne de vitesse avec la fonction precedente constrain_speed
void constrain_speed_order(){

    // vitesse consigne(o comme order) et consigne contrainte(oc)
    float v_o = speed_asserv.speed_order.v;
    float vt_o = speed_asserv.speed_order.vt;
    float v_oc = speed_asserv.speed_order_constrained.v;
    float vt_oc = speed_asserv.speed_order_constrained.vt;

    constrain_speed(v_o, vt_o, &v_oc, &vt_oc);
    speed_asserv.speed_order_constrained.v = v_oc;
    speed_asserv.speed_order_constrained.vt = vt_oc;
}

// effectue un pas d'asservissement
void asserv_step(Odo *odo, float *commande_g, float *commande_d){
    // choix en fonction du mode d'asservissement (off, position ou vitesse)
    switch (asserv_mode){
        // si on est en roue libre
        case ASSERV_MODE_OFF :
            *commande_g = 0;
            *commande_d = 0;
            speed_asserv.speed_order_constrained = motionState.speed;
            break;
        // si on est en asservissement en position
        case ASSERV_MODE_POS :
            pos_asserv_step(odo, commande_g, commande_d);
            if (debug_mode){debug_pos_asserv();}
            break;
        // si on est en asservissement en vitesse
        case ASSERV_MODE_SPEED :
            if (debug_mode){debug_speed_asserv();}
            speed_asserv_step(odo, commande_g, commande_d);
            break;
        // si on est en asservissement en angle
        case ASSERV_MODE_ANGLE :
            //if (debug_mode){debug_speed_asserv();}
            angle_asserv_step(odo, commande_g, commande_d);
            break;
        case ASSERV_MODE_SEQUENCE :
            seq_asserv_step(odo, commande_g, commande_d);
            break;
    }
}

void speed_asserv_step(Odo *odo, float *commande_g, float *commande_d){
    // commandes des PID en vitesse absolue (delta) et angulaire (alpha)
    float commande_delta, commande_alpha;

    // verifier qu'on est pas bloque par un obstacle
    check_blocked(motionState.speed, speed_asserv.speed_order_constrained);

    // on commence par verifier les contraintes de vitesses et acceleration
    constrain_speed_order();

    // maj des consignes des PID
    pid_set_order(&(speed_asserv.pid_delta), speed_asserv.speed_order_constrained.v);
    pid_set_order(&(speed_asserv.pid_alpha), speed_asserv.speed_order_constrained.vt);

    // maj des valeurs des PID
    pid_maj(&(speed_asserv.pid_delta), odo->state->speed.v);
    pid_maj(&(speed_asserv.pid_alpha), odo->state->speed.vt);

    // calcul des sorties des PID
    commande_delta = pid_process(&(speed_asserv.pid_delta));
    commande_alpha = pid_process(&(speed_asserv.pid_alpha));

    // renvoie des commandes gauche et droite
    *commande_g = commande_delta - commande_alpha;
    *commande_d = commande_delta + commande_alpha;

    /*
    // verification si on est arrive a la bonne consigne
    if (pid_done(&(speed_asserv.pid_delta)) && pid_done(&(speed_asserv.pid_alpha))){
        speed_asserv.done = 1;
    } else {speed_asserv.done = 0;}
     */
}


void pos_asserv_step(Odo *odo, float *commande_g, float *commande_d){
    /*
     * On calcule les consignes de vitesse et vitesse angulaire
     * en fonction de la position actuelle et de la consigne de position.
     *
     * Idees :
     * La priorite a la rotation
     *   -> l'acceleration angulaire max doit permettre cette priorite
     * On doit avoir une decroissance des consignes de vitesse plus lente que
     * celles autorisees par la deceleration max
     */

    // recuperation de la consigne (o pour "order") en position
    float x_o = pos_asserv.pos_order.x; // consigne en x
    float y_o = pos_asserv.pos_order.y; // consigne en y

    // recuperation de la position et vitesse courantes
    float x = odo->state->pos.x;
    float y = odo->state->pos.y;
    float v = odo->state->speed.v;
    float vt = odo->state->speed.vt;

    // contraintes
    float a_max = motionConstraint.a_max.a;
    float deceleration_max = a_max;

    // calcul de la distance a la consigne en position
    float d = sqrt((x_o-x)*(x_o-x) + (y_o-y)*(y_o-y));

    // calcul de la deviation angulaire par rapport a la consigne en position
    float dt = principal_angle(atan2f(y_o-y,x_o-x) - odo->state->pos.t);

    // declaration des consignes en vitesse et vitesse angulaire
    float v_o, vt_o;

    // hysteresis pour eviter les allers retours
    float epsi;
    int derriere, sens_rotation;

    // si on est arrive on ne bouge plus
    if (d < pos_asserv.stop_distance) {
        pos_asserv.done = 1;
        *commande_g = 0;
        *commande_d = 0;
    }
    else {
        // On determine dans un premier temps si le robot doit plutot avancer
        // ou reculer pour atteindre la consigne de position. Pour cela, il suffit
        // de regarder la valeur de l'ecart angulaire "dt" a la consigne:
        //     - si |dt| < pi/2 , l'objectif est en face de nous.
        //     - si |dt| > pi/2 , il est derriere.
        // On ajoute en plus un hysteresis pour eviter les allers retours
        // quand l'objectif est quasiment a angle droit sur le cote (|dt| proche de PI/2)

        epsi = 0.1 * PI/2;
        if (v > 0){
            derriere = fabs(dt) > PI/2 + epsi;
        } else {
            derriere = fabs(dt) > PI/2 - epsi;
        }

        if (derriere){
            d = -d;
            dt = principal_angle(dt+PI);
        }

        // On veut determiner des consignes en vitesse et en vitesse angulaire
        // qui permettront de se rapprocher de la consigne de position.
        // Pour pouvoir freiner suffisament vite il faut que la deceleration
        // autorisee par ce calcul de vitesse ne depasse pas la deceleration
        // maximale autorisee
        v_o  = 0.9 * deceleration_max * d;

        // Pour ne pas tourner autour de la position, il faut corriger plus rapidement
        // l'ecart angulaire que l'ecart de distance.
        // Pour un petit deplacement "delta", et une petite variation angulaire "dtheta",
        // on peut ecrire
        //     dtheta = tan(dtheta) = delta / rayon
        // Le rayon de courbure vaut donc
        //     rayon = v/vt
        // Il est donc imperatif d'avoir un rayon de courbure inferieur a la moitie
        // de la distance |d| qui nous separe de la consigne.
        // En choisissant par exemple rayon = |d|/2 , on obtient
        //     |vt| = 2 * |v/d|
        if (dt>0) sens_rotation=1 else sens_rotation=-1;
        vt_o = sens_rotation * 2 * fabs(v_o/d);

        // appel de l'asserve en vitesse avec les bonnes consignes
        speed_asserv.speed_order.v = v_o;
        speed_asserv.speed_order.vt = vt_o;
        speed_asserv_step(odo,commande_g,commande_d);

        // maj de la distance à la consigne
        pos_asserv.distance.d = d;
        pos_asserv.distance.dt = dt;
    }
}

// asservissement en angle
void angle_asserv_step(Odo *odo, float *commande_g, float *commande_d){
    // angle restant a parcourir
    float dt = principal_angle(angle_asserv.angle_order - odo->state->pos.t);
    float vt_o;
    // contraintes
    float at_max = motionConstraint.a_max.at;
    float deceleration_max = at_max;

    // si on est arrive on ne bouge plus
    if (fabs(dt) < 0.02) {
        angle_asserv.done = 1;
        *commande_g = 0;
        *commande_d = 0;
    } else {
        // calcul de la vitesse angulaire necessaire
        vt_o = 0.9 * deceleration_max * dt;
        // appel de l'asserve en vitesse avec les bonnes consignes
        speed_asserv.speed_order.v = 0;
        speed_asserv.speed_order.vt = vt_o;
        speed_asserv_step(odo,commande_g,commande_d);
    }
}

// asservissement en sequence
void seq_asserv_step(Odo *odo, float *commande_g, float *commande_d){
    // si on est arrive on ne bouge plus
    if (!(motionSequence.waiting)) {
        *commande_g = 0;
        *commande_d = 0;
    } else {
        // choix de la position en cours
        pos_asserv.pos_order = motionSequence.pos_seq[motionSequence.in_progress];
        pos_asserv.stop_distance = motionSequence.stop_distance[motionSequence.in_progress];
        pos_asserv_step(odo,commande_g,commande_d);
        // si cette etape est finie, passer a la suivante
        if (pos_asserv.done){
            pos_asserv.done = 0;
            motionSequence.waiting--;
            motionSequence.in_progress = !(motionSequence.in_progress);
        }
    }
}

// indique si l'asservissement en cours a termine
int asserv_done(){
    if (asserv_mode == ASSERV_MODE_OFF) {return 1;}
    else if (asserv_mode == ASSERV_MODE_POS) {return pos_asserv.done;}
    else if (asserv_mode == ASSERV_MODE_SPEED) {return speed_asserv.done;}
    else if (asserv_mode == ASSERV_MODE_ANGLE) {return angle_asserv.done;}
    else if (asserv_mode == ASSERV_MODE_SEQUENCE) {return !(motionSequence.waiting);}
    else {return 0;}
}
