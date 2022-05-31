#ifndef DOUBLE_Q_LEARNING_H
#define DOUBLE_Q_LEARNING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double** Qmatrix_1;
double** Qmatrix_2;
envOutput stepOut;
envOutput finalOut;
int current_state;
action current_action;
int new_state;
void alloc_Q1();
void alloc_Q2();
int max_Qvalue(int state);
void episode_double_q_learning();
void trajectory_double_q_learning();

#endif 
