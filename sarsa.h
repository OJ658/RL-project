#ifndef SARSA_H
#define SARSA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double** Qmatrix_sarsa;
//int** reward;
envOutput stepOut;
envOutput finalOut;
int current_state;
action current_action;
int new_state;
action new_action;
void alloc_Q_sarsa();
void alloc_reward();
int max_Qvalue_sarsa(int current_state);
action choose_action(int state);
void episode_sarsa();
void trajectory_sarsa();

#endif 