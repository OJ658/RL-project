#ifndef Q_LEARNING_H
#define Q_LEARNING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double** Qmatrix;
int** reward;
//double alpha; 
//double gama;
//double epsilon;
envOutput stepOut;
envOutput finalOut;
int current_state;
action current_action;
int new_state;
void alloc_Q();
void alloc_reward();
void Q_render();
void reward_render();
int max_Qvalue(int current_state, double** Qmatrix);
void episode();
void trajectory();

#endif 
