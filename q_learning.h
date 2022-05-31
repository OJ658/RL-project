#ifndef Q_LEARNING_H
#define Q_LEARNING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double** Qmatrix;
int** reward;
envOutput stepOut;
envOutput finalOut;
int current_state;
action current_action;
int new_state;
void alloc_Q_q_learning();
void alloc_reward();
int max_Qvalue_q_learning(int current_state);
void episode_q_learning();
void trajectory_q_learning();

#endif 
