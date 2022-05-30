#include "mazeEnv.h"
#include "Q_learning.h"

int dfs(int row, int col){ //retourne le chemin vers le but
    int* current = &visited[row][col];

    if(*current == goal){
        return 1;
    }else if(*current == unknown){
        *current = known;

        if (dfs(row, col-1)){
            *current = crumb;
            return 1;
        } else if (dfs(row+1, col)){
            *current = crumb;
            return 1;
        }  else if (dfs(row, col+1)){
            *current = crumb;
            return 1;
        }  else if (dfs(row-1, col)){
            *current = crumb;
            return 1;
        }

    }

    return 0;
}

void add_crumbs(){
     for (int i=0; i<rows; i++){
          for (int j=0; j<cols; j++){
              if (visited[i][j] ==crumb){
                  maze[i][j] ='.';
              }
          }
     }
     maze[start_row][start_col]= 's';
}

int main(){
    maze_make("maze.txt");
    maze_reset();
    printf("la position initiale =(%d,%d)\n",start_row,start_col);
    printf("la position visée =(%d,%d)\n",goal_row,goal_col);
    printf("\n");
    init_visited(); // créer et remplir le tableau visited
    maze_render();//afficher le labyrinthe dans son état initial
    printf("\n\n");
    //dfs(start_row,start_col);
    //add_crumbs();
    //maze_render();
    //printf("\n\n");

    alloc_Q();//créer et initialiser la Qmatrix
    alloc_reward();//créer et initialiser la matrice reward
    int max_steps = 1000000; 
    for(int i=0;i<max_steps;i++){
        // L'agent est entrainé au fur et à mesure des itérations, le nb est choisi suffisament grand 
        // de manière que l'agent soit suffisamment prêt à déterminer le chemin au but 
       episode();
   }
   printf("chemin obtenu avec la méthode du Q-learning :\n");
   trajectory();//déroulement de l'algorithme
   maze_render();
   return 0;
}