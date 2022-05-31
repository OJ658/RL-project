#include "mazeEnv.h" 
#include "functions.h"
#include "q_learning.h"


void alloc_Q_q_learning() {
    // création de la matrice Q
    Qmatrix = malloc(rows * cols * sizeof(double*));
    for(int i=0;i<rows*cols;i++){
        Qmatrix[i] = malloc(number_actions * sizeof(double));
    }
    // initialisation de la matrice Q : 0 partout
    for(int i =0;i<rows*cols;i++) {
        for(int j=0;j<number_actions;j++) {
            Qmatrix[i][j] = 0;
        }
    }
}

// création de la matrice reward;
void alloc_reward() {
    reward = malloc(rows * sizeof(int*));
    for(int i=0;i<rows;i++) {
        reward[i] = malloc(cols * sizeof(int));
    }
    // initialisation de r : 1 pour goal, -1 pour wall, 0 pour les autres
    for(int i =0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
            if(visited[i][j] == wall) {reward[i][j] = -1;}
            else if(visited[i][j] == goal) {reward[i][j] = 1;}
            else {reward[i][j] = 0;}
        }
    }
}

// Initialisation de alpha et gamma et epsilon
double alpha_1 = 0.01;
double gama_1 = 0.95;
double epsilon_1 = 0.90;

int max_Qvalue_qlearning(int state) { 
    // La fonction max_Qvalue détermine l'action ayant le plus grande valeur dans la Qmatrix en
    // faisant le départ de la position current_state
    double maximum = fmax(fmax(Qmatrix[state][up],Qmatrix[state][down]),fmax(Qmatrix[state][left],Qmatrix[state][right]));
    // maximum = max Qmatrix[current_state][action], la variable est l'action
    int* tab_max = malloc(number_actions*sizeof(int));
    int j=0;
    for(int i=0;i<number_actions;i++) {
        if(Qmatrix[state][i] == maximum) {
            tab_max[j]=i;
            j++;
        }
    }
    // On remplit tab_max par les actions i vérifiant : maximum = max Qmatrix[current_state][action] 
    int r = rand()%j;
    return tab_max[r];
    // On retourne une valeur aléatoire parmi les actions dans tab_max
}

void episode_q_learning() {// 
    double r = (double)rand()/(double)(RAND_MAX); // nombre aléatoire réel entre 0 et 1
    current_state = state_row*cols+state_col;
    // On adopte la méthode Epsilon-greedy
    if(r<=epsilon_1) {
        current_action = env_action_sample();
        // on choisit une action aléatoire
    }
    else {
        current_action = max_Qvalue_qlearning(current_state);
        // on choisit l'action ayant la valeur maximum dans la Qmatrix pour la position current_state
    }
    stepOut = maze_step(current_action);
    new_state = state_row*cols+state_col;// la fonction maze_step change state_row et state_col
    if(visited[state_row][state_col] != wall) {
        // mise à jour de la Qmatrix par la formule de Bellman
        Qmatrix[current_state][current_action] += alpha_1*(reward[state_row][state_col] + gama_1 * Qmatrix[new_state][max_Qvalue_qlearning(new_state)] - Qmatrix[current_state][current_action]);  
    }
    else {
        Qmatrix[current_state][current_action] += alpha_1*(reward[state_row][state_col] - Qmatrix[current_state][current_action]);
        if (epsilon_1>0.05) {epsilon_1 -= 1e-3;}
    }
}    


void trajectory_q_learning() { // la fonction trajectory n'est que le déroulement de l'algorithme à l'aide des fonctions 
                    // déja implémenté   
    maze_reset();
    int ctp = 0;
    int done = 0;
      
    while(done != 1) { // tant qu'on n'est pas arrivé au but
        current_state = state_row*cols+state_col;
        finalOut= maze_step(max_Qvalue_qlearning(current_state));
        maze[state_row][state_col] = '.';// remplacer chaque position occupée par un point
        ctp++;
        done = finalOut.done;// mise à jour de done
    }
    printf("le nb d'itérations = %d\n",ctp);
}
