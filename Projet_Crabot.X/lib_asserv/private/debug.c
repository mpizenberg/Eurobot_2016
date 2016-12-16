#include "extern_globals_asserv.h"
#include "../lib_asserv_default.h"
#include "debug.h"
#include "motion.h"
#include "asserv.h"

/******************************    Variables    *******************************/

volatile int debug_mode;
volatile int debug_count;
volatile SpeedDebug speedDebug;
//volatile PosDebug posDebug;
//volatile PosXYDebug posXYDebug;

/******************************    Fonctions    *******************************/

void set_debug_mode(int mode) {
    debug_mode = mode;
}

void init_debug_table(volatile float *table) {
    int i;
    for (i = 0; i < DEBUG_COUNT_MAX; i++) {
        table[i] = 0;
    }
}

void debug_init() {
    debug_mode = DEFAULT_DEBUG_MODE;
    debug_count = 0;
    init_debug_table(speedDebug.v);
    init_debug_table(speedDebug.vt);
    //    init_debug_table(speedDebug.cons_v);
    //    init_debug_table(speedDebug.cons_vt);
    //    init_debug_table(speedDebug.pid_v);
    //    init_debug_table(speedDebug.pid_vt);
}

void debug_speed_asserv() {
    if (debug_count < DEBUG_COUNT_MAX) {
        (speedDebug.v)[debug_count] = motionState.speed.v;
        (speedDebug.vt)[debug_count] = motionState.speed.vt;
        //        (speedDebug.cons_v)[debug_count] = speed_asserv.speed_order_constrained.v;
        //        (speedDebug.cons_vt)[debug_count] = speed_asserv.speed_order_constrained.vt;
        //        (speedDebug.pid_v)[debug_count] = pid_process((Pid*)&(speed_asserv.pid_delta));
        //        (speedDebug.pid_vt)[debug_count] = pid_process((Pid*)&(speed_asserv.pid_alpha));
        (speedDebug.c)[debug_count] = speed_asserv.courbure;
        (speedDebug.ac)[debug_count] = motionState.speed.v + motionConstraint.a_max.a * 0.01;
        (speedDebug.atc)[debug_count] = motionState.speed.vt + motionConstraint.a_max.at * 0.01;
        (speedDebug.vcc)[debug_count] = motionConstraint.v_max.v * 2 / (2 + odo.coefs.spacing * fabsf(speed_asserv.courbure));
        (speedDebug.vac)[debug_count] = sqrtf(motionConstraint.a_max.v_vt / fabsf(speed_asserv.courbure));

        debug_count++;
    }
}

void debug_pos_asserv() {/*
    if (debug_count < DEBUG_COUNT_MAX){
        (posDebug.d)[debug_count] = pos_asserv.distance.d;
        (posDebug.dt)[debug_count] = pos_asserv.distance.dt;
        (posDebug.cons_v)[debug_count] = speed_asserv.speed_order_constrained.v;
        (posDebug.cons_vt)[debug_count] = speed_asserv.speed_order_constrained.vt;
        debug_count++;
    }*/
}

void debug_pos_xy_asserv() {/*
    if (debug_count < DEBUG_COUNT_MAX){
        (posXYDebug.x)[debug_count] = motionState.pos.x;
        (posXYDebug.y)[debug_count] = motionState.pos.y;
        debug_count++;
    }*/
}