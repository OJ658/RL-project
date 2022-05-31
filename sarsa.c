#include "mazeEnv.h" 
#include "functions.h"
#include "sarsa.h"
#include "q_learning.h"

void alloc_Q_sarsa() {
    // création de la matrice Q
    Qmatrix_sarsa = malloc(rows * cols * sizeof(double*));
    for(int i=0;i<rows*cols;i++){
        Qmatrix_sarsa[i] = malloc(number_actions * sizeof(double));
    }
    // initialisation de la matrice Q : 0 partout
    for(int i =0;i<rows*cols;i++) {
        for(int j=0;j<number_actions;j++) {
            Qmatrix_sarsa[i][j] = 0;
        }
    }
}

// Initialisation de alpha et gamma et epsilon
double alpha_2 = 0.01;
double gama_2 = 0.950000;
double epsilon_2 = 0.74000;

int max_Qvalue_sarsa(int state) { 
    // La fonction max_Qvalue détermine l'action ayant le plus grande valeur dans la Qmatrix en
    // faisant le départ de la position current_state
    double maximum = fmax(fmax(Qmatrix_sarsa[state][up],Qmatrix_sarsa[state][down]),fmax(Qmatrix_sarsa[state][left],Qmatrix_sarsa[state][right]));
    // maximum = max Qmatrix[current_state][action], la variable est action
    int* tab_max = malloc(number_actions*sizeof(int));
    int j=0;
    for(int i=0;i<number_actions;i++) {
        if(Qmatrix_sarsa[state][i] == maximum) {
            tab_max[j]=i;
            j++;
        }
    }
    // On remplit tab_max par les actions i vérifiant : maximum = max Qmatrix[current_state][action] 
    int r = rand()%j;
    return tab_max[r];
    // On retourne une valeur aléatoire parmi les actions dans tab_max
}

action optimal_action(int state) {
    // La fonction optimal_action détermine l'action ayant le plus grande valeur dans la Qmatrix mais
    // aussi menant vers une autre position pas encore visitée en faisant le départ de la position current_state
    //double maximum = fmax(fmax(Qmatrix[current_state][up],Qmatrix[current_state][down]),fmax(Qmatrix[current_state][left],Qmatrix[current_state][right]));
    // maximum = max Qmatrix[current_state][action], la variable est action
    int* tab_max = malloc(number_actions*sizeof(int));
    int j=0;
    int position_row = state/cols;
    int position_col = state%cols;
    double maximum = Qmatrix_sarsa[state][0];
    for(int i=0;i<number_actions;i++) {
        // actualiser (position_row,position_col) en fonction de l'ation sélectionnée
        if (i==up){
       position_row = max(0,position_row -1);
        }else if (i==down){
       position_row = min(rows-1,position_row +1);
        }else if (i==right){
       position_col = min(cols-1,position_col +1);
        }else if (i==left){
       position_col = max(0,position_col -1);
        }
        if(Qmatrix_sarsa[state][i] == maximum && (visited[position_row][position_col]==unknown || visited[position_row][position_col]==goal)) {
            tab_max[j]=i;
            j++;
        }
        else if(Qmatrix_sarsa[state][i] > maximum && (visited[position_row][position_col]==unknown || visited[position_row][position_col]==goal)) {
            j=0;
            tab_max[j]=i;
            maximum = Qmatrix_sarsa[state][i];
            j++;
        }
        //tab_max contient les actions avec lesquelles le maximum Q[state][] est atteint mais aussi qui mène vers des positions non visitées
        else {};
        // reinitialiser (position_row,position_col)
        position_row = state/cols;
        position_col = state%cols;
    }
    // On remplit tab_max par les actions i vérifiant : maximum = max Qmatrix[current_state][action] 
    int r = rand()%(j);
    return tab_max[r];
    // On retourne une valeur aléatoire parmi les actions dans tab_max
}

action choose_action(int state){
    double r = (double)rand()/(double)(RAND_MAX); // nombre aléatoire réel entre 0 et 1
    action chosen;
    // On adopte la méthode Epsilon-greedy
    if(r<=epsilon_2) {
        chosen = env_action_sample();
        // on choisit une action aléatoire
    }
    else {
        chosen = max_Qvalue_sarsa(state);
        // on choisit l'action ayant la valeur maximum dans la Qmatrix pour la position current_state
    }
    return chosen;
}


void episode_sarsa() {
    current_state = state_row*cols+state_col;
    stepOut = maze_step(current_action);
    new_state = state_row*cols+state_col;// la fonction maze_step change state_row et state_col
    new_action = choose_action(new_state);
    if(visited[state_row][state_col] != wall) {
        // mise à jour de la Qmatrix par la formule de Bellman
        Qmatrix_sarsa[current_state][current_action] += alpha_2*(reward[state_row][state_col] + gama_2 * Qmatrix_sarsa[new_state][new_action] - Qmatrix_sarsa[current_state][current_action]);  
    }
    else {
        Qmatrix_sarsa[current_state][current_action] += alpha_2*(reward[state_row][state_col] - Qmatrix_sarsa[current_state][current_action]);
        if (epsilon_2>0.05) {epsilon_2 -= 1e-3;}
    }
    current_action = new_action;// pour assurer que la continuité entre les états consécutifs
}    


void trajectory_sarsa() { // la fonction trajectory n'est que le déroulement de l'algorithme à l'aide des fonctions 
                    // déja implémenté   
    maze_reset();
    int ctp = 0;
    int done = 0;
      
    while(done != 1) { // tant qu'on n'est pas arrivé au but
        current_state = state_row*cols+state_col;
        visited[state_row][state_col] = known;
        finalOut =  maze_step(optimal_action(current_state));  
        maze[state_row][state_col] = '.';// remplacer chaque position occupée par un point
        ctp++;
        done = finalOut.done;// mise à jour de done
    }
    printf("le nb d'itérations = %d\n",ctp);
}
