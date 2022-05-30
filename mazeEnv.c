#include "mazeEnv.h" 
#include "functions.h"

void alloc_maze(){ // allouer de l'espace pour le labyrinthe
     maze = malloc(rows * sizeof(char*));

     for(int i=0; i<rows; i++) {
         maze[i] = malloc(cols * sizeof(char*));
     }
}

void maze_make(char* file_name){ // importer le labyrinhe à partir du fichier texte
     char c;
     char rows_s[3] ={'\0'};
     char cols_s[3] ={'\0'};
     int rows_i = 0;
     int cols_i = 0;
     int swap = 0;

     FILE* file = fopen(file_name, "r");

     if (file) { // déterminer le nb de lignes et de colonnes
         /* lire la premiere ligne avant EOF */
         while( (c=getc(file)) != EOF) {
               if(c== '\n'){
                      break;
               } else if (c==',') {
                      swap = 1;
               } else if (!swap) {
                      rows_s[rows_i]=c;
                      rows_i++;
               } else {
                      cols_s[cols_i]= c;
                      cols_i++;
               }
         }
     }

     /* convertir le string en nombre */
     rows = atoi(rows_s);
     cols = atoi(cols_s);

     alloc_maze();

     for (int i=0; i<rows; i++){
         for (int j=0; j < cols; j++){
             c = getc(file);

             if (c=='\n'){
                 c = getc(file);
             } else if (c == 's'){// déterminer les cordonnées de la source
               start_row = i;
               start_col = j;
             } else if ( c == 'g'){// déterminer les coordonnées du but
               goal_row = i;
               goal_col = j;
             }

             maze[i][j] = c;
         }
     }

     fclose(file);
}
// La variable maze contient le labyrinthe

void maze_render(){ // afficher le labyrinthe
     for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
             printf("%c ", maze[i][j]);
         }
         printf("\n");
     }
     printf("\n");
}


void maze_reset(){ // revenir à la situation initiale, cad se replacer dans la position source
     state_row = start_row;
     state_col = start_col;
}

envOutput maze_step(action a){ // exécute l'action a et change les variables state(row et col) qui 
// indiquent notre position 
    int reward = 0;
    int done = 0;
    envOutput stepOut;

    if (a==up){
       state_row = max(0,state_row -1);
    }else if (a==down){
       state_row = min(rows-1,state_row +1);
    }else if (a==right){
       state_col = min(cols-1,state_col +1);
    }else if (a==left){
       state_col = max(0,state_col -1);
    }
    
    if((state_row == goal_row) && (state_col == goal_col)){
       reward = 1;
       done   = 1;
    }

    stepOut.reward = reward;
    stepOut.done   = done;
    stepOut.new_col = state_col;
    stepOut.new_row = state_row; 

   return stepOut;
}

action env_action_sample(){ // avoir une action aléatoire
  return (enum action)(rand() % number_actions);
}

void alloc_visited() // créer un tableau des int* de même taille que le labyrinthe
{
        visited = malloc(rows * sizeof(int*));
        int i;
        for (i = 0; i < rows; ++i){
                visited[i] = malloc(cols * sizeof(int*));
        }
}


void init_visited() // remplir un tableau par wall pour le but etc
{
        alloc_visited();

        int i, j;
        for (i = 0; i < rows; ++i) {
                for (j = 0; j < cols; ++j) {
                        if (maze[i][j] == '+') {
                                visited[i][j] = wall;
                        } else if (maze[i][j] == 'g') {
                                visited[i][j] = goal;
                        } else {
                                visited[i][j] = unknown;
                        }
                }
        }
}

