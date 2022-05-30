#include "mazeEnv.h" 
#include "functions.h"
#include "Q_learning.h"


void alloc_Q() {
    // création de la matrice Q la Q-value
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

/*void reward_render() { // affichage de la matrice reward
    for(int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
            printf("%d ",reward[i][j]);
        }
        printf("\n");
    }
}*/

// Initialisation de alpha et gamma et epsilon
double alpha = 0.01;
double gama = 0.95;
double epsilon = 0.90;

int max_Qvalue(int current_state, double** Qmatrix) { 
    // La fonction max_Qvalue détermine l'action ayant le plus grande valeur dans la Qmatrix en
    // faisant le départ de la position current_state
    double maximum = fmax(fmax(Qmatrix[current_state][up],Qmatrix[current_state][down]),fmax(Qmatrix[current_state][left],Qmatrix[current_state][right]));
    // maximum = max Qmatrix[current_state][action], la variable est action
    int* tab_max = malloc(number_actions*sizeof(int));
    int j=0;
    for(int i=0;i<number_actions;i++) {
        if(Qmatrix[current_state][i] == maximum) {
            tab_max[j]=i;
            j++;
        }
    }
    // On remplit tab_max par les actions i vérifiant : maximum = max Qmatrix[current_state][action] 
    int r = rand()%j;
    return tab_max[r];
    // On retourne une valeur aléatoire parmi les actions dans tab_max
}

/*void Q_render() {
    for(int i=0;i<rows*cols;i++) {
        printf("row = %d\n",i);
        printf("action = %d\n",max_Qvalue(i,Qmatrix));
        for(int j=0;j<number_actions;j++) {
            printf("%lf ",Qmatrix[i][j]);
        }
        printf("\n\n");
    }
}*/

void episode() {
    double r = (double)rand()/(double)(RAND_MAX); // nombre aléatoire réel entre 0 et 1
    current_state = state_row*cols+state_col;
    // On adopte la méthode Epsilon-greedy
    if(r<=epsilon) {
        current_action = env_action_sample();
        // on choisit une action aléatoire
    }
    else {
        current_action = max_Qvalue(current_state,Qmatrix);
        // on choisit l'action ayant la valeur maximum dans la Qmatrix pour la position current_state
    }
    stepOut = maze_step(current_action);
    new_state = state_row*cols+state_col;// la fonction maze_step change state_row et state_col
    if(visited[state_row][state_col] != wall) {
        // mise à jour de la Qmatrix par la formule de Bellman
        Qmatrix[current_state][current_action] += alpha*(reward[state_row][state_col] + gama * Qmatrix[new_state][max_Qvalue(new_state,Qmatrix)] - Qmatrix[current_state][current_action]);  
    }
    else {
        Qmatrix[current_state][current_action] += alpha*(reward[state_row][state_col] - Qmatrix[current_state][current_action]);
        if (epsilon>0.05) {epsilon -= 1e-3;}
    }
}    


void trajectory() { // la fonction trajectory n'est que le déroulement de l'algorithme à l'aide des fonctions 
                    // déja implémenté   
    maze_reset();
    int ctp = 0;
    int done = 0;
      
    while(done != 1) { // tant qu'on n'est pas arrivé au but
        current_state = state_row*cols+state_col;
        finalOut= maze_step(max_Qvalue(current_state,Qmatrix));
        maze[state_row][state_col] = '.';// remplacer chaque position occupée par un point
        ctp++;
        done = finalOut.done;// mise à jour de done
    }
    printf("le nb d'itérations = %d\n",ctp);
}
